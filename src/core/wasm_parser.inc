; ---------------------------------------------------------------------
; wasm_parser.inc
; WASM BINARY PARSER
; Parse the Binary Format described in the Wasm 1.0 Spec
; ---------------------------------------------------------------------

include 'wasm_const.inc'
include 'wasm_name.inc'

buf_ptr dd ?
buf_siz dd ?
buf_end dd ?
func_idx dd 0

parse_saved_esp dd 0 
parse_saved_ebp dd 0

macro advance{
        inc ebx
}

include 'wasm_func.inc'

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
; a wasm binary at least have a 4 bytes magic and 4 bytes header
        cmp     ebx, 0x08 
        jb      .too_small
        mov     [buf_ptr], eax
        mov     [buf_siz], ebx
        lea     ecx, [ebx + eax]
        mov     [buf_end], ecx
        ; println "Buf start: 0x%x, buf_size: %d, buf_end: 0x%x", eax, ebx, ecx
        mov     ebx, eax
        ; save for error recovery
        mov     [parse_saved_esp], esp
        mov     [parse_saved_ebp], ebp
.parse_module:
        call    check_header
        call    parse_sections

.parse_end:
        println "Successfully parsed wasm binary"
        ret

.too_small:
        println "Refusing to parse a file of size: 0x%x without wasm header", ebx
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
        mov     eax, [buf_end]
        cmp     ebx, eax
        jge     @f
        jmp     @b
.section_skip:
        println "In section skip"
        call leb128_decode_u32
        add  ebx, eax
        mov  eax, [buf_end]
        cmp  ebx, eax
        jge  @f
        jmp  @b
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
        println "       functype[%d]:", dword [func_idx]
        inc [func_idx]
        advance
        call    parse_vec_param
        call    parse_vec_result
        println ""
        ret

parse_vec_param:
        push    edi
        call    leb128_decode_u32
        mov     edi, eax
        print "            Params(%d): ", edi

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
        print "            Result(%d): ", edi

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
        println "Section 2: Import (%d bytes)", eax
        add     eax, ebx
        push    eax
        call    leb128_decode_u32
        println "    Vec of Import (Length: %d)", eax
        mov     edi, eax

.loop:
        test    edi, edi
        jz      .done
        call    parse_import
        dec     edi
        jmp     .loop     
.done:
        pop     esi
        cmp     ebx, esi
        jne     .error
        ret
.error:
        println "Invalid section size for import. ebx: (0x%x), esi: (0x%x", ebx, esi
        jmp     parse_error

parse_import:
; parse modname first
        call    leb128_decode_u32
        print "       module: %.*s", eax, ebx
        add     ebx, eax
; parse nm 
        call    leb128_decode_u32
        print " name: %.*s ", eax, ebx
        add     ebx, eax

parse_importdesc:
        movzx     eax, byte [ebx]
        advance
        test    eax, eax
        je      .typeidx
        cmp     eax, 0x01
        je      .tabletype 
        cmp     eax, 0x02 
        je      .memtype
        cmp     eax, 0x03
        je      .globaltype

.typeidx:
        call    leb128_decode_u32
        println " Import type: typeidx (%d)", eax
        ret
.tabletype:
        print   " Import type: "
        jmp     parse_table_type

.memtype:
        print   " Import type: "
        jmp     parse_memtype

.globaltype:
        print   " Import type: "
        jmp    parse_globaltype


parse_table_type:
        cmp   byte [ebx], 0x70
        je    @f
        movzx   eax, byte [ebx]  
        println "Error: Expecting funcref element type buf found (0x%x)", eax
        jmp     parse_error
@@:
        advance
        print   "Tabletype "
        jmp parse_limits
        


parse_memtype:
        print "Memtype: "
parse_limits:
        movzx   eax, byte [ebx]
        advance
        test  eax, eax
        je    .min
        cmp   eax, LIMIT_MIN_MAX
        je    .minmax
        println "Invalid Limit parsed"
        jmp      parse_error
.min:
        call    leb128_decode_u32
        println " with limit min: (%d), and unbounded max", eax
        ret
.minmax:
        call    leb128_decode_u32
        print   " with limit min: (%d)", eax
        call    leb128_decode_u32
        println   ", and max: (%d)", eax
        ret


parse_globaltype:
        print   "Globaltype: "
        call    valtype_to_str
        test    eax, eax
        jne     .valtype_error
        advance
        movzx     eax, byte[ebx]
        advance

; check if mutable or constant
        test    eax, eax
        jne     .check_var
        println "(const)"
        ret

.check_var:
        cmp     eax, GLOBAL_VAR
        jne     .mut_error
        println "(var)"
        ret

.valtype_error:
        movzx   eax, byte [ebx]
        println " Invalid Valtype (0x%x)", eax
        jmp     parse_error
.mut_error:
        println " Invalid mutable type (%x)", eax
        jmp     parse_error


parse_function_sec:
        call    leb128_decode_u32
        println ""
        println "Section 3: Function (%d bytes)", eax
        add     eax, ebx
        push    eax
; function is  vec(typeidx)

        call    leb128_decode_u32
        mov     edi, eax
        print   "Vector of Typeidx: "
.loop:
        test    edi, edi 
        jz      .done
        call    leb128_decode_u32
        print   " %d ", eax
        dec     edi
        jmp     .loop
.done:
        pop     esi
        cmp     esi, ebx
        jne     .error
        println ""
        ret
.error:
        println "Error while parsing function section. Section size is incorrect"
        jmp     parse_error


parse_table_sec:
        call     leb128_decode_u32
        println ""
        println "Section 4: Table (%d bytes)", eax
        add     eax, ebx
        push    eax
; table is a vector of tabletype
        call    leb128_decode_u32
        mov     edi, eax
        println "    Vector of Tabletype (Length: %d): ", edi
.loop:
        test    edi, edi
        jz      .done
        print   "        "
        call    parse_table_type
        dec     edi
        jmp     .loop
.done:
        pop     esi
        cmp     ebx, esi
        jne     .error
        ret
.error:
        println "Error while parsing table section: Section size is incorrect"
        jmp     parse_error


parse_memory_sec:
        call     leb128_decode_u32
        println ""
        println "Section 5: Memory (%d bytes)", eax
        add     eax, ebx
        push    eax
; memory section is a vector of memtype
        call    leb128_decode_u32
        println "    Vector of Memtype (Length: %d): ", eax
        mov     edi, eax

.loop:
        test    edi, edi
        jz      .done
        print   "        "
        call   parse_memtype
        dec     edi
        jmp     .loop
.done:
        pop     esi
        cmp     ebx, esi
        jne     .error
        ret
.error:
        println "Error while parsing memory section: Section size is incorrect"
        jmp     parse_error


parse_global_sec:
        call    leb128_decode_u32
        println ""
        println "Section 6: Global (%d bytes)", eax
        add     eax, ebx
        push    eax
; global section is a vector of global
        call    leb128_decode_u32
        println  "    Vector of Global (Length: %d): ", eax
        mov     edi, eax
.loop:
        test    edi, edi
        jz      .done
        print   "        "
        call    parse_globaltype
        print   "        init: "
        call    parse_const_expr
        dec     edi
        jmp     .loop
.done:
        pop     esi
        cmp     esi, ebx
        jne     .error
        ret
.error:
        println "Error while parsing global section: Section size is incorrect"
        jmp     parse_error


parse_export_sec:
        call    leb128_decode_u32
        println ""
        println "Section 7: Export (%d bytes)", eax
        add     eax, ebx
        push    eax
        call    leb128_decode_u32
        println "    Vector of Export (Length: %d): ", eax
        mov     edi, eax
.loop:
        test    edi, edi
        jz      .done
        call    parse_export
        dec     edi
        jmp     .loop
.done:
        pop     esi
        cmp     esi, ebx
        jne     .error
        ret
.error: 
        println "Error while parsing export section: Section size is incorrect"
        jmp     parse_error


parse_export:
; parse nm
        call    leb128_decode_u32
        print "        name: %.*s ", eax, ebx
        add     ebx, eax

        movzx     eax, byte [ebx]
        advance
        test    eax, eax
        je      .funcidx
        cmp     eax, 0x01
        je      .tableidx
        cmp     eax, 0x02
        je      .memidx
        cmp     eax, 0x03
        je      .globalidx

.funcidx:
        call    leb128_decode_u32
        println " Export type: funcidx (%d)", eax
        ret

.tableidx:
        call    leb128_decode_u32
        println " Export type: tableidx (%d)", eax
        ret

