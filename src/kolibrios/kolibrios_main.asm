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

include 'wasm_kolibrios_interface.inc'
include '../core/wasm_parser.inc'

START:
        mcall   68, 11
        stdcall dll.Load, @IMPORT
        or      eax, eax        
                               
        jnz     .exit

        cmp     byte[parameters], 0
        je      .no_file 

        ; get file details
        mov     eax, 70
        mov     dword [file_info_struct], 5

        mov     dword [file_info_struct + 16], ddib_block
        mov     dword [file_info_struct +21], parameters
        mov     ebx, file_info_struct
        mcall
        test    eax, eax
        jnz     .file_details_error
        ; get size (hopefully no wasm file doesn't exceed 4gb)
        mov     ecx, dword [ddib_block + 32]
        mov     [file_siz], ecx
        ; println "Size gotten for file: %s is %d", parameters, ecx
        mov     ebx, 12
        mov     eax, 68
        mcall


        mov     [file_ptr], eax

        mov     eax, 70
        mov     ebx, [file_ptr]
        mov     dword [file_info_struct], 0
        mov     dword [file_info_struct + 4], 0
        mov     dword [file_info_struct + 8], 0
        mov     ecx, dword [file_siz]
        mov     dword [file_info_struct + 12], ecx
        mov     dword [file_info_struct + 16], ebx
        mov     dword [file_info_struct + 20], 0
        mov     dword [file_info_struct + 21], parameters
        mov     ebx, file_info_struct
        mcall

        test   eax, eax
        jne .file_read_error

        mov     eax, [file_ptr]
        mov     ebx, dword [file_siz]
        ; println "Passing ptr: 0x0x, and size: %d to wasm_parse", eax, ebx
        call    wasm_parse
        mov     ebx, 13
        mov     eax, 68
        mov     ecx, [file_ptr]
        mcall
        jmp     .exit

.no_file:
        println "Usage: wasm_dis <filename>"
        jmp     .exit
.file_details_error:
        println "An error occurred while getting details for file: %s", parameters
        jmp     .exit

.file_read_error:
        println  "An error occured while reading file: %s", parameters

.exit:
        print   "Press any key to exit"
        invoke con_getc
        invoke con_exit, 1
        mov     eax, -1
        mcall
I_END:

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

    rb  131072 ; reserve 128kb
align 16

STACKTOP:

parameters rb 1024
ddib_block rb 560 ; 40 bytes + at most 520 for bytes
MEM:
