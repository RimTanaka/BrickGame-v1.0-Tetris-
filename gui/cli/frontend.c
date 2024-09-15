#include "frontend.h"

WINDOW *initNcurses() {
  initscr();
  cbreak();

  start_color();
  init_pair(1, COLOR_GREEN, COLOR_WHITE);  // сетка самой карты
  init_pair(2, COLOR_CYAN, COLOR_BLACK);   // сетка  контур
  init_pair(3, COLOR_RED, COLOR_BLACK);  // фигур с прозрачным фоном
  init_pair(4, COLOR_YELLOW, COLOR_BLACK);  // заполненные клетки поля
  init_pair(5, COLOR_WHITE, COLOR_BLACK);  // левая границы

  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  scrollok(stdscr, TRUE);
  curs_set(0);

  int begin_y = 1, begin_x = 1;
  WINDOW *gamewin =
      newwin(HIGHT * CELL_HIGHT + 1, WIDTH * CELL_WIDTH + 1, begin_y, begin_x);

  wbkgd(gamewin, COLOR_PAIR(1));

  return gamewin;
}

void closeNcurses(WINDOW *gamewin) {
  delwin(gamewin);
  endwin();
}

UserAction_t getUserAction(int ch, bool *hold) {
  int flag = Start;
  switch (ch) {
    case KEY_LEFT:
      *hold = true;
      flag = Left;
      break;
    case KEY_RIGHT:
      *hold = true;
      flag = Right;
      break;
    case KEY_DOWN:
      *hold = true;
      flag = Down;
      break;
    case KEY_UP:
      *hold = false;
      flag = Action;
      break;
    case 'p':
    case 'P':
      flag = Pause;
      break;
    case 'q':
    case 'Q':
      flag = Terminate;
      break;
    default:
      flag = Start;
      break;
  }
  return flag;
}

void drawGame(WINDOW *gamewin, GameInfo_t *gameInfo, Figure_t *currentFigure,
              GameState_t currentState) {
  // Очистка и перерисовка окна
  werase(gamewin);

  drawBorders(gamewin);
  drawFigure(gamewin, currentFigure);
  drawGameField(gamewin, gameInfo);
  drawGrid(gamewin);
  drawGameInterface(gameInfo);
  if (currentState == STATE_PAUSED) {
    mvprintw(HIGHT * CELL_HIGHT / 2, WIDTH * CELL_WIDTH / 3, "Game Paused");
  }

  wrefresh(gamewin);
  refresh();
}

void printStartGame() {
  mvprintw(HIGHT * CELL_HIGHT / 2, WIDTH * CELL_WIDTH / 3,
           "Let's started the game");
  mvprintw(HIGHT * CELL_HIGHT / 2 + 2, WIDTH * CELL_WIDTH / 3,
           "Press Enter to start");
  mvprintw(HIGHT * CELL_HIGHT / 2 + 4, WIDTH * CELL_WIDTH / 3,
           "Control: Left, Right, Up(rotation), Down");
  mvprintw(HIGHT * CELL_HIGHT / 2 + 6, WIDTH * CELL_WIDTH / 3,
           "Control: p(Pause), q(Quit)");
  while (getch() != 10)
    ;
}

void printGameOver(GameInfo_t *gameInfo) {
  char ch = 10;
  mvprintw(HIGHT * CELL_HIGHT / 2, WIDTH * CELL_WIDTH / 3, "Game Over");
  mvprintw(HIGHT * CELL_HIGHT / 2 + 2, WIDTH * CELL_WIDTH / 3, "Your score: %d",
           gameInfo->score);
  mvprintw(HIGHT * CELL_HIGHT / 2 + 4, WIDTH * CELL_WIDTH / 3, "Max score: %d",
           gameInfo->high_score);
  mvprintw(HIGHT * CELL_HIGHT / 2 + 6, WIDTH * CELL_WIDTH / 3,
           "Press q, to exit");
  while (ch != 'q' && ch != 'Q') ch = getch();
}

void drawBorders(WINDOW *gamewin) {
  wattron(gamewin, COLOR_PAIR(5));
  for (int i = 0; i <= HIGHT * CELL_HIGHT; ++i) mvwprintw(gamewin, i, 0, "|");

  for (int i = 0; i <= HIGHT * CELL_HIGHT; ++i)
    mvwprintw(gamewin, i, WIDTH * CELL_WIDTH, "|");

  for (int j = 0; j <= WIDTH * CELL_WIDTH; ++j)
    mvwprintw(gamewin, HIGHT * CELL_HIGHT, j, "-");

  wattroff(gamewin, COLOR_PAIR(5));
}

void drawGrid(WINDOW *gamewin) {
  wattron(gamewin, COLOR_PAIR(2));
  for (int i = 0; i < HIGHT * CELL_HIGHT; ++i) {
    for (int j = 1; j <= WIDTH * CELL_WIDTH - 1; ++j) {
      if (i % CELL_HIGHT == 0) mvwprintw(gamewin, i, j, "-");
      if (j % CELL_WIDTH == 0) mvwprintw(gamewin, i, j, "|");
    }
  }
  wattroff(gamewin, COLOR_PAIR(2));
}

void drawGameInterface(GameInfo_t *gameInfo) {
  mvprintw(4, 15 * CELL_WIDTH, "Score: %d", gameInfo->score);
  mvprintw(5, 15 * CELL_WIDTH, "High Score: %d", gameInfo->high_score);
  mvprintw(6, 15 * CELL_WIDTH, "Level: %d", gameInfo->level);
  mvprintw(7, 15 * CELL_WIDTH, "Speed: %d", gameInfo->level);
  mvprintw(8, 15 * CELL_WIDTH, "Next:");

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (gameInfo->next[i][j] == 0) continue;
      mvprintw(10 + i, 15 * CELL_WIDTH + j, "@");
    }
  }
}

void drawFigure(WINDOW *gamewin, Figure_t *figure) {
  wattron(gamewin, COLOR_PAIR(3));
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; ++j) {
      if (figure->shape[i][j] == 0) {
        continue;
      }
      int y = figure->y * CELL_HIGHT + i * CELL_HIGHT;
      int x = figure->x * CELL_WIDTH + j * CELL_WIDTH;
      for (int h = 0; h < CELL_HIGHT; h++) {
        for (int w = 0; w < CELL_WIDTH - 1; w++)
          mvwaddch(gamewin, y + h, x + w + 1, '@');
      }
    }
  }
  wattroff(gamewin, COLOR_PAIR(3));
}

void drawGameField(WINDOW *gamewin, GameInfo_t *gameInfo) {
  for (int i = 0; i < HIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      int y = i * CELL_HIGHT;
      int x = j * CELL_WIDTH;
      if (gameInfo->field[i][j] == 0) {
        continue;
      }
      wattron(gamewin, COLOR_PAIR(4));
      for (int h = 0; h < CELL_HIGHT; h++) {
        for (int w = 0; w < CELL_WIDTH - 1; w++)
          mvwprintw(gamewin, y + h, x + w + 1, "#");
      }
      wattroff(gamewin, COLOR_PAIR(4));
    }
  }
}
