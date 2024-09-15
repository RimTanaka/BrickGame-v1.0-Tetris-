#include "brick_game/tetris/tetris.h"
#include "gui/cli/frontend.h"

void gameLoop(GameInfo_t *gameInfo, WINDOW *gamewin) {
  GameState_t currentState = STATE_INIT;
  bool gameRunning = true;
  int fallCounter = 0;
  int fallSpeed = 20;
  Figure_t *currentFigure = {0};

  gameRunning = loadHighScore(gameInfo);

  printStartGame();
  while (gameRunning) {
    bool hold = false;
    UserAction_t action = Start;

    int ch = getch();
    if (ch != ERR) {
      action = getUserAction(ch, &hold);
    }
    userInput(action, hold, &gameRunning, gameInfo, &currentFigure,
              &currentState);

    if (gameRunning) {
      *gameInfo = updateCurrentState(*gameInfo, &fallCounter, &fallSpeed,
                                     currentFigure, currentState);
      drawGame(gamewin, gameInfo, currentFigure, currentState);
    }
    usleep(50000);
    clear();
  }

  saveHighScore(gameInfo);
  printGameOver(gameInfo);
}

int main() {
  GameInfo_t gameInfo = {0};

  WINDOW *gamewin = initNcurses();

  gameLoop(&gameInfo, gamewin);

  freeGame(&gameInfo);

  closeNcurses(gamewin);
  return 0;
}
