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
        dd str_i32_lt_s
        dd str_i32_lt_u
        dd str_i32_gt_s
        dd str_i32_gt_u
        dd str_i32_le_s
        dd str_i32_le_u
        dd str_i32_ge_s
        dd str_i32_ge_u

        dd str_op_i64_eqz
        dd str_op_i64_eq
        dd str_op_i64_ne
        dd str_i64_lt_s
        dd str_i64_lt_u
        dd str_i64_gt_s
        dd str_i64_gt_u
        dd str_i64_le_s
        dd str_i64_le_u
        dd str_i64_ge_s
        dd str_i64_ge_u

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
        dd parse_br_table ; 0x0e
        dd parse_simple   ; 0x0f
        dd parse_op_u32    ; 0x10
        dd parse_call_indirect   ; 0x11 
        rept 8 { dd parse_error}  ; 0x12 - 0x
        dd parse_op_simple    ; 0x1a
        dd parse_op_simple    ; 0x1b
        rept 4 { dd parse_error}
        rept 5 { dd parse_op_u32 } ; 0x20 - 0x24
        rept 3 { dd parse_error }    0x25 - 0x27 Reserved
        rept 23 { dd parse_op_memarg } ; 0x28 - 0x3e
        dd parse_mem_inst
        dd parse_mem_inst
        dd parse_op_i32
        dd parse_op_i64
        dd parse_op_f32
        dd parse_op_f64
        rept 123 { dd parse_simple }

assert ($ - opcode_parse_table) = (192 * 4)
