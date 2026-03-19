format binary as ""

use32
org 0

db 'MENUET01'
dd 1
dd START
dd I_END
dd MEM
dd STACKTOP
dd parameters 
dd 00


file_info_struct:
   .fn dd 0
   .offset dd 0
   .offset2 dd 0
   .size dd 0
   .ptr dd 0
   .ecd db 0
   .path dd 0

file_ptr dd ?
file_siz dd ?
include 'wasm_kolibrios_interface.inc'
include 'wasm_parser.inc'

START:
        mcall   68, 11
        stdcall dll.Load, @IMPORT
        or      eax, eax        
                               
        jnz     .exit

        cmp     byte[parameters], 0
        je      .no_file 
        println  "Starting program"

        ; get file details
        mov     eax, 70
        mov     dword [file_info_struct], 5

        mov     dword [file_info_struct + 16], ddib_block
        mov     dword [file_info_struct +21], parameters
        mov     ebx, file_info_struct
        mcall
        test    eax, eax
        jnz     .file_error
        ; get size
        mov     ecx, dword [ddib_block + 32]
        mov     ebx, 12
        mov     eax, 68
        mcall

        mov     [file_ptr], eax

        mov     eax, 70
        mov     dword [file_info_struct], 1
        mov     dword [file_info_struct + 4], 0
        mov     dword [file_info_struct + 8], 0
        mov     ecx, dword [file_siz]
        mov     dword [file_info_struct + 12], ecx
        mov     dword [file_info_struct + 16], file_ptr
        mov     dword [file_info_struct + 21], parameters
        mov     ebx, file_info_struct
        mcall

        test   eax, eax
        jne .file_error

        mov     eax, file_ptr
        mov     ebx, dword [file_siz]
        call    wasm_parse

        print   "Press any key to exit"
        invoke con_getc

.no_file:
        println "Usage: wasm_dis <filename>"
        jmp   .exit
.file_error:
        println "An error occurred while processing file: %s", parameters
.exit:
        invoke con_exit, 1
        mov     eax, -1
        mcall
        int     0x40
I_END:
    rb  131072 ; reserve 128kb
align 16

STACKTOP:

parameters rb 1024
ddib_block rb 560 ; 40 bytes + at most 520 for bytes
MEM:
