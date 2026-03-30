; valtype
str_i32         db "i32", 0
str_i64         db "i64", 0
str_f32         db "f32", 0
str_f64         db "f64", 0
valtype:
  dd VAL_I32, str_i32
        dd VAL_I64, str_i64
  dd VAL_F32, str_f32
  dd VAL_F64, str_f64
  dd 0

str_op_unreachable      db "unreachable", 0
str_op_nop              db "nop", 0
str_op_block            db "block", 0
str_op_loop             db "loop", 0
str_op_if               db "if", 0
str_op_br               db "br", 0
str_op_br_if            db "br_if", 0
str_op_br_table         db "br_table", 0
str_op_return           db "return", 0
str_op_call             db "call", 0
str_op_call_indirect    db "call_indirect", 0
str_op_drop             db "drop", 0
str_op_select           db "select", 0
str_op_local_get        db "local.get", 0
str_op_local_set        db "local.set", 0
str_op_local_tee        db "local.tee", 0
str_op_global_get       db "global.get", 0
str_op_global_set       db "global.set", 0
str_op_i32_load         db "i32.load", 0
str_op_i64_load         db "i64.load", 0
str_op_f32_load         db "f32.load", 0
str_op_f64_load         db "f64.load", 0
str_op_i32_load8_s      db "i32.load8_s", 0
str_op_i32_load8_u      db "i32.load8_u", 0
str_op_i32_load16_s     db "i32.load16_s", 0
str_op_i32_load16_u     db "i32.load16_u", 0
str_op_i64_load8_s      db "i64.load8_s", 0
str_op_i64_load8_u      db "i64.load8_u", 0
str_op_i64_load16_s     db "i64.load16_s", 0
str_op_i64_load16_u     db "i64.load16_u", 0
str_op_i64_load32_s     db "i64.load32_s", 0
str_op_i64_load32_u     db "i64.load32_u", 0
str_op_i32_store        db "i32.store", 0
str_op_i64_store        db "i64.store", 0
str_op_f32_store        db "f32.store", 0
str_op_f64_store        db "f64.store", 0
str_op_i32_store8       db "i32.store8", 0
str_op_i32_store16      db "i32.store16", 0
str_op_i64_store8       db "i64.store8", 0
str_op_i64_store16      db "i64.store16", 0
str_op_i64_store32      db "i64.store32", 0
str_op_memory_size      db "memory.size", 0
str_op_memory_grow      db "memory.grow", 0
str_op_i32_const        db "i32.const", 0
str_op_i64_const        db "i64.const", 0
str_op_f32_const        db "f32.const", 0
str_op_f64_const        db "f64.const", 0
str_op_i32_eqz         db "i32.eqz", 0
str_op_i32_eq          db "i32.eq", 0
str_op_i32_ne          db "i32.ne", 0
str_op_i32_lt_s           db "i32.lt_s", 0
str_op_i32_lt_u           db "i32.lt_u", 0
str_op_i32_gt_s           db "i32.gt_s", 0
str_op_i32_gt_u           db "i32.gt_u", 0
str_op_i32_le_s           db "i32.le_s", 0
str_op_i32_le_u           db "i32.le_u", 0
str_op_i32_ge_s           db "i32.ge_s", 0
str_op_i32_ge_u           db "i32.ge_u", 0
str_op_i64_eqz         db "i64.eqz", 0
str_op_i64_eq          db "i64.eq", 0
str_op_i64_ne          db "i64.ne", 0
str_op_i64_lt_s           db "i64.lt_s", 0
str_op_i64_lt_u           db "i64.lt_u", 0
str_op_i64_gt_s           db "i64.gt_s", 0
str_op_i64_gt_u           db "i64.gt_u", 0
str_op_i64_le_s           db "i64.le_s", 0
str_op_i64_le_u           db "i64.le_u", 0
str_op_i64_ge_s           db "i64.ge_s", 0
str_op_i64_ge_u           db "i64.ge_u", 0
str_op_f32_eq          db "f32.eq", 0
str_op_f32_ne          db "f32.ne", 0
str_op_f32_lt          db "f32.lt", 0
str_op_f32_gt          db "f32.gt", 0
str_op_f32_le          db "f32.le", 0
str_op_f32_ge          db "f32.ge", 0
str_op_f64_eq          db "f64.eq", 0
str_op_f64_ne          db "f64.ne", 0
str_op_f64_lt          db "f64.lt", 0
str_op_f64_gt          db "f64.gt", 0
str_op_f64_le          db "f64.le", 0
str_op_f64_ge          db "f64.ge", 0
str_op_i32_clz         db "i32.clz", 0
str_op_i32_ctz         db "i32.ctz", 0
str_op_i32_popcnt      db "i32.popcnt", 0
str_op_i32_add         db "i32.add", 0
str_op_i32_sub         db "i32.sub", 0
str_op_i32_mul         db "i32.mul", 0
str_op_i32_div_s       db "i32.div_s", 0
str_op_i32_div_u       db "i32.div_u", 0
str_op_i32_rem_s       db "i32.rem_s", 0
str_op_i32_rem_u       db "i32.rem_u", 0
str_op_i32_and         db "i32.and", 0
str_op_i32_or          db "i32.or", 0
str_op_i32_xor         db "i32.xor", 0
str_op_i32_shl         db "i32.shl", 0
str_op_i32_shr_s       db "i32.shr_s", 0
str_op_i32_shr_u       db "i32.shr_u", 0
str_op_i32_rotl        db "i32.rotl", 0
str_op_i32_rotr        db "i32.rotr", 0
str_op_i64_clz         db "i64.clz", 0
str_op_i64_ctz         db "i64.ctz", 0
str_op_i64_popcnt      db "i64.popcnt", 0
str_op_i64_add         db "i64.add", 0
str_op_i64_sub         db "i64.sub", 0
str_op_i64_mul         db "i64.mul", 0
str_op_i64_div_s       db "i64.div_s", 0
str_op_i64_div_u       db "i64.div_u", 0
str_op_i64_rem_s       db "i64.rem_s", 0
str_op_i64_rem_u       db "i64.rem_u", 0
str_op_i64_and         db "i64.and", 0
str_op_i64_or          db "i64.or", 0
str_op_i64_xor         db "i64.xor", 0
str_op_i64_shl         db "i64.shl", 0
str_op_i64_shr_s       db "i64.shr_s", 0
str_op_i64_shr_u       db "i64.shr_u", 0
str_op_i64_rotl        db "i64.rotl", 0
str_op_i64_rotr        db "i64.rotr", 0
str_op_f32_abs         db "f32.abs", 0
str_op_f32_neg         db "f32.neg", 0
str_op_f32_ceil        db "f32.ceil", 0
str_op_f32_floor       db "f32.floor", 0
str_op_f32_trunc       db "f32.trunc", 0
str_op_f32_nearest     db "f32.nearest", 0
str_op_f32_sqrt        db "f32.sqrt", 0
str_op_f32_add         db "f32.add", 0
str_op_f32_sub         db "f32.sub", 0
str_op_f32_mul         db "f32.mul", 0
str_op_f32_div         db "f32.div", 0
str_op_f32_min         db "f32.min", 0
str_op_f32_max         db "f32.max", 0
str_op_f32_copysign    db "f32.copysign", 0
str_op_f64_abs         db "f64.abs", 0
str_op_f64_neg         db "f64.neg", 0
str_op_f64_ceil        db "f64.ceil", 0
str_op_f64_floor       db "f64.floor", 0
str_op_f64_trunc       db "f64.trunc", 0
str_op_f64_nearest     db "f64.nearest", 0
str_op_f64_sqrt        db "f64.sqrt", 0
str_op_f64_add         db "f64.add", 0
str_op_f64_sub         db "f64.sub", 0
str_op_f64_mul         db "f64.mul", 0
str_op_f64_div         db "f64.div", 0
str_op_f64_min         db "f64.min", 0
str_op_f64_max         db "f64.max", 0
str_op_f64_copysign    db "f64.copysign", 0
str_op_i32_wrap_i64         db "i32.wrap_i64", 0
str_op_i32_trunc_f32_s      db "i32.trunc_f32_s", 0
str_op_i32_trunc_f32_u      db "i32.trunc_f32_u", 0
str_op_i32_trunc_f64_s      db "i32.trunc_f64_s", 0
str_op_i32_trunc_f64_u      db "i32.trunc_f64_u", 0
str_op_i64_extend_i32_s     db "i64.extend_i32_s", 0
str_op_i64_extend_i32_u     db "i64.extend_i32_u", 0
str_op_i64_trunc_f32_s      db "i64.trunc_f32_s", 0
str_op_i64_trunc_f32_u      db "i64.trunc_f32_u", 0
str_op_i64_trunc_f64_s      db "i64.trunc_f64_s", 0
str_op_i64_trunc_f64_u      db "i64.trunc_f64_u", 0
str_op_f32_convert_i32_s    db "f32.convert_i32_s", 0
str_op_f32_convert_i32_u    db "f32.convert_i32_u", 0
str_op_f32_convert_i64_s    db "f32.convert_i64_s", 0
str_op_f32_convert_i64_u    db "f32.convert_i64_u", 0
str_op_f32_demote_f64       db "f32.demote_f64", 0
str_op_f64_convert_i32_s    db "f64.convert_i32_s", 0
str_op_f64_convert_i32_u    db "f64.convert_i32_u", 0
str_op_f64_convert_i64_s    db "f64.convert_i64_s", 0
str_op_f64_convert_i64_u    db "f64.convert_i64_u", 0
str_op_f64_promote_f32      db "f64.promote_f32", 0
str_op_i32_reinterpret_f32  db "i32.reinterpret_f32", 0
str_op_i64_reinterpret_f64  db "i64.reinterpret_f64", 0
str_op_f32_reinterpret_i32  db "f32.reinterpret_i32", 0
str_op_f64_reinterpret_i64  db "f64.reinterpret_i64", 0
str_invalid                 db "<invalid>", 0

