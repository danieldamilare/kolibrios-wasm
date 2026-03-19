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
        xor     esi, esi    ; accumulator
        xor     ecx, ecx    ; shift amount
.loop:
        movzx   eax, byte [ebx]
        inc     ebx
        mov     edx, eax    
        and     edx, 0x7F
        shl     edx, cl
        or      esi, edx
        add     ecx, 7
        test    eax, 0x80
        jnz     .loop
        mov     eax, esi
        pop     edx
        pop     esi
        pop     ecx
        ret


