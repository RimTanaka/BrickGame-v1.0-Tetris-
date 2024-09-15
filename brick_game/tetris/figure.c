#include <stdlib.h>

#include "tetris.h"

static const int TETROMINOS[8][4][4] = {
    {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}},

    {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 1, 0}},

    {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 0}},

    {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}},

    {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}},

    {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},

    {{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}},

    {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
};

void rotationO(Figure_t* temp, Figure_t* figure) {
  if (figure->shape[2][0] == 1) {
    for (int i = 0; i < 4; i++) {
      temp->shape[i][2] = figure->shape[2][i];
    }
  } else {
    for (int i = 0; i < 4; i++) {
      temp->shape[2][i] = figure->shape[i][2];
    }
  }
}

void rotationLeftG(Figure_t* temp, Figure_t* figure) {
  if (figure->shape[3][0] == 1 && figure->shape[3][2] == 1) {
    temp->shape[1][2] = figure->shape[2][0];
    temp->shape[2][2] = figure->shape[3][0];
    temp->shape[3][2] = figure->shape[3][1];
    temp->shape[3][1] = figure->shape[3][2];
  } else if (figure->shape[3][2] == 1 && figure->shape[1][2] == 1) {
    temp->shape[1][2] = figure->shape[1][2];
    temp->shape[2][2] = figure->shape[2][2];
    temp->shape[1][0] = figure->shape[3][2];
    temp->shape[1][1] = figure->shape[3][1];
  } else if (figure->shape[1][0] == 1 && figure->shape[1][2] == 1) {
    temp->shape[3][0] = figure->shape[1][2];
    temp->shape[2][0] = figure->shape[2][2];
    temp->shape[1][0] = figure->shape[1][0];
    temp->shape[1][1] = figure->shape[1][1];
  } else if (figure->shape[1][0] == 1 && figure->shape[3][0] == 1) {
    temp->shape[2][0] = figure->shape[3][0];
    temp->shape[3][0] = figure->shape[2][0];
    temp->shape[3][1] = figure->shape[1][0];
    temp->shape[3][2] = figure->shape[1][1];
  }
}

void rotationRightG(Figure_t* temp, Figure_t* figure) {
  if (figure->shape[3][0] == 1 && figure->shape[3][2] == 1) {
    temp->shape[3][2] = figure->shape[3][0];
    temp->shape[2][2] = figure->shape[3][1];
    temp->shape[1][2] = figure->shape[3][2];
    temp->shape[1][1] = figure->shape[2][2];
  } else if (figure->shape[3][2] == 1 && figure->shape[1][2] == 1) {
    temp->shape[1][2] = figure->shape[3][2];
    temp->shape[2][0] = figure->shape[2][2];
    temp->shape[1][0] = figure->shape[1][2];
    temp->shape[1][1] = figure->shape[1][1];
  } else if (figure->shape[1][2] == 1 && figure->shape[1][0] == 1) {
    temp->shape[1][0] = figure->shape[1][2];
    temp->shape[2][0] = figure->shape[2][0];
    temp->shape[3][0] = figure->shape[1][0];
    temp->shape[3][1] = figure->shape[1][1];
  } else if (figure->shape[1][0] == 1 && figure->shape[3][0] == 1) {
    temp->shape[3][0] = figure->shape[1][0];
    temp->shape[3][1] = figure->shape[2][0];
    temp->shape[3][2] = figure->shape[3][0];
    temp->shape[2][2] = figure->shape[3][1];
  }
}

void rotationT(Figure_t* temp, Figure_t* figure) {
  if (figure->shape[3][0] == 1 && figure->shape[3][2] == 1) {
    temp->shape[2][1] = figure->shape[2][1];
    temp->shape[1][2] = figure->shape[3][0];
    temp->shape[2][2] = figure->shape[3][1];
    temp->shape[3][2] = figure->shape[3][2];
  } else if (figure->shape[1][2] == 1 && figure->shape[3][2] == 1) {
    temp->shape[2][1] = figure->shape[2][1];
    temp->shape[1][0] = figure->shape[1][2];
    temp->shape[1][1] = figure->shape[2][2];
    temp->shape[1][2] = figure->shape[3][2];
  } else if (figure->shape[1][2] == 1 && figure->shape[1][0] == 1) {
    temp->shape[2][1] = figure->shape[2][1];
    temp->shape[1][0] = figure->shape[1][0];
    temp->shape[2][0] = figure->shape[1][1];
    temp->shape[3][0] = figure->shape[1][2];
  } else if (figure->shape[1][0] == 1 && figure->shape[3][0] == 1) {
    temp->shape[2][1] = figure->shape[2][1];
    temp->shape[3][0] = figure->shape[1][0];
    temp->shape[3][1] = figure->shape[2][0];
    temp->shape[3][2] = figure->shape[3][0];
  }
}

void rotationLeftZ(Figure_t* temp, Figure_t* figure) {
  if (figure->shape[1][0] == 1) {
    temp->shape[1][1] = figure->shape[1][0];
    temp->shape[2][1] = figure->shape[1][1];
    temp->shape[2][0] = figure->shape[2][1];
    temp->shape[3][0] = figure->shape[2][2];
  } else {
    temp->shape[1][0] = figure->shape[1][1];
    temp->shape[1][1] = figure->shape[2][1];
    temp->shape[2][1] = figure->shape[2][0];
    temp->shape[2][2] = figure->shape[3][0];
  }
}

