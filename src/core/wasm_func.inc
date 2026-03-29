;----------------------------------------------------
; wasm_func.inc: Utility functions for wasm
;---------------------------------------------------


;---------------------------------------------------
; decode_leb128_u32
;
; decode an unsigned leb128 number
; use the algorithm described by Wikipedia: https://en.wikipedia.org/wiki/LEB128
;
; accept: ebx a pointer to the address to decode
; move ebx past the leb128 number
; wasm allows multiple 0 to follow unsigned leb128, our decoder just discard it
; automatically because the shift would overflow the register
; --------------------------------------------------

leb128_decode_u32:
        push    ecx
        push    esi
        push    edx
        xor     eax, eax    ; accumulator
        xor     ecx, ecx    ; shift amount
.loop:
        cmp     ecx, 35
        jge      .error
        movzx   esi, byte [ebx]
        advance
        mov     edx, esi    
        and     edx, 0x7F
        shl     edx, cl
        or      eax, edx
        add     ecx, 7
        test    esi, 0x80
        jnz     .loop
        pop     edx
        pop     esi
        pop     ecx
        ret
.error:
        println "Error while decoding leb128 integer: u32 must not exceed 4 bytes"
        jmp     parse_error

leb128_decode_s32:
        push    ecx
        push    esi
        push    edx
        xor     eax, eax    ; accumulator
        xor     ecx, ecx    ; shift amount
.loop:
        cmp     ecx, 35
        jge      .error
        movzx   esi, byte [ebx]
        advance
        mov     edx, esi    
        and     edx, 0x7F
        shl     edx, cl
        or      eax, edx
        add     ecx, 7
        test    esi, 0x80
        jnz     .loop
        cmp     ecx, 32
        jge     .done
        test    esi, 0x40
        jz      .done
        xor     esi, esi
        not     esi
        shl     esi, ecx
        or      eax, esi
.done
        pop     edx
        pop     esi
        pop     ecx
        ret
.error:
        println "Error while decoding leb128 integer: i32 must not exceed 4 bytes"
        jmp     parse_error