.memidx:
        call    leb128_decode_u32
        println " Export type: memidx (%d)", eax
        ret

.globalidx:
        call    leb128_decode_u32
        println " Export type: globalidx (%d)", eax
        ret

parse_start_sec:
        call   leb128_decode_u32
        println ""
        println "Section 8: Start (%d bytes)", eax
        add     eax, ebx
        push    eax
        call    leb128_decode_u32
        println "    Function index: %d", eax
        pop     eax
        cmp     eax, ebx
        jne     .error
        ret
.error:
        println "Error while parsing start section: Section size is incorrect"
        jmp     parse_error


parse_element_sec:
        call     leb128_decode_u32
        println ""
        println "Section 9: Element (%d bytes)", eax
        add     eax, ebx
        push    eax
        call    leb128_decode_u32
        println "    Vector of Elem (Length: %d)", eax
        mov     edi, eax
.loop:
        test    edi, edi
        jz      .done
        call    parse_elem
        dec     edi
        jmp     .loop
.done:  
        pop     esi
        cmp     ebx, esi
        jne     .error
        ret
.error: 
        println "Error while parsing element section: Section size is incorrect, supposed to end at 0x%x but ended at 0x%x", ebx, esi
        jmp     parse_error


parse_elem:
        call    leb128_decode_u32
        println "    tableidx: %d", eax
        println "    offset"
        call    parse_const_expr
        print  "    vector of funcidx: "
        call    leb128_decode_u32
        push    edi
        mov     edi, eax
.loop:
        test    edi, edi
        jz      .done
        call    leb128_decode_u32
        print " %d ", eax
        dec     edi
        jmp .loop
.done:
        pop     edi
        println ""
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
        println "Section 11: Data (%d bytes)", eax
        add     eax, ebx
        push    eax
        call    leb128_decode_u32
        println "    Vector of Data (Length: %d)", eax
        mov     edi, eax
.loop:
        test    edi, edi
        jz      .done
        call    parse_data
        dec     edi
        jmp     .loop
.done:
        pop     esi
        cmp     ebx, esi
        jne     .error
        ret
.error:
        println "Error while parsing Data section: Section size is incorrect"
        jmp     parse_error


parse_data:
        call    leb128_decode_u32        
        println "        memidx: %d", eax
        call    parse_const_expr
        print   "        vector of bytes:"
        call    leb128_decode_u32
        push    edi
        mov     edi, eax
.loop: 
        test    edi, edi
        jz      .done
        movzx   esi, byte [ebx]
        advance
        print   " 0x%x", esi
        dec     edi
        jmp     .loop
.done:
        pop     edi
        println ""
        ret

; -----------------------------------------------------------------
; expression parsing
; parse wasm instructions
; -------------------------------------------------------------------
parse_op_simple:
        movzx   eax, byte [ebx]
        advance
        println " %s ", dword [opcode_str_table + eax * 4]
        ret

parse_op_u32:
        movzx   esi, byte [ebx]
        advance
        call    leb128_decode_u32
        println " %s %d", dword [opcode_str_table + esi * 4], eax
        ret

parse_op_memarg:
        push    edi
        movzx   esi, byte [ebx]
        advance
        call    leb128_decode_u32
        mov     edi, eax
        call    leb128_decode_u32
        println "%s align=%d offset=%d", dword [opcode_str_table + esi * 4], edi, eax
        pop     edi
        ret

parse_blocktype:
        cmp     byte [ebx], 0x40
        je     .exit
        print  " (result "
        call    valtype_to_str
        test    eax, eax
        jne     .error
        print   ")"
.exit:
        advance
        println ""
        ret
.error:
        println "Error: Invalid valtype type while parsing blocktype"
        jmp     parse_error

parse_op_block:
        movzx   esi, byte [ebx]
        advance
        print   "  %s ", dword [opcode_str_table + esi * 4]
        call    parse_blocktype
.instr:
        jmp     parse_expr
.error:
        println "An error occurred while parsing %s expression", dword [opcode_str_table + esi * 4]
        jmp     parse_error


parse_op_if:
        push    edi
        movzx   esi, byte [ebx]
        advance
        print   " %s ", dword [opcode_str_table + esi * 4]
        call    parse_blocktype
        mov     edi, 0x0b
        mov     esi, 0x05
.loop:
        movzx     eax, byte[ebx]
        cmp     eax ,edi
        je      .done
        cmp     eax, esi
        je      .else 
        call    dword [opcode_parse_table + eax * 4]
        jmp     .loop
.else:
        advance
        println ""
        println "else"

@@:
        movzx     eax, byte [ebx]
        advance
        cmp     eax, edi
        je      .done
        call    dword [opcode_parse_table + eax * 4]
        jmp     @b
.done:
        advance
        pop     edi
        println "end"
        ret

parse_op_br_table:
        movzx   esi, byte [ebx]
        advance
        print   " %s ", dword [opcode_str_table + esi * 4]
        call    leb128_decode_u32
        push    edi
        mov     edi, eax
.loop:
        test    edi, edi
        jz      .done
        call    leb128_decode_u32
        print   " %d", eax
        dec     edi
.done:
        call    leb128_decode_u32
        println " labelidx: %d", eax
        pop     edi
        ret


parse_call_indirect:
        movzx   esi, byte [ebx]
        advance
        call    leb128_decode_u32
        println   " %s (%d) " , dword [opcode_str_table + esi * 4], eax
        movzx   eax, byte [ebx]
        advance
        cmp     eax, 0
        jne     .error
        ret
.error:
        println "Error while parsing call_indirect, expected 0x00, but got 0x%x", eax
        jmp     parse_error

parse_mem_inst:
        movzx   esi, byte [ebx]
        advance
        println "%s", dword [opcode_str_table + esi * 4]
        movzx   eax, byte[ebx]
        advance
        test    eax, eax
        jnz     .error
        ret

.error:
        println "Error while parsing memory instruction (%s): expected 0x00, but got 0x%x", dword [opcode_str_table + esi * 4], eax
        jmp     parse_error


parse_op_f64:
        movzx   esi, byte [ebx]
        advance
        mov     eax, [buf_end]
        sub     eax, ebx
        cmp     eax, 8
        jl      .error
        print " %s ", dword [opcode_str_table + esi * 4]
        println "%lf", dword [ebx], dword [ebx + 4] ; argument are pushed in reversed order
        add     ebx, 8
        ret
.error:
        println "Error: Incomplete binary for f64"
        jmp     parse_error


parse_op_f32:
        movzx   esi, byte [ebx]
        advance
        mov     eax, [buf_end]
        sub     eax, ebx
        cmp     eax, 4
        jl      .error
        movss   xmm0,  dword [ebx]
        add     ebx, 4
        cvtss2sd xmm0, xmm0  
        sub     esp, 8
        movsd   [esp], xmm0
        pop     eax
        pop     edx
        print "%s ", dword [opcode_str_table + esi * 4]
        println "%lf", edx, eax
        ret
.error:
        println "Error: Incomplete binary for f32"
        jmp     parse_error


parse_expr:
        movzx   esi, byte [ebx] ; read but don't advance so handler can handle their opcode themselves
        cmp     esi, 0x0B
        je      .done
        call    dword [opcode_parse_table + esi * 4]
        jmp parse_expr
.done:
        advance  ; advance the end byte
        ret

parse_const_expr:
        movzx   esi, byte [ebx]
        cmp     esi, 0x0B
        je      .error_empty    ; empty const expr is invalid
        cmp     esi, OP_GLOBAL_GET
        je      .dispatch
        cmp     esi, OP_I32_CONST
        jl      .error
        cmp     esi, OP_F64_CONST
        jg      .error
.dispatch:
        call    dword [opcode_parse_table + esi * 4]
        movzx   esi, byte [ebx]
        cmp     esi, 0x0B
        jne     .error_multiple
        advance    
        ret
.error_empty:
        println "Error: empty constant expression"
        jmp     parse_error
.error_multiple:
        println "Error: multiple instructions in constant expression"
        jmp     parse_error
.error:
        println "Error: invalid instruction in constant expression (0x%x)", esi
        jmp     parse_error

parse_op_i32:
        movzx   esi, byte [ebx]
        advance
        call    leb128_decode_s32
        println "%s %d", dword [opcode_str_table + esi * 4], eax
        ret

parse_op_i64:
        ret

parse_error:
        println "Error occured while parsing"
        mov     ebp, [parse_saved_ebp]
        mov     esp, [parse_saved_esp]
        ret
