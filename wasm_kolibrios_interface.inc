include 'includes/proc32.inc'
include 'includes/macros.inc'
include 'includes/dll.inc'
include 'includes/string.inc'

align 16
@IMPORT:
library  terminal, 'console.obj'

import terminal, \
        con_init, 'con_init', \
        con_exit, 'con_exit', \
        con_printf,  'con_printf', \
        con_getc,  'con_getch'

macro print str, [args]{
common
        local ..s, ..count,  ..skip
        ..count = 0
        jmp ..skip
        ..s db str, 0

..skip:
reverse
match any, args \{
        push args
        ..count = ..count + 1
\}

common
        push ..s
        call [con_printf]
        add esp, 4 + (..count * 4)
}


macro println str, [args]{
common
        local ..s, ..skip, ..count
        ..count = 0
        jmp ..skip
        ..s db str, 10, 0
..skip:

reverse
match any, args \{
        push args
        ..count = ..count + 1
\}
common
        push ..s
        call [con_printf]
        add esp, 4 + (..count * 4)
}

