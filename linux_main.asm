format ELF
public  _start
use32

include 'wasm_linux_interface.inc'
include 'wasm_parser.inc'

section '.data' writeable
buf_size dd 0


section '.text' executable
LSEEK = 19
MMAP = 90

_start:
        ; stack at entry: [esp] = argc, [esp+4] = argv[0], [esp+8] = argv[1]
        pop     ecx             ; ecx = argc
        cmp     ecx, 2          ; need at least 2 args (program + filename)
        jl      .no_file
        println "Starting program"
        pop     eax             ; skip argv[0] (program name)
        pop     ebx             ; eax = argv[1] (wasm file path)
        println "File given: %s",  ebx

        ; open file
        mov     eax, 5          ; sys_open
        xor     ecx, ecx        ; O_RDONLY
        int     0x80
        test    eax, eax
        js      .open_error
        mov     ebx, eax        ; save fd

        ; get file size via lseek
        mov     eax, LSEEK         
        xor     ecx, ecx        
        mov     edx, 2          
        int     0x80
        mov     [buf_size], eax  ; save size
        
        push    eax             
        mov     eax, LSEEK         ; sys_lseek
        xor     ecx, ecx        ; offset 0
        xor     edx, edx        ; SEEK_SET
        int     0x80

        ; allocate buffer via mmap
        pop     edx             
        push    edx             
        println "edx is now %d", edx
        mov     eax, MMAP         
        push    0               
        push    ebx             
        push    2
        push    1               
        push    edx             
        push    0

        mov     ebx, esp
        int     0x80
        add     esp, 24        
        cmp     eax, -4095
        ja     .mmap_error

        ; parse
        pop     ebx             
        mov     ebx, [buf_size]
        call    wasm_parse

        ; exit clean
        mov     eax, 1
        xor     ebx, ebx
        int     0x80

.no_file:
        println "Usage: wasm_parser <file.wasm>"
        mov     eax, 1
        mov     ebx, 1
        int     0x80

.open_error:
        println "Error: could not open file"
        mov     eax, 1
        mov     ebx, 1
        int     0x80

.mmap_error:
        println "Error: could not allocate memory"
        mov     eax, 1
        mov     ebx, 1
        int     0x80

