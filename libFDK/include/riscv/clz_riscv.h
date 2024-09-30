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

    // asm volatile (
    //     "li       %0, 0                    \n"  // Initialize leadingBits to 0
    //     "not      t1, %1                   \n"  // Perform bitwise NOT on 'result'
    //     "loop%=:                             \n"
    //     "bgez     t1, end%=                  \n"  // If MSB is 0 (a is non-negative), break loop
    //     "slli     t1, t1, 1                \n"  // Shift 'a' left by 1 bit (store result in t1)
    //     "addi     %0, %0, 1                \n"  // Increment leadingBits
    //     "j        loop%=                     \n"  // Repeat the loop
    //     "end%=:                              \n"
    //     : "=&r" (result) // Output operands
    //     : "r" (value)
    //     : "t1"                                         
    // );

    asm volatile(
        // R_TYPE_INSTR(_f7, _rs2, _rs1, _f3, _rd, _opc)
        // .word (((_f7) << 25) | ((_rs2) << 20) | ((_rs1) << 15) | ((_f3) << 12) | ((_rd) << 7) | (_opc))
        "mv a0, %1 \n"
        ".word (((0b0110000) << 25) | ((0b00000) << 20) | ((10) << 15) | ((0b001) << 12) | ((11) << 7) | (0b0010011)) \n" // a0 is register 10, a1 is register 11
        "mv %0, a1 \n"
        : "=r" (result) // output
        : "r" (value) // input
        : "a0", "a1"
    );

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