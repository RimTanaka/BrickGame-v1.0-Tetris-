#include "test.h"
/**

 STATE_INIT,
 STATE_RUNNING,
 STATE_PAUSED,
 STATE_GAME_OVER
 */

START_TEST(test_handle_running_left) {
  GameInfo_t gameInfo = {0};
  GameState_t currentState = STATE_INIT;
  bool gameRunning = true;
  Figure_t *currentFigure = {0};
  UserAction_t action = Start;
  bool hold = true;

  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);

  int x = currentFigure->x;
  x--;
  action = Left;

  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);

  ck_assert_int_eq(x, currentFigure->x);

  currentState = STATE_GAME_OVER;
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);

  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_handle_running_right) {
  GameInfo_t gameInfo = {0};
  GameState_t currentState = STATE_INIT;
  bool gameRunning = true;
  Figure_t *currentFigure = {0};
  UserAction_t action = Right;
  bool hold = true;

  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);

  int x = currentFigure->x;
  x++;

  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);

  ck_assert_int_eq(x, currentFigure->x);

  currentState = STATE_GAME_OVER;
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);

  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_handle_running_down) {
  GameInfo_t gameInfo = {0};
  GameState_t currentState = STATE_INIT;
  bool gameRunning = true;
  Figure_t *currentFigure = {0};
  UserAction_t action = Down;
  bool hold = true;

  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);

  int y = currentFigure->y;
  y++;

  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);

  ck_assert_int_eq(y, currentFigure->y);

  currentState = STATE_GAME_OVER;
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);

  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_handle_running_up) {
  GameInfo_t gameInfo = {0};
  GameState_t currentState = STATE_INIT;
  bool gameRunning = true;
  Figure_t *currentFigure = {0};
  UserAction_t action = Up;
  bool hold = true;

  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);

  int x = currentFigure->x;
  int y = currentFigure->y;

  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);

  ck_assert_int_eq(x, currentFigure->x);
  ck_assert_int_eq(y, currentFigure->y);

  currentState = STATE_GAME_OVER;
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);

  freeGame(&gameInfo);
}
END_TEST

Suite *test_handle_running_suite(void) {
  Suite *s;
  s = suite_create("\033[33mstest_handle_running\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("test_handle_running");
  tcase_add_test(tc_core, test_handle_running_left);
  tcase_add_test(tc_core, test_handle_running_right);
  tcase_add_test(tc_core, test_handle_running_down);
  tcase_add_test(tc_core, test_handle_running_up);

  suite_add_tcase(s, tc_core);
  return s;
}
