;-----------------------------------------------------------
; wasm_linux_interface.inc
; Linux interface for WASM parser/validator
; Uses libc for output — mirrors wasm_kolibrios_interface.inc
;-----------------------------------------------------------

extrn printf
extrn puts
extrn putchar
extrn fwrite
extrn exit
extrn stdout


; --------------------------------------------------
; print a printf style string and add a newline
; --------------------------------------------------
macro println str, [args] {
common
    pusha
    local ..s, ..count
    ..count = 0
    section '.data'
    ..s db str, 10, 0
    section '.text'

reverse
match any, args \{
        push args
        ..count = ..count + 1
\}
common
        push ..s
        call printf
        add esp, 4 + (..count * 4)
        popa
}

macro print str, [args]{
common
    pusha
    local ..s, ..count
    ..count = 0
    section '.data'
    ..s db str, 0
    section '.text'

reverse
match any, args \{
        push args
        ..count = ..count + 1
\}
common
        push ..s
        call printf
        add esp, 4 + (..count * 4)
        popa
}

