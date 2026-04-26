#ifndef FX_MEMORY_BLOCK_H
#define FX_MEMORY_BLOCK_H

#include <stdint.h>
#include "mword.h"

// Определяем оптимальный тип метаданных для FXMemoryBlock
#if defined(__x86_64__) || defined(_M_X64) || \
    defined(__amd64__) || defined(__amd64) || \
    defined(__aarch64__) || defined(_M_ARM64) || \
    defined(__AARCH64__) || defined(__powerpc64__) || \
    defined(__ppc64__)
    // Для 64-битных архитектур используем uint32_t
    // для оптимального баланса между размером и производительностью
    typedef uint32_t fxmbmeta_t;

#elif defined(__i386__) || defined(_M_IX86) || \
      defined(__i486__) || defined(__i586__) || \
      defined(__i686__) || defined(__arm__) || \
      defined(_M_ARM) || defined(__ARM_ARCH_7__) || \
      defined(__ARM_ARCH_8__) || defined(__powerpc__) || \
      defined(__ppc__)
    // Для 32-битных архитектур используем uint32_t
    typedef uint32_t fxmbmeta_t;

#elif defined(__riscv)
    #if __riscv_xlen == 64
        typedef uint32_t fxmbmeta_t;
    #elif __riscv_xlen == 32
        typedef uint32_t fxmbmeta_t;
    #else
        #error "Unsupported RISC-V word size: __riscv_xlen must be 32 or 64"
    #endif

#else
    // Резервный вариант: определяем по размеру указателя
    #if sizeof(void*) == 8
        typedef uint32_t fxmbmeta_t;
    #elif sizeof(void*) == 4
        typedef uint32_t fxmbmeta_t;
    #else
        #error "Unsupported pointer size"
    #endif
#endif

// Проверка корректности определения типа
static_assert(sizeof(fxmbmeta_t) == 4, "fxmbmeta_t must be 32-bit");

#endif // FX_MEMORY_BLOCK_H
