#if !defined(SCRAMBLE_RISCV_H)
#define SCRAMBLE_RISCV_H

#if defined(__riscv)

#define FUNCTION_scramble
#if defined(FUNCTION_scramble)

inline void scramble(FIXP_DBL x[], INT n) {
  FDK_ASSERT(!(((INT)x) & (ALIGNMENT_DEFAULT - 1)));
  asm volatile(
    "li      t0, 1\n"         // t0(m) = 1
    "addi    t1, %1, -1\n"    // t1 = n-1
    "li      t2, 0\n"         // t2(j) = 0

    "scramble_m_loop:\n"
    "mv      t3, %1\n"        // t3(k) = n

    "scramble_k_loop:\n"
    "srli    t3, t3, 1\n"     // k >>= 1
    "xor     t2, t2, t3\n"    // j ^= k
    "and     t4, t2, t3\n"    // t4 = j & k
    "beqz    t4, scramble_k_loop\n"  // if (j & k) break loop early

    "blt     t2, t0, scramble_m_loop_end\n"  // if (j < m) skip swapping

    "slli    t3, t0, 3\n"     // t3 = m * 8
    "slli    t4, t2, 3\n"     // t4 = j * 8

    "add     t5, %0, t3\n"    // t5 = &x[m]
    "add     t6, %0, t4\n"    // t6 = &x[j]

    "lw      a0, 0(t5)\n"     // a0 = x[m]
    "lw      a1, 4(t5)\n"     // a1 = x[m+1]
    "lw      a2, 0(t6)\n"     // a2 = x[j]
    "lw      a3, 4(t6)\n"    // a3 = x[j+1]

    "sw      a0, 0(t6)\n"     // x[j] = x[m]
    "sw      a1, 4(t6)\n"     // x[j+1] = x[m+1]
    "sw      a2, 0(t5)\n"     // x[m] = x[j]
    "sw      a3, 4(t5)\n"    // x[m+1] = x[j+1]

    "scramble_m_loop_end:\n"
    "addi    t0, t0, 1\n"     // m++
    "blt     t0, t1, scramble_m_loop\n"  // if (m < n-1) continue loop
    :
    : "r"(x), "r"(n)
    : "t0", "t1", "t2", "t3", "t4", "t5", "t6", "a0", "a1", "a2", "a3", "memory"
  );
}
#else
/* Force C implementation if no assembler version available. */
#undef FUNCTION_scramble

#endif /* defined(FUNCTION_scramble) */

#endif /* __riscv */

#endif /* !defined(SCRAMBLE_RISCV_H) */