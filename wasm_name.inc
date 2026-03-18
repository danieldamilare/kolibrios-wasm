str_i32 db "i32", 0
str_i64 db "i64", 0
str_f32 db "f32", 0
str_f64 db "f64", 0

valtype:
  dd VAL_I32, str_i32
  dd VAL_I64, str_i64
  dd VAL_F32, str_f32
  dd VAL_F64, str_f64
  dd 0


