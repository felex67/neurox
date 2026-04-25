#pragma once

#include "FXAlloc.h"

#include "mword.h"

typedef struct FXMemoryBlock FXMemoryBlock;

/**
 * @brief Минимальная структурная единица - блок памяти
 * В памяти расположены друг за другом с гарантированным выравниванием по void*
 * Клиентский указатель указывает непосредственно за структуру
 * fxalloc() → return (void*)(block + 1);
 * fxfree() → FXMemoryBlock* block = (FXMemoryBlock*)_Ptr - 1;
 * @property next: FXMemoryBlock* - Указатель на следующий свободный блок
 * @property Индекс потока в глобальном пуле
 * @property Индекс грейда в пуле конкретного потока
 * */
struct FXMemoryBlock {
    /// @brief Указатель на следующий свободный блок
    FXMemoryBlock* next;
    /// @brief Индекс потока в глобальном пуле
    umword_t tid;
    /// @brief Индекс грейда в пуле конкретного потока
    umword_t gid;
};

struct FXMemoryBlock {
    /// @brief Указатель на следующий свободный блок
    FXMemoryBlock* next;
    /// @brief Индекс потока в глобальном пуле
    uint32_t tid;
    /// @brief Индекс грейда в пуле конкретного потока
    uint32_t gid;
};

/**
 * @brief Минимальная структурная единица - блок памяти
 * В памяти расположены друг за другом с гарантированным выравниванием по void*
 * Клиентский указатель указывает непосредственно за структуру
 * fxalloc() → return (void*)(block + 1);
 * fxfree() → FXMemoryBlock* block = (FXMemoryBlock*)_Ptr - 1;
 * @property next: FXMemoryBlock* - Указатель на следующий свободный блок
 * @property Индекс потока в глобальном пуле
 * @property Индекс грейда в пуле конкретного потока
 * */
struct FXMemoryBlock {
    /// @brief Указатель на следующий свободный блок
    FXMemoryBlock* next;
    /// @brief Полезные данные в блоке
    uint32_t used;
    /// @brief Индекс потока в глобальном пуле
    uint16_t tid;
    /// @brief Индекс грейда в пуле конкретного потока
    uint16_t gid;
};

/// @brief Группа блоков одной градации
typedef struct FXGradedMemoryPool {
    /// @brief Указатель на последний свободный блок
    FXMemoryBlock* free;
    /// @brief Всего блоков в данной группе
    umword_t total;
    /// @brief Количество преаллоцированных блоков
    umword_t count_pre;
    /// @brief Количество используемых блоков
    mword_t used;
    /// @brief Количество свободных блоков
    mword_t free;
} FXMemoryPoolGrade;