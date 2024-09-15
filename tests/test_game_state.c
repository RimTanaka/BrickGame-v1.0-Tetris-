#include "test.h"
/**

 STATE_INIT,
 STATE_RUNNING,
 STATE_PAUSED,
 STATE_GAME_OVER
 */

START_TEST(test_game_state_running) {
  GameInfo_t gameInfo = {0};
  GameState_t currentState = STATE_INIT;
  bool gameRunning = true;
  Figure_t *currentFigure = {0};
  UserAction_t action = Start;
  bool hold = false;

  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  ck_assert_int_eq(currentState, STATE_RUNNING);
  currentState = STATE_GAME_OVER;
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_game_state_pause_1) {
  GameInfo_t gameInfo = {0};
  GameState_t currentState = STATE_RUNNING;
  bool gameRunning = true;
  Figure_t *currentFigure = {0};
  UserAction_t action = Pause;
  bool hold = false;

  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  ck_assert_int_eq(currentState, STATE_PAUSED);
  currentState = STATE_GAME_OVER;
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_game_state_pause_2) {
  GameInfo_t gameInfo = {0};
  GameState_t currentState = STATE_PAUSED;
  bool gameRunning = true;
  Figure_t *currentFigure = {0};
  UserAction_t action = Pause;
  bool hold = false;

  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  ck_assert_int_eq(currentState, STATE_RUNNING);
  currentState = STATE_GAME_OVER;
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_game_state_pause_3) {
  GameInfo_t gameInfo = {0};
  GameState_t currentState = STATE_PAUSED;
  bool gameRunning = true;
  Figure_t *currentFigure = {0};
  UserAction_t action = Terminate;
  bool hold = false;

  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  ck_assert_int_eq(currentState, STATE_GAME_OVER);
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_game_state_terminate_1) {
  GameInfo_t gameInfo = {0};
  GameState_t currentState = STATE_RUNNING;
  bool gameRunning = true;
  Figure_t *currentFigure = {0};
  UserAction_t action = Terminate;
  bool hold = false;

  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  ck_assert_int_eq(currentState, STATE_GAME_OVER);
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_game_state_terminate_2) {
  GameInfo_t gameInfo = {0};
  GameState_t currentState = STATE_GAME_OVER;
  bool gameRunning = true;
  Figure_t *currentFigure = {0};
  UserAction_t action = Terminate;
  bool hold = false;

  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  ck_assert_int_eq(gameRunning, false);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_game_state_terminate_3) {
  GameInfo_t gameInfo = {0};
  GameState_t currentState = STATE_INIT;
  bool gameRunning = true;
  Figure_t *currentFigure = {0};
  UserAction_t action = Start;
  bool hold = false;

  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);

  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      gameInfo.field[i][j] = 1;
    }
  }
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  ck_assert_int_eq(currentState, STATE_GAME_OVER);
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  freeGame(&gameInfo);
}
END_TEST

Suite *test_game_state_suite(void) {
  Suite *s;
  s = suite_create("\033[33mstest_game_state\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("test_game_state");
  tcase_add_test(tc_core, test_game_state_running);
  tcase_add_test(tc_core, test_game_state_pause_1);
  tcase_add_test(tc_core, test_game_state_pause_2);
  tcase_add_test(tc_core, test_game_state_pause_3);
  tcase_add_test(tc_core, test_game_state_terminate_1);
  tcase_add_test(tc_core, test_game_state_terminate_2);
  tcase_add_test(tc_core, test_game_state_terminate_3);

  suite_add_tcase(s, tc_core);
  return s;
}
