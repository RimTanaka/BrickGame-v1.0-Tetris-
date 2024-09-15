#ifndef INTERFACE_H
#define INTERFACE_H

#include <ncurses.h>

#include "../../brick_game/tetris/tetris.h"

#define CELL_HIGHT 2
#define CELL_WIDTH 4

WINDOW *initNcurses();
void closeNcurses(WINDOW *gamewin);
UserAction_t getUserAction(int ch, bool *hold);
void drawGame(WINDOW *gamewin, GameInfo_t *gameInfo, Figure_t *currentFigure,
              GameState_t currentState);
void printStartGame();
void printGameOver(GameInfo_t *gameInfo);
static const int TETROMINOS[8][4][4];
void drawBorders(WINDOW *gamewin);
void drawGrid(WINDOW *gamewin);
void drawGameInterface(GameInfo_t *gameInfo);
void drawFigure(WINDOW *gamewin, Figure_t *figure);
void drawGameField(WINDOW *gamewin, GameInfo_t *gameInfo);

#endif