void rotationRightZ(Figure_t* temp, Figure_t* figure) {
  if (figure->shape[3][1] == 1) {
    temp->shape[1][1] = figure->shape[1][0];
    temp->shape[1][2] = figure->shape[2][1];
    temp->shape[2][1] = figure->shape[2][0];
    temp->shape[2][0] = figure->shape[3][1];
  } else {
    temp->shape[1][0] = figure->shape[1][1];
    temp->shape[2][1] = figure->shape[1][2];
    temp->shape[2][0] = figure->shape[2][1];
    temp->shape[3][1] = figure->shape[2][0];
  }
}

void rotateFigure(Figure_t* figure, GameInfo_t* gameInfo) {
  Figure_t* temp = createFigure(7);
  temp->x = figure->x;
  temp->y = figure->y;
  temp->type = figure->type;
  temp->nexType = figure->nexType;

  if (figure->type == 0)
    rotationO(temp, figure);  // Прямая фигура
  else if (figure->type == 1)
    rotationLeftG(temp, figure);  // Г фигура леая
  else if (figure->type == 2)
    rotationRightG(temp, figure);  // Г фигура правая
  else if (figure->type == 3)
    *temp = *figure;  // Квадрат
  else if (figure->type == 4) {
    rotationT(temp, figure);  // T фигура
  } else if (figure->type == 5)
    rotationLeftZ(temp, figure);  // Z фигура
  else if (figure->type == 6)
    rotationRightZ(temp, figure);  // Обратная Z фигура

  if (!collisionFigure(temp, gameInfo)) *figure = *temp;
  destroyFigure(temp);
}

void updateNextFigure(GameInfo_t* gameInfo, int currentFigure[4][4],
                      int* nexType) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      currentFigure[i][j] = gameInfo->next[i][j];
    }
  }

  *nexType = rand() % 7;
  Figure_t* nextFigure = createFigure(*nexType);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      gameInfo->next[i][j] = nextFigure->shape[i][j];
    }
  }
  destroyFigure(nextFigure);
}

void initNewFigure(GameInfo_t* gameInfo, int newType) {
  Figure_t* newFigure = createFigure(newType);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      gameInfo->next[i][j] = newFigure->shape[i][j];
    }
  }
  destroyFigure(newFigure);
}

Figure_t* createFigure(int type) {
  Figure_t* figure = (Figure_t*)malloc(sizeof(Figure_t));
  if (!figure) {
    fprintf(stderr, "Failed to allocate memory for figure\n");
    return NULL;
  }
  figure->x = 0;
  figure->y = -3;
  figure->type = type;
  figure->nexType = rand() % 7;
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) figure->shape[i][j] = TETROMINOS[type][i][j];
  figure->x = WIDTH / 3;
  return figure;
}

void destroyFigure(Figure_t* figure) {
  if (figure) free(figure);
}

void moveFigureDown(Figure_t* figure, GameInfo_t* gameInfo) {
  figure->y++;
  if (collisionFigure(figure, gameInfo)) {
    figure->y--;
    fixFigure(figure, gameInfo);
    figure->type = figure->nexType;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        figure->shape[i][j] = gameInfo->next[i][j];
      }
    }
    figure->x = WIDTH / 3;
    figure->y = -3;
    figure->nexType = rand() % 7;
    updateNextFigure(gameInfo, figure->shape, &figure->nexType);
  }
}

void moveFigureRight(Figure_t* figure, GameInfo_t* gameInfo) {
  figure->x++;
  if (collisionFigure(figure, gameInfo)) {
    figure->x--;
  }
}

void moveFigureLeft(Figure_t* figure, GameInfo_t* gameInfo) {
  figure->x--;
  if (collisionFigure(figure, gameInfo)) {
    figure->x++;
  }
}

bool collisionFigure(Figure_t* figure, GameInfo_t* GameInfo) {
  int flag = false;
  for (int i = 0; i < 4 && !flag; i++) {
    for (int j = 0; j < 4 && !flag; j++) {
      if (figure->shape[i][j] == 0) continue;

      int newX = figure->x + j;
      int newY = figure->y + i;

      if (!flag && (newX < 0 || newX >= WIDTH || newY >= HIGHT)) {
        flag = true;
      }

      if (!flag && (newY >= 0 && GameInfo->field[newY][newX] != 0)) {
        flag = true;
      }
    }
  }

  return flag;
}

void fixFigure(Figure_t* figure, GameInfo_t* info) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (figure->shape[i][j] == 0) continue;

      int x = figure->x + j;
      int y = figure->y + i;

      if (y >= 0 && x >= 0 && x < WIDTH && y < HIGHT)
        info->field[y][x] = figure->shape[i][j];
    }
  }
}

void updScore(GameInfo_t* gameInfo, int linesCleared) {
  switch (linesCleared) {
    case 1:
      gameInfo->score += 100;
      break;
    case 2:
      gameInfo->score += 300;
      break;
    case 3:
      gameInfo->score += 700;
      break;
    case 4:
      gameInfo->score += 1500;
      break;
    default:
      break;
  }
}

void clearFullLines(GameInfo_t* gameInfo) {
  int linesCleared = 0;
  for (int y = 0; y < 20; y++) {
    bool isFull = true;
    for (int x = 0; x < 10; x++) {
      if (gameInfo->field[y][x] == 0) {
        isFull = false;
        break;
      }
    }
    if (isFull) {
      linesCleared++;
      for (int yy = y; yy > 0; yy--) {
        for (int xx = 0; xx < 10; xx++) {
          gameInfo->field[yy][xx] = gameInfo->field[yy - 1][xx];
        }
      }
      for (int xx = 0; xx < 10; xx++) {
        gameInfo->field[0][xx] = 0;
      }
    }
  }
  updScore(gameInfo, linesCleared);
}
