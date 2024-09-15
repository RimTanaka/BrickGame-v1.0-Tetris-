#ifndef TETRIS_H
#define TETRIS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 10
#define HIGHT 20

typedef enum {
  STATE_INIT,
  STATE_RUNNING,
  STATE_PAUSED,
  STATE_GAME_OVER
} GameState_t;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int** field;
  int** next;
  int score;
  int high_score;
  int level;
  int speed;
  bool pause;
} GameInfo_t;

typedef struct {
  int shape[4][4];
  int x;
  int y;
  int type;
  int nexType;
} Figure_t;

int initGame(GameInfo_t* gameInfo, bool* gameRunning);
void initNewFigure(GameInfo_t* gameInfo, int newType);
void freeGame(GameInfo_t* gameInfo);
UserAction_t getUserAction(int ch, bool* hold);
void updateNextFigure(GameInfo_t* gameInfo, int currentFigure[4][4],
                      int* nexType);

void userInput(UserAction_t action, bool hold, bool* gameRunning,
               GameInfo_t* gameInfo, Figure_t** currentFigure,
               GameState_t* currentState);
GameInfo_t updateCurrentState(GameInfo_t gameInfo, int* fallCounter,
                              int* fallSpeed, Figure_t* currentFigure,
                              GameState_t currentState);

bool checkGameOver(GameInfo_t* gameInfo);
void handleRunningState(UserAction_t action, bool hold, GameInfo_t* gameInfo,
                        Figure_t* currentFigure);
int loadHighScore(GameInfo_t* gameInfo);
int saveHighScore(GameInfo_t* gameInfo);
void fallTick(int* fallCounter, const int* fallSpeed, Figure_t* currentFigure,
              GameInfo_t* gameInfo, GameState_t currentState);
void updHighScore(GameInfo_t* gameInfo);
void updLvl(GameInfo_t* gameInfo, int* fallSpeed);

// FIGURE_H

void rotateFigure(Figure_t* figure, GameInfo_t* gameInfo);
Figure_t* createFigure(int type);
void destroyFigure(Figure_t* figure);

void moveFigureDown(Figure_t* figure, GameInfo_t* gameInfo);
void moveFigureRight(Figure_t* figure, GameInfo_t* gameInfo);
void moveFigureLeft(Figure_t* figure, GameInfo_t* gameInfo);

bool collisionFigure(Figure_t* figure, GameInfo_t* GameInfo);
void fixFigure(Figure_t* figure, GameInfo_t* info);

void clearFullLines(GameInfo_t* gameInfo);
void updScore(GameInfo_t* gameInfo, int linesCleared);

#endif
