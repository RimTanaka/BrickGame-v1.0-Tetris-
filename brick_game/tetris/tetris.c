#include "tetris.h"
// #define calloc(x, y) NULL

int initGame(GameInfo_t* gameInfo, bool* gameRunning) {
  int flag = true;
  gameInfo->field = (int**)calloc(HIGHT, sizeof(int*));
  if (gameInfo->field == NULL) {
    perror("\nFailed to allocate memory for game field");
    flag = false;
  }
  for (int i = 0; i < HIGHT && flag; i++) {
    gameInfo->field[i] = (int*)calloc(WIDTH, sizeof(int));
    if (gameInfo->field[i] == NULL) {
      perror("\nFailed to allocate memory for game field row");
      freeGame(gameInfo);
      flag = false;
    }
  }

  if (flag) gameInfo->next = (int**)calloc(4, sizeof(int*));

  if (flag && gameInfo->next == NULL) {
    perror("\nFailed to allocate memory for next figure");
    freeGame(gameInfo);
    flag = false;
  }

  for (int i = 0; i < 4 && flag; i++) {
    gameInfo->next[i] = (int*)calloc(4, sizeof(int));
    if (gameInfo->next[i] == NULL) {
      perror("\nFailed to allocate memory for next figure row");
      freeGame(gameInfo);
      flag = false;
    }
  }

  if (flag)
    *gameRunning = true;
  else
    *gameRunning = false;
  gameInfo->score = 0;
  gameInfo->level = 1;
  gameInfo->speed = 1;
  gameInfo->pause = 0;
  return flag;
}

void freeGame(GameInfo_t* gameInfo) {
  if (gameInfo == NULL) return;
  if (gameInfo->field != NULL) {
    for (int i = 0; i < HIGHT; i++) {
      if (gameInfo->field[i] != NULL) {
        free(gameInfo->field[i]);
        gameInfo->field[i] = NULL;
      }
    }
    free(gameInfo->field);
    gameInfo->field = NULL;
  }

  if (gameInfo->next != NULL) {
    for (int i = 0; i < 4; i++) {
      if (gameInfo->next[i] != NULL) {
        free(gameInfo->next[i]);
        gameInfo->next[i] = NULL;
      }
    }
    free(gameInfo->next);
    gameInfo->next = NULL;
  }
}

void userInput(UserAction_t action, bool hold, bool* gameRunning,
               GameInfo_t* gameInfo, Figure_t** currentFigure,
               GameState_t* currentState) {
  int flag = true;
  switch (*currentState) {
    case STATE_INIT:
      flag = initGame(gameInfo, gameRunning);
      if (flag) {
        srand(time(NULL));
        printf("%d",
               rand() % 7);     // Need to 1 Fig -> dinamic, print for cppcheck
        int type = rand() % 7;  // rand() % 7
        initNewFigure(gameInfo, type);

        *currentFigure = createFigure(type);
        (*currentFigure)->nexType = rand() % 7;

        updateNextFigure(gameInfo, (*currentFigure)->shape,
                         &(*currentFigure)->nexType);
        *currentState = STATE_RUNNING;
      }
      break;

    case STATE_RUNNING:
      if (action == Pause)
        *currentState = STATE_PAUSED;
      else if (action == Terminate || checkGameOver(gameInfo))
        *currentState = STATE_GAME_OVER;
      else {
        handleRunningState(action, hold, gameInfo, *currentFigure);
        clearFullLines(gameInfo);
      }
      break;

    case STATE_PAUSED:
      if (action == Pause)
        *currentState = STATE_RUNNING;
      else if (action == Terminate)
        *currentState = STATE_GAME_OVER;
      break;

    case STATE_GAME_OVER:
      destroyFigure(*currentFigure);
      *gameRunning = false;
      break;
  }
}

void handleRunningState(UserAction_t action, bool hold, GameInfo_t* gameInfo,
                        Figure_t* currentFigure) {
  switch (action) {
    case Left:
      if (hold) moveFigureLeft(currentFigure, gameInfo);
      break;
    case Right:
      moveFigureRight(currentFigure, gameInfo);
      break;
    case Down:
      moveFigureDown(currentFigure, gameInfo);
      break;
    case Action:
      rotateFigure(currentFigure, gameInfo);
      break;
    case Up:
    default:
      break;
  }
}

/*
 предназначена для получения данных для отрисовки в интерфейсе
 */
GameInfo_t updateCurrentState(GameInfo_t gameInfo, int* fallCounter,
                              int* fallSpeed, Figure_t* currentFigure,
                              GameState_t currentState) {
  fallTick(fallCounter, fallSpeed, currentFigure, &gameInfo, currentState);

  updHighScore(&gameInfo);

  updLvl(&gameInfo, fallSpeed);
  return gameInfo;
}

bool checkGameOver(GameInfo_t* gameInfo) {
  int flag = false;
  for (int x = 1; x < 10 && !flag; x++) {
    if (gameInfo->field[0][x] != 0) {
      flag = true;
    }
  }
  return flag;
}

int loadHighScore(GameInfo_t* gameInfo) {
  FILE* fp;
  int flag = true;
  if ((fp = fopen("./brick_game/tetris/score.txt", "r")) == NULL) {
    // Если нет файла создаем его, ну а если уже не получится создать, то ОШИБКА
    if ((fp = fopen("./brick_game/tetris/score.txt", "w+")) == NULL) {
      printf("Cannot open file.\n");
      flag = false;
    }
    gameInfo->high_score = 0;
  }
  if (fscanf(fp, "%d", &gameInfo->high_score) != 1) {
    gameInfo->high_score = 0;
  }

  if (flag) fclose(fp);
  return flag;
}

int saveHighScore(GameInfo_t* gameInfo) {
  int flag = true;
  if (gameInfo->score >= gameInfo->high_score) {
    FILE* fp = fopen("./brick_game/tetris/score.txt", "w");
    if (fp == NULL) {
      printf("Cannot open file for writing.\n");
      flag = false;
    }
    if (flag) {
      fprintf(fp, "%d", gameInfo->high_score);
      fclose(fp);
    }
  }
  return flag;
}

void fallTick(int* fallCounter, const int* fallSpeed, Figure_t* currentFigure,
              GameInfo_t* gameInfo, GameState_t currentState) {
  if (*fallCounter >= *fallSpeed && currentState == STATE_RUNNING) {
    moveFigureDown(currentFigure, gameInfo);
    *fallCounter = 0;
  } else {
    *fallCounter += 1;
  }
}

void updHighScore(GameInfo_t* gameInfo) {
  if (gameInfo->score > gameInfo->high_score) {
    gameInfo->high_score = gameInfo->score;
  }
}

void updLvl(GameInfo_t* gameInfo, int* fallSpeed) {
  if (gameInfo->level < 10) {
    gameInfo->level = gameInfo->score / 600 + 1;
    *fallSpeed = 20 - gameInfo->score / 600 * 1.5;
  } else {
    gameInfo->level = 10;
    *fallSpeed = 20 - 10 * 1.5;
  }
}
