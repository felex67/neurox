#pragma once

#include <stdint.h>

#if defined(__x86_64__) || defined(_M_X64) || \
    defined(__amd64__) || defined(__amd64)
    // x64: 64-битное машинное слово
    typedef int64_t mword_t;
    typedef uint64_t umword_t;

#elif defined(__i386__) || defined(_M_IX86) || \
      defined(__i486__) || defined(__i586__) || \
      defined(__i686__)
    // x86: 32-битное машинное слово
    typedef int32_t mword_t;
    typedef uint32_t umword_t;

#elif defined(__aarch64__) || defined(_M_ARM64) || defined(__AARCH64__)
    // ARM64: 64-битное машинное слово
    typedef int64_t mword_t;
    typedef uint64_t umword_t;

#elif defined(__arm__) || defined(_M_ARM) || defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_8__)
    // ARM32: 32-битное машинное слово
    typedef int32_t mword_t;
    typedef uint32_t umword_t;

#elif defined(__riscv) && defined(__riscv_xlen)
    #if __riscv_xlen == 64
        // RISC‑V 64: 64-битное машинное слово
        typedef int64_t mword_t;
        typedef uint64_t umword_t;
    #elif __riscv_xlen == 32
        // RISC‑V 32: 32-битное машинное слово
        typedef int32_t mword_t;
        typedef uint32_t umword_t;
    #else
        #error "Unsupported RISC-V word size: __riscv_xlen must be 32 or 64"
    #endif

#elif defined(__powerpc64__) || defined(__ppc64__)
    // PowerPC64: 64-битное машинное слово
    typedef int64_t mword_t;
    typedef uint64_t umword_t;

#elif defined(__powerpc__) || defined(__ppc__)
    // PowerPC32: 32-битное машинное слово
    typedef int32_t mword_t;
    typedef uint32_t umword_t;


#else
    // Резервный вариант: определяем по диапазону unsigned long
    #include <limits.h>
    #if ULONG_MAX == 18446744073709551615ULL  // 2^64 - 1
        typedef int64_t mword_t;
        typedef uint64_t umword_t;
    #elif ULONG_MAX == 4294967295UL  // 2^32 - 1
        typedef int32_t mword_t;
        typedef uint32_t umword_t;
    #elif ULONG_MAX == 65535U  // 2^16 - 1
        typedef int16_t mword_t;
        typedef uint16_t umword_t;
    #else
        #error "Cannot determine machine word size: unsupported ULONG_MAX"
    #endif
#endif

/* Проверки добавлены по настоянию YandexGPT 5.1 Pro(АлисаAI) */
// Статическая проверка: размер слова — степень двойки
static_assert((sizeof(mword_t) & (sizeof(mword_t) - 1)) == 0, "Machine word size must be a power of two");

// Статическая проверка: signed и unsigned версии имеют одинаковый размер
static_assert(sizeof(mword_t) == sizeof(umword_t), "mword_t and umword_t must have the same size");