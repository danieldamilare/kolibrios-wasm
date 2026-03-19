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
- Fully parses the type section: functypes, params, and results
- Uses leb128 u32 decoding to decode size as specified in the spec
- Skips all other sections cleanly using their size fields
- Prints custom section names
- Validates section boundaries

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

Section 2: Import (260 bytes) - Skipping
Section 3: Function (249 bytes) - Skipping
Section 4: Table (4 bytes) - Skipping
Section 5: Memory (6 bytes) - Skipping
Section 6: Global (8 bytes) - Skipping
Section 7: Export (198 bytes) - Skipping
Section 9: Element (61 bytes) - Skipping
Section 10: Code (65696 bytes) - Skipping
Section 11: Data (15418 bytes) - Skipping

Section 0: Custom (5398 bytes)
   name: name
Section 0: Custom (21868 bytes)
   name: .debug_abbrev
Section 0: Custom (98903 bytes)
   name: .debug_info

Successfully parsed wasm binary
```

## Dependencies

- [FASM](https://flatassembler.net/)
- GCC with 32-bit support: Linux build only, for linking libc
- KolibriOS with console.obj:  KolibriOS build only

## Notes

The Linux build exists purely for development and testing. The KolibriOS build
is the actual target. Both builds share the same core parser in `src/core/` and
produce identical output,  only the platform interface differs.

This project is being developed as a GSoC 2026 contribution for KolibriOS.
