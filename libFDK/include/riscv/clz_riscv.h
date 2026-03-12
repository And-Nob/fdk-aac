#if !defined(CLZ_RISCV_H)
#define CLZ_RISCV_H

#if defined(__riscv)

#define FUNCTION_fixnormz_D
#define FUNCTION_fixnorm_D
#define FUNCTION_fixnormz_S
#define FUNCTION_fixnorm_S

#ifdef FUNCTION_fixnormz_D
inline int fixnormz_D(long value) {
  int result;

  asm volatile(".insn i 0x13, 1, %0, %1, 0x600" : "=r"(result) : "r"(value));

  return result;
}
#endif /* #ifdef FUNCTION_fixnormz_D */

#ifdef FUNCTION_fixnorm_D
inline INT fixnorm_D(LONG value) {
  if (!value) return 0;
  if (value < 0) value = ~value;
  return fixnormz_D(value) - 1;
}
#endif /* #ifdef FUNCTION_fixnorm_D */

#ifdef FUNCTION_fixnormz_S
inline INT fixnormz_S(SHORT value) {
  INT result;
  result = (LONG)(value << 16);
  if (result == 0)
    result = 16;
  else
    result = fixnormz_D(result);
  return result;
}
#endif /* #ifdef FUNCTION_fixnormz_S */

#ifdef FUNCTION_fixnorm_S
inline INT fixnorm_S(SHORT value) {
  LONG lvalue = (LONG)(value << 16);
  if (!lvalue) return 0;
  if (lvalue < 0) lvalue = ~lvalue;
  return fixnormz_D(lvalue) - 1;
}
#endif /* #ifdef FUNCTION_fixnorm_S */

#endif /* __riscv */

#endif /* !defined(CLZ_RISCV_H) */