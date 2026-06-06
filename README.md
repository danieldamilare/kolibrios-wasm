# kolibrios-wasm

A WebAssembly 1.0 runtime for [KolibriOS](http://kolibrios.org/), written in x86 FASM assembly.

## Status

Work in progress. Current state:

- Binary parser: WIP, tested on Linux and KolibriOS
- Validator: Not Started
- Interpreter: Not Started

## What it does

Parses WebAssembly 1.0 binary files according to the
[WebAssembly 1.0 spec](https://webassembly.github.io/multi-value/core/_download/WebAssembly.pdf).

The parser currently:
- Validates the magic number and version header
- Fully parses all 12 WASM 1.0 sections
- Decodes LEB128 u32, s32 integers as specified in the spec
- Validates section boundaries — catches malformed binaries
- Prints human-readable disassembly of all decoded data
- Disassembles all 172 WASM 1.0 opcodes in function bodies (code section in progress)
- Tested against real WASM binaries on both Linux and KolibriOS (QEMU)

## Project structure
```
src/
    core/
        wasm_const.inc               # Wasm 1.0 binary format constants
        wasm_name.inc                # Value type name strings
        wasm_func.inc                # LEB128 decoder
        wasm_parser.inc              # Binary parser
    kolibrios/
        includes/                    # KolibriOS standard includes
        kolibrios_main.asm           # KolibriOS entry point
        wasm_kolibrios_interface.inc # Console output macros
    linux/
        linux_main.asm               # Linux entry point
        wasm_linux_interface.inc     # libc output macros
tests/
    simple.wasm
    ekun.wasm
```

## Building

### Linux

Requires FASM and GCC (32-bit).
```bash
fasm src/linux/linux_main.asm linux_main.o
gcc -m32 -o parser linux_main.o -nostartfiles -lc -Wl,-e,_start
./parser tests/simple.wasm
```

### KolibriOS

Requires FASM.
```bash
fasm src/kolibrios/kolibrios_main.asm wasm_dis.kex
```

Copy `wasm_dis.kex` to KolibriOS and run from the console:
```
wasm_dis test.wasm
```

## Output

Both platforms produce identical output. Example against a real wasm binary:
```
    ./src/parser tests/ekun.wasm
Parsing Sections...

Section 1: Type (288 bytes):
    Vec of functype (Length: 45):
       functype[0]:
            Params(0):
            Result(0):

       functype[1]:
            Params(3):  i32  i32  i32
            Result(1):  i32

       functype[2]:
            Params(1):  i32
            Result(1):  i32

       functype[3]:
            Params(1):  i32
            Result(0):

       functype[4]:
            Params(2):  i32  i32
            Result(1):  i32

       functype[5]:
            Params(0):
            Result(1):  i32

       functype[6]:
            Params(2):  i32  i32
            Result(0):

       functype[7]:
            Params(3):  i32  i32  i32
            Result(0):

       functype[8]:
            Params(5):  i32  i64  i64  i64  i64
            Result(0):

       functype[9]:
            Params(4):  i32  i32  i32  i32
            Result(1):  i32

Section 2: Import (260 bytes)
    Vec of Import (Length: 9)
       module: env name: exit  Import type: typeidx (3)
       module: env name: emscripten_asm_const_int  Import type: typeidx (1)
       module: env name: _emscripten_memcpy_js  Import type: typeidx (7)
       module: env name: emscripten_date_now  Import type: typeidx (21)
       module: wasi_snapshot_preview1 name: fd_close  Import type: typeidx (2)
       module: wasi_snapshot_preview1 name: fd_write  Import type: typeidx (9)
       module: wasi_snapshot_preview1 name: fd_read  Import type: typeidx (9)
       module: env name: emscripten_resize_heap  Import type: typeidx (2)
       module: wasi_snapshot_preview1 name: fd_seek  Import type: typeidx (12)

Section 3: Function (249 bytes)
Vector of Typeidx:  0  3  3  3  3  2  1  3  4  4  6  3  3  0  2  3  3  0  0  5  6  5  10  3  3  2  3  2  2  6  5  10  2  5  6  1  7  3  5  4  3  4  3  1  1  9  3  2  4  4  5  2  4  6  1  1  1  2  2  2  6  6  2  0  3  0  3  5  3  6  3  6  0  3  7  6  7  7  7  7  3  0  3  0  4  3  0  5  0  0  1  0  0  7  0  0  0  0  0  0  0  0  0  0  0  0  6  0  0  0  0  0  11  0  0  0  0  0  0  0  0  0  0  0  2  5  1  1  5  1  2  3  2  4  4  4  4  2  2  3  1  9  2  2  9  1  4  1  1  11  22  11  15  15  11  23  24  16  16  11  25  26  27  28  5  5  5  0  2  2  1  13  13  1  4  4  2  1  1  1  29  2  17  8  14  30  8  31  10  2  32  33  34  10  35  4  17  12  36  7  2  10  37  19  19  38  1  18  6  39  1  9  1  2  1  4  5  2  2  1  3  4  4  6  8  14  20  20  8  40  41  6  6  5  5  14  8  8  8  42  3  3  2  5  43  12  44

Section 4: Table (4 bytes)
    Vector of Tabletype (Length: 1):
        Tabletype  with limit min: (44), and unbounded max

Section 5: Memory (6 bytes)
    Vector of Memtype (Length: 1):
        Memtype:  with limit min: (258), and max: (258)

Section 6: Global (8 bytes)
    Vector of Global (Length: 1):
        Globaltype:  i32 (var)
        init: i32.const 99936

Section 7: Export (198 bytes)
    Vector of Export (Length: 9):
        name: memory  Export type: memidx (0)
        name: __wasm_call_ctors  Export type: funcidx (9)
        name: __indirect_function_table  Export type: tableidx (0)
        name: run_from_js  Export type: funcidx (71)
        name: disassemble_from_js  Export type: funcidx (73)
        name: _emscripten_stack_restore  Export type: funcidx (250)
        name: _emscripten_stack_alloc  Export type: funcidx (251)
        name: emscripten_stack_get_current  Export type: funcidx (252)
        name: dynCall_jiji  Export type: funcidx (254)

Section 9: Element (61 bytes)
    Vector of Elem (Length: 1)
    tableidx: 0
    offset: i32.const 1
    vector of funcidx:  109  110  111  112  113  107  108  114  98  117  119  123  131  120  122  125  126  127  128  118  129  130  105  106  116  74  103  104  132  100  101  83  85  86  87  88  178  179  181  182  216  217  221
```

## Dependencies

- [FASM](https://flatassembler.net/)
- GCC with 32-bit support: Linux build only, for linking libc
- KolibriOS with console.obj:  KolibriOS build only

## Notes

The Linux build exists purely for development and testing. The KolibriOS build
is the actual target. Both builds share the same core parser in `src/core/` and
produce identical output,  only the platform interface differs.