opcode_str_table:
        dd str_op_unreachable 
        dd str_op_nop
        dd str_op_block
        dd str_op_loop
        dd str_op_if
        rept 7 { dd str_invalid } ; shouldn't be printed

        dd str_op_br
        dd str_op_br_if
        dd str_op_br_table
        dd str_op_return
        dd str_op_call 
        dd str_op_call_indirect
        rept 8 { dd str_invalid }

        dd str_op_drop
        dd str_op_select
        rept 4 { dd str_invalid }

        dd str_op_local_get 
        dd str_op_local_set 
        dd str_op_local_tee
        dd str_op_global_get
        dd str_op_global_set
        rept 3 {dd str_invalid}

        dd str_op_i32_load
        dd str_op_i64_load
        dd str_op_f32_load
        dd str_op_f64_load
        dd str_op_i32_load8_s
        dd str_op_i32_load8_u
        dd str_op_i32_load16_s
        dd str_op_i32_load16_u

        dd str_op_i64_load8_s
        dd str_op_i64_load8_u
        dd str_op_i64_load16_s
        dd str_op_i64_load16_u
        dd str_op_i64_load32_s
        dd str_op_i64_load32_u

        dd str_op_i32_store
        dd str_op_i64_store
        dd str_op_f32_store
        dd str_op_f64_store
        dd str_op_i32_store8
        dd str_op_i32_store16
        dd str_op_i64_store8
        dd str_op_i64_store16
        dd str_op_i64_store32
        dd str_op_memory_size
        dd str_op_memory_grow
        dd str_op_i32_const
        dd str_op_i64_const
        dd str_op_f32_const
        dd str_op_f64_const

        dd str_op_i32_eqz
        dd str_op_i32_eq
        dd str_op_i32_ne
        dd str_op_i32_lt_s
        dd str_op_i32_lt_u
        dd str_op_i32_gt_s
        dd str_op_i32_gt_u
        dd str_op_i32_le_s
        dd str_op_i32_le_u
        dd str_op_i32_ge_s
        dd str_op_i32_ge_u

        dd str_op_i64_eqz
        dd str_op_i64_eq
        dd str_op_i64_ne
        dd str_op_i64_lt_s
        dd str_op_i64_lt_u
        dd str_op_i64_gt_s
        dd str_op_i64_gt_u
        dd str_op_i64_le_s
        dd str_op_i64_le_u
        dd str_op_i64_ge_s
        dd str_op_i64_ge_u

        dd str_op_f32_eq
        dd str_op_f32_ne
        dd str_op_f32_lt
        dd str_op_f32_gt
        dd str_op_f32_le
        dd str_op_f32_ge

        dd str_op_f64_eq
        dd str_op_f64_ne
        dd str_op_f64_lt
        dd str_op_f64_gt
        dd str_op_f64_le
        dd str_op_f64_ge

        dd str_op_i32_clz
        dd str_op_i32_ctz
        dd str_op_i32_popcnt
        dd str_op_i32_add
        dd str_op_i32_sub
        dd str_op_i32_mul
        dd str_op_i32_div_s
        dd str_op_i32_div_u
        dd str_op_i32_rem_s
        dd str_op_i32_rem_u
        dd str_op_i32_and
        dd str_op_i32_or
        dd str_op_i32_xor
        dd str_op_i32_shl
        dd str_op_i32_shr_s
        dd str_op_i32_shr_u
        dd str_op_i32_rotl
        dd str_op_i32_rotr

        dd str_op_i64_clz
        dd str_op_i64_ctz
        dd str_op_i64_popcnt
        dd str_op_i64_add
        dd str_op_i64_sub
        dd str_op_i64_mul
        dd str_op_i64_div_s
        dd str_op_i64_div_u
        dd str_op_i64_rem_s
        dd str_op_i64_rem_u
        dd str_op_i64_and
        dd str_op_i64_or
        dd str_op_i64_xor
        dd str_op_i64_shl
        dd str_op_i64_shr_s
        dd str_op_i64_shr_u
        dd str_op_i64_rotl
        dd str_op_i64_rotr

        dd str_op_f32_abs
        dd str_op_f32_neg
        dd str_op_f32_ceil
        dd str_op_f32_floor
        dd str_op_f32_trunc
        dd str_op_f32_nearest
        dd str_op_f32_sqrt
        dd str_op_f32_add
        dd str_op_f32_sub
        dd str_op_f32_mul
        dd str_op_f32_div
        dd str_op_f32_min
        dd str_op_f32_max
        dd str_op_f32_copysign

        dd str_op_f64_abs
        dd str_op_f64_neg
        dd str_op_f64_ceil
        dd str_op_f64_floor
        dd str_op_f64_trunc
        dd str_op_f64_nearest
        dd str_op_f64_sqrt
        dd str_op_f64_add
        dd str_op_f64_sub
        dd str_op_f64_mul
        dd str_op_f64_div
        dd str_op_f64_min
        dd str_op_f64_max
        dd str_op_f64_copysign

        dd str_op_i32_wrap_i64
        dd str_op_i32_trunc_f32_s
        dd str_op_i32_trunc_f32_u
        dd str_op_i32_trunc_f64_s
        dd str_op_i32_trunc_f64_u
        dd str_op_i64_extend_i32_s
        dd str_op_i64_extend_i32_u
        dd str_op_i64_trunc_f32_s
        dd str_op_i64_trunc_f32_u
        dd str_op_i64_trunc_f64_s
        dd str_op_i64_trunc_f64_u
        dd str_op_f32_convert_i32_s
        dd str_op_f32_convert_i32_u
        dd str_op_f32_convert_i64_s
        dd str_op_f32_convert_i64_u
        dd str_op_f32_demote_f64
        dd str_op_f64_convert_i32_s
        dd str_op_f64_convert_i32_u
        dd str_op_f64_convert_i64_s
        dd str_op_f64_convert_i64_u
        dd str_op_f64_promote_f32
        dd str_op_i32_reinterpret_f32
        dd str_op_i64_reinterpret_f64
        dd str_op_f32_reinterpret_i32
        dd str_op_f64_reinterpret_i64

assert ($ - opcode_str_table) = (192 * 4)

opcode_parse_table:
        dd parse_op_simple ;0x00
        dd parse_op_simple ; 0x01
        dd parse_op_block  ; 0x02
        dd parse_op_block  ; 0x03
        dd parse_op_if  ; 0x04
        rept 7 { dd parse_error }; no opcode taken or opcode are part of other opcode 
        dd parse_op_u32   ; 0x0c
        dd parse_op_u32    ; 0x0d
        dd parse_op_br_table ; 0x0e
        dd parse_op_simple   ; 0x0f
        dd parse_op_u32    ; 0x10
        dd parse_call_indirect   ; 0x11 
        rept 8 { dd parse_error}  ; 0x12 - 0x
        dd parse_op_simple    ; 0x1a
        dd parse_op_simple    ; 0x1b
        rept 4 { dd parse_error}
        rept 5 { dd parse_op_u32 } ; 0x20 - 0x24
        rept 3 { dd parse_error } ;   0x25 - 0x27 Reserved
        rept 23 { dd parse_op_memarg } ; 0x28 - 0x3e
        dd parse_mem_inst
        dd parse_mem_inst
        dd parse_op_i32
        dd parse_op_i64
        dd parse_op_f32
        dd parse_op_f64
        rept 123 { dd parse_op_simple }

assert ($ - opcode_parse_table) = (192 * 4)
