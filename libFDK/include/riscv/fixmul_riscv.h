#if !defined(FIXMUL_RISCV_H)
#define FIXMUL_RISCV_H

#if defined(__riscv)

#define FUNCTION_fixmul_DD
#define FUNCTION_fixmuldiv2_DD

#define FUNCTION_fixmuldiv2BitExact_DD
#define fixmuldiv2BitExact_DD(a, b) fixmuldiv2_DD(a, b)

#define FUNCTION_fixmulBitExact_DD
#define fixmulBitExact_DD(a, b) fixmul_DD(a, b)

#define FUNCTION_fixmuldiv2BitExact_DS
#define fixmuldiv2BitExact_DS(a, b) fixmuldiv2_DS(a, b)

#define FUNCTION_fixmulBitExact_DS
#define fixmulBitExact_DS(a, b) fixmul_DS(a, b)

inline INT fixmul_DD(INT a, const INT b) {
    INT result;

    asm volatile (
        "mulh %0, %1, %2;\n"
        "slli %0, %0, 1;\n"
        : "=r" (result)
        : "r" (a), "r" (b)
    );
    return result;
}

inline INT fixmuldiv2_DD(INT a, const INT b) {
    INT result;

    asm volatile (
        "mulh %0, %1, %2;\n"
        : "=r" (result)
        : "r" (a), "r" (b)
    );
    return result;
}

#endif /* __riscv */

#endif /* !defined(FIXMUL_RISCV_H) */