; ---------------------------------------------------------------------
; wasm_parser.inc
; WASM BINARY PARSER
; Parse the Binary Format described in the Wasm 1.0 Spec
; ---------------------------------------------------------------------

include 'wasm_const.inc'
include 'wasm_name.inc'
include 'wasm_func.inc'

buf_ptr dd ?
buf_siz dd ?

; mimic c setjmp
parse_saved_esp dd 0 
parse_saved_ebp dd 0


macro advance{
        inc ebx
}

;---------------------------------------------
; print a string word for a valtype
; accept ebx - pointer holding valtype
; return eax - 0 on success, 1 on error
; --------------------------------------------

valtype_to_str:
        push    esi
        mov     esi, valtype
.loop:
        cmp     dword [esi], 0
        je      .error
        movzx   eax, byte [ebx]
        cmp     [esi], eax
        je      .found
        add     esi, 8
        jmp     .loop

.error:
        println "Unknown byte 0x%x", eax
        mov     eax, 1
        pop     esi
        ret
.found:
        add    esi, 4
        print  " %s ", dword [esi]
        xor     eax, eax
.exit:
        pop     esi
        ret
        
section_parse_table:
        dd parse_custom_sec
        dd parse_type_sec
        dd parse_import_sec
        dd parse_function_sec
        dd parse_table_sec
        dd parse_memory_sec
        dd parse_global_sec
        dd parse_export_sec
        dd parse_start_sec
        dd parse_element_sec
        dd parse_code_sec
        dd parse_data_sec

;----------------------------------------------------------
; wasm_parse: Parse a Wasm Binary
; INPUT:
; eax - Buffer address containing the binary
; ebx - Buffer size

; register usage
; ebx - current pointer to buffer
; eax - scratch register
; ---------------------------------------------------------
wasm_parse:
        mov     [buf_ptr], eax
        mov     [buf_siz], ebx
        mov     ebx, eax

        ; save for recovery
        mov     [parse_saved_esp], esp
        mov     [parse_saved_ebp], ebp

parse_module:
        call    check_header
        call    parse_sections
        jmp     parse_end

parse_end:
        println "Successfully parsed wasm binary"
        ret

check_header:
        cmp   dword [ebx], WASM_MAGIC
        jne   .magic_error
        add   ebx, 4
        cmp   dword [ebx], WASM_VERSION
        jne   .version_error
        add   ebx, 4
        ret
.magic_error:
        println "Error, Magic Number 0x%x does not match required 0x%x", dword [ebx], WASM_MAGIC
        jmp parse_error

.version_error:
        println "Error, Version Number 0x%x does not match required 0x%x", dword [ebx], WASM_VERSION
        jmp parse_error


; each binary part is a section
parse_sections:
        println "Parsing Sections..."
@@:
        movzx   eax, byte [ebx]
        advance
        cmp     eax, SECTION_DATA ; biggest section number in SECTION
        ja      .section_skip
        call    dword [section_parse_table + eax * 4]
        mov     eax, [buf_ptr]
        add     eax, [buf_siz]
        cmp     eax, ebx
        je      @f
        jmp     @b
.section_skip:
@@:
        ret
        
parse_custom_sec:
        call     leb128_decode_u32
        println ""
        println "Section 0: Custom (%d bytes)", eax
        ; do nothing but skip section
        lea     esi, [ebx + eax]  ; save end pointer to advance later
        ; print name 
        call    leb128_decode_u32
        println "   name: %.*s", eax, ebx ; write  ebx of length eax
        mov     ebx,  esi ;skip
        ret

parse_type_sec:
        push    ebp
        mov     ebp, esp
        call    leb128_decode_u32
        println ""
        println "Section 1: Type (%d bytes): ", eax

        add     eax, ebx
        push    eax
        ; type : vec<functype>
        call    leb128_decode_u32
        println "    Vec of functype (Length: %d): ", eax
        mov     edi, eax
.loop:
        test    edi, edi
        jz      .done
        call    parse_functype
        dec     edi
        jmp     .loop

.done:
        pop     esi 
        cmp     esi, ebx
        jne     .error
        leave
        ret
.error:
        println "Invalid section size for section: type"
        jmp     parse_error

parse_functype: ; function start with 0x60 
        cmp     byte [ebx], FUNC_START
        je      .continue

        println "Invalid byte while parsing function. Function should start with %d", FUNC_START
        jmp     parse_error

.continue:
        advance
        call    parse_vec_param
        call    parse_vec_result
        ret

parse_vec_param:
        push    edi
        call    leb128_decode_u32
        mov     edi, eax
        print "        Params(%d): ", edi

.loop:
        test    edi, edi
        jz      .done
        call    valtype_to_str
        test    eax, eax
        ja      parse_error
        advance
        dec     edi
        jmp     .loop
.done:
        println ""
        pop     edi
        ret

parse_vec_result:
        push    edi
        call    leb128_decode_u32
        mov     edi, eax
        print "        Result(%d): ", edi

.loop:
        test    edi, edi
        jz      .done
        call    valtype_to_str
        test    eax, eax
        ja      parse_error
        advance
        dec     edi
        jmp     .loop
.done:
        println ""
        pop     edi
        ret

parse_import_sec:
        call    leb128_decode_u32
        println ""
        println "Section 2: Import (%d bytes) - Skipping", eax
        add     ebx, eax
        ret

parse_function_sec:
        call    leb128_decode_u32
        println ""
        println "Section 3: Function (%d bytes) - Skipping", eax
        add     ebx, eax
        ret

parse_table_sec:
        call     leb128_decode_u32
        println ""
        println "Section 4: Table (%d bytes) - Skipping", eax
        add     ebx, eax
        ret

parse_memory_sec:
        call     leb128_decode_u32
        println ""
        println "Section 5: Memory (%d bytes) - Skipping", eax
        add     ebx, eax
        ret

parse_global_sec:
        call    leb128_decode_u32
        println ""
        println "Section 6: Global (%d bytes)- Skipping", eax
        add     ebx, eax
        ret

parse_export_sec:
        call    leb128_decode_u32
        println ""
        println "Section 7: Export (%d bytes) -  Skipping", eax
        add     ebx, eax
        ret

parse_start_sec:
        call   leb128_decode_u32
        println ""
        println "Section 8: Start (%d bytes)", eax
        add     eax, ebx
        push    eax
        call    leb128_decode_u32
        println "Function index: %d", eax
        pop     eax
        cmp     eax, ebx
        jne     .error
        ret
.error:
        println "Section size didnot match section"
        jmp     parse_error

parse_element_sec:
        call     leb128_decode_u32
        println ""
        println "Section 9: Element (%d bytes) - Skipping", eax
        add     ebx, eax
        ret

parse_code_sec:
        call     leb128_decode_u32
        println ""
        println "Section 10: Code (%d bytes) - Skipping", eax
        add     ebx, eax
        ret

parse_data_sec:
        call     leb128_decode_u32
        println ""
        println "Section 11: Data (%d bytes) - Skipping", eax
        add     ebx, eax
        ret

parse_error:
        println "Error occured while parsing"
        mov     ebp, [parse_saved_ebp]
        mov     esp, [parse_saved_esp]
        ret
