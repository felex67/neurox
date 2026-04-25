#pragma once

#include <stdint.h>

#ifndef _WIN32
    #include <sys/types.h>
#endif //_WIN32

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

/**
 * @brief Структура преднастройки аллокатора задающая градации и количество блоков памяти
 * 
 * @property +est_size: size_t - Предполагаемый размер блока
 * @property +est_count: size_t - Предполагаемое количество блоков
 */
typedef struct FXGrade {
    /// Предполагаемый размер блока
    const size_t est_size;
    /// Предполагаемое количество блоков
    const size_t est_count;
} FXGrade;

/**
 * @brief Переменная для сохранения преднастроек пула памяти с ноль-терминантом
 * Определена в src/FXAlloc.c 
 */
extern const FXGrade* grades;

/**
 * @brief Функция выделения памяти
 * @param[in] _NBytes: size_t - Количество байт
 * @retval !0 - Кратный size_t указатель выровненный для любого типа данных
 * @retval NULL - В случае единственно возможной ошибки EBADALLOC результат сохранён в errno
 */
void* fxalloc(size_t _NBytes);

/**
 * @brief Высвобождает память выделенную исключительно fxalloc
 * @param[in] _Ptr: void*
 */
void fxfree(void* _Ptr);

#ifdef __cplusplus
}
#endif //__cplusplus