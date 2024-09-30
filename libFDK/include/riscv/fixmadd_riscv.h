#if !defined(FIXMADD_RISCV_H)
#define FIXMADD_RISCV_H

#if defined(__riscv)

#define FUNCTION_fixmadddiv2_DD
#ifdef FUNCTION_fixmadddiv2_DD
inline FIXP_DBL fixmadddiv2_DD(FIXP_DBL x, const FIXP_DBL a, const FIXP_DBL b) {
  INT result;
  asm("mulh %0, %1, %2\n"
      "add  %0, %3, %0"
      : "=&r"(result)
      : "r"(a), "r"(b), "r"(x));
  return result;
}
#endif /* #ifdef FUNCTION_fixmadddiv2_DD */

#define FUNCTION_fixmsubdiv2_DD
#ifdef FUNCTION_fixmsubdiv2_DD
inline FIXP_DBL fixmsubdiv2_DD(FIXP_DBL x, const FIXP_DBL a, const FIXP_DBL b) {
  INT result;
  asm("mulh %0, %1, %2\n"
      "sub  %0, %3, %0"
      : "=&r"(result)
      : "r"(a), "r"(b), "r"(x));
  return result;
}
#endif /* #ifdef FUNCTION_fixmsubdiv2_DD */

#define FUNCTION_fixmadddiv2BitExact_DD
#ifdef FUNCTION_fixmadddiv2BitExact_DD
#define fixmadddiv2BitExact_DD(a, b, c) fixmadddiv2_DD(a, b, c)
#endif /* #ifdef FUNCTION_fixmadddiv2BitExact_DD */

#define FUNCTION_fixmsubdiv2BitExact_DD
#ifdef FUNCTION_fixmsubdiv2BitExact_DD
inline FIXP_DBL fixmsubdiv2BitExact_DD(FIXP_DBL x, const FIXP_DBL a,
                                       const FIXP_DBL b) {
  return x - fixmuldiv2BitExact_DD(a, b);
}
#endif /* #ifdef FUNCTION_fixmsubdiv2BitExact_DD */

#define FUNCTION_fixmadddiv2BitExact_DS
#ifdef FUNCTION_fixmadddiv2BitExact_DS
#define fixmadddiv2BitExact_DS(a, b, c) fixmadddiv2_DS(a, b, c)
#endif /* #ifdef FUNCTION_fixmadddiv2BitExact_DS */

#define FUNCTION_fixmsubdiv2BitExact_DS
#ifdef FUNCTION_fixmsubdiv2BitExact_DS
inline FIXP_DBL fixmsubdiv2BitExact_DS(FIXP_DBL x, const FIXP_DBL a,
                                       const FIXP_SGL b) {
  return x - fixmuldiv2BitExact_DS(a, b);
}
#endif /* #ifdef FUNCTION_fixmsubdiv2BitExact_DS */

#endif /* __riscv */

#endif /* !defined(FIXMADD_RISCV_H) */