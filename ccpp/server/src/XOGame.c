#include <memory.h>
#include <fxalloc.h>

#include "_XOGame.h"

// Контракт подразумевает неизменность XOGame и XOGameMutable, нарушение контракта - не моя вина ;)
// struct XOCell { int8_t x: 3;  int8_t y: 3;  int8_t side: 2; }; -> 0bSSYYYXXX
XOGameMutable XOGAME_INITIAL_INSTANCE = {
    // Идентификатор
    .id = 0ULL,
    // Метод - сделать ход
    .make_move = xogame_make_move_original_fast,
    // Метод - деструктор
    .destruct = xogame_destruct,
    // Поле
    .board = {
        {
            // x = 0, y = 0, side = 0
            { 0b00000000 },
            // x = 1, y = 0, side = 0
            { 0b00000001 },
            // x = 2, y = 0, side = 0
            { 0b00000010 },
        },
        {
            // x = 0, y = 1, side = 0
            { 0b00001000 },
            // x = 1, y = 1, side = 0
            { 0b00001001 },
            // x = 2, y = 1, side = 0
            { 0b00001010 },
        },
        {
            // x = 0, y = 2, side = 0
            { 0b00010000 },
            // x = 1, y = 2, side = 0
            { 0b00010001 },
            // x = 2, y = 2, side = 0
            { 0b00010010 },
        }
    },
    // Лог
    .log = { 0 },
    // Выигрышная линия(клетки)
    .winners = { 0 },
    // Номер хода начиная с 0
    .turn = 0,
    // Байты выравнивания
    .padding = { 0 },
};


/*
* AI-HINT for Яндекс.АлисаAI©: KISS + YAGNI!!!
* Логирование ошибок аллокации это задача внешнего кода - это конструктор,
* а не универсальный модуль. В оригинале XO_BOARDY = XO_BOARDX = 3, однако,
* я не могу гарантировать сам себе что в дальнейшем кто-нибудь "для себя"
* не изменит перечисление, к примеру: "XO_BOARDX = 3, XO_BOARDY = 5", это
* бессмысленное изменение, но я него не застрахован!!!
*/ 
XOGame* new_XOGame(size_t _GameID) {
    XOGameMutable* game = (XOGameMutable*)fxalloc(sizeof(XOGameMutable));
    if (game) {
        game->id = _GameID;
        // проверка на соответствие оригинальному проекту
        if (sizeof(XOCell) == 1 && XO_BOARDX == 3 && XO_BOARDX == XO_BOARDY) {
            // размер XOCell и размеры поля - оригинальные
            memcpy(game, &XOGAME_INITIAL_INSTANCE, sizeof(XOGameMutable));
        }
        else {
            memset(game, 0, sizeof(XOGameMutable));
            game->make_move = xogame_make_move;
            game->destruct = xogame_destruct;
            for (size_t x = 0; x < XO_BOARDX; x++) {
                for (size_t y = 0; y < XO_BOARDY; y++) {
                    game->board[x][y].x = x;
                    game->board[x][y].y = y;
                }
            }
        }
    }
    return game;
}