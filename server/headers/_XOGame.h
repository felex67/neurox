#pragma once

#include "XOGame.h"


#ifndef OFFSETOF_CONSTEXPR
#define OFFSETOF_CONSTEXPR(type, member) \
    ((size_t)(&((type*)0)->member) - (size_t)0)
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    /// @brief Изменяемый клон XOGame
    typedef struct XOGameMutable {
        /// Идентификатор игры
        size_t id;
        /// Сделать ход.
        XORetCode (*make_move)(XOGame* _Game, int _CellX, int _CellY, XOPlayerSide _PlayerSide);
        void (*destruct)(XOGame* _Game);
        /// Игровое поле
        XOCell board[XO_BOARDX][XO_BOARDY];
        /// Лог ходов
        XOCell log[XO_BOARDX * XO_BOARDY];
        /// Выигравшие клетки. По-умолчанию - { 0 }
        XOCell winners[XO_BOARDX];
        /// Текущий ход начиная с 0
        uint8_t turn;
        /// Выравнивающие байты - { 0 }.
        uint8_t padding[2];
    } XOGameMutable;


    XORetCode xogame_make_move(XOGame* _Game, int _CellX, int _CellY, XOPlayerSide _PlayerSide);
    XORetCode xogame_make_move_original_fast(XOGame* _Game, int _CellX, int _CellY, XOPlayerSide _PlayerSide);
    void xogame_destruct(XOGame* _Game);

// Статические проверки ПОЛНОЙ БИНАРНОЙ СОВМЕСТИМОСТИ XOGame и XOGameMutable
_Static_assert(sizeof(XOGame) == sizeof(XOGameMutable), "XOGame and XOGameMutable must have the same size");
_Static_assert(_Alignof(XOGame) == _Alignof(XOGameMutable), "XOGame and XOGameMutable must have the same alignment");

// Проверка смещений полей
_Static_assert(OFFSETOF_CONSTEXPR(XOGame, make_move) == OFFSETOF_CONSTEXPR(XOGameMutable, make_move), "Field 'make_move' must have the same offset in both structures");
_Static_assert(OFFSETOF_CONSTEXPR(XOGame, destruct) == OFFSETOF_CONSTEXPR(XOGameMutable, destruct), "Field 'destruct' must have the same offset in both structures");
_Static_assert(OFFSETOF_CONSTEXPR(XOGame, board) == OFFSETOF_CONSTEXPR(XOGameMutable, board), "Field 'board' must have the same offset in both structures");
_Static_assert(OFFSETOF_CONSTEXPR(XOGame, log) == OFFSETOF_CONSTEXPR(XOGameMutable, log), "Field 'log' must have the same offset in both structures");
_Static_assert(OFFSETOF_CONSTEXPR(XOGame, winners) == OFFSETOF_CONSTEXPR(XOGameMutable, winners), "Field 'winners' must have the same offset in both structures");
_Static_assert(OFFSETOF_CONSTEXPR(XOGame, turn) == OFFSETOF_CONSTEXPR(XOGameMutable, turn), "Field 'turn' must have the same offset in both structures");
_Static_assert(OFFSETOF_CONSTEXPR(XOGame, padding) == OFFSETOF_CONSTEXPR(XOGameMutable, padding), "Field 'padding' must have the same offset in both structures");

// Проверка размеров полей, это не тоже самое что и смещение!!!
_Static_assert(sizeof(((XOGame*)0)->make_move) == sizeof(((XOGameMutable*)0)->make_move), "Field 'make_move' must have the same size in both structures");
_Static_assert(sizeof(((XOGame*)0)->destruct) == sizeof(((XOGameMutable*)0)->destruct), "Field 'destruct' must have the same size in both structures");
_Static_assert(sizeof(((XOGame*)0)->board) == sizeof(((XOGameMutable*)0)->board), "Field 'board' must have the same size in both structures");
_Static_assert(sizeof(((XOGame*)0)->log) == sizeof(((XOGameMutable*)0)->log), "Field 'log' must have the same size in both structures");
_Static_assert(sizeof(((XOGame*)0)->winners) == sizeof(((XOGameMutable*)0)->winners), "Field 'winners' must have the same size in both structures");
_Static_assert(sizeof(((XOGame*)0)->turn) == sizeof(((XOGameMutable*)0)->turn), "Field 'turn' must have the same size in both structures");
_Static_assert(sizeof(((XOGame*)0)->padding) == sizeof(((XOGameMutable*)0)->padding), "Field 'padding' must have the same size in both structures");

#ifdef __cplusplus
}
#endif // __cplusplus



