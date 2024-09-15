#include "test.h"
/**

 STATE_INIT,
 STATE_RUNNING,
 STATE_PAUSED,
 STATE_GAME_OVER
 */

START_TEST(test_upd_currentState_tick_1) {
  GameInfo_t gameInfo = {0};
  GameState_t currentState = STATE_INIT;
  bool gameRunning = true;
  Figure_t *currentFigure = {0};
  UserAction_t action = Start;
  bool hold = true;

  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  int fallCounter = 20;
  int fallSpeed = 20;
  gameInfo = updateCurrentState(gameInfo, &fallCounter, &fallSpeed,
                                currentFigure, currentState);

  ck_assert_int_eq(fallCounter, 0);
  currentState = STATE_GAME_OVER;
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);

  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_upd_currentState_tick_2) {
  GameInfo_t gameInfo = {0};
  GameState_t currentState = STATE_INIT;
  bool gameRunning = true;
  Figure_t *currentFigure = {0};
  UserAction_t action = Start;
  bool hold = true;

  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  int fallCounter = 0;
  int fallSpeed = 20;
  gameInfo = updateCurrentState(gameInfo, &fallCounter, &fallSpeed,
                                currentFigure, currentState);

  ck_assert_int_eq(fallCounter, 1);
  currentState = STATE_GAME_OVER;
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);

  freeGame(&gameInfo);
}
END_TEST

// collisionFigure
START_TEST(test_upd_currentState_tick_3) {
  GameInfo_t gameInfo = {0};
  GameState_t currentState = STATE_INIT;
  bool gameRunning = true;
  Figure_t *currentFigure = {0};
  UserAction_t action = Start;
  bool hold = true;

  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  int fallCounter = 20;
  int fallSpeed = 20;
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      gameInfo.field[i][j] = 1;
    }
  }
  gameInfo = updateCurrentState(gameInfo, &fallCounter, &fallSpeed,
                                currentFigure, currentState);

  ck_assert_int_eq(fallCounter, 0);
  currentState = STATE_GAME_OVER;
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);

  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_upd_currentState_score_1) {
  GameInfo_t gameInfo = {0};
  GameState_t currentState = STATE_INIT;
  bool gameRunning = true;
  Figure_t *currentFigure = {0};
  UserAction_t action = Start;
  bool hold = true;

  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  int fallCounter = 0;
  int fallSpeed = 20;
  gameInfo.high_score = 0;
  gameInfo.score = 100;

  gameInfo = updateCurrentState(gameInfo, &fallCounter, &fallSpeed,
                                currentFigure, currentState);

  ck_assert_int_eq(gameInfo.high_score, gameInfo.score);

  currentState = STATE_GAME_OVER;
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);

  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_upd_currentState_score_2) {
  GameInfo_t gameInfo = {0};
  GameState_t currentState = STATE_INIT;
  bool gameRunning = true;
  Figure_t *currentFigure = {0};
  UserAction_t action = Start;
  bool hold = true;
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  int fallCounter = 0;
  int fallSpeed = 20;

  for (int i = 19; i < HIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      gameInfo.field[i][j] = 1;
    }
  }
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  gameInfo = updateCurrentState(gameInfo, &fallCounter, &fallSpeed,
                                currentFigure, currentState);

  ck_assert_int_eq(gameInfo.score, 100);

  currentState = STATE_GAME_OVER;
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);

  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_upd_currentState_score_3) {
  GameInfo_t gameInfo = {0};
  GameState_t currentState = STATE_INIT;
  bool gameRunning = true;
  Figure_t *currentFigure = {0};
  UserAction_t action = Start;
  bool hold = true;
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  int fallCounter = 0;
  int fallSpeed = 20;

  for (int i = 18; i < HIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      gameInfo.field[i][j] = 1;
    }
  }
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  gameInfo = updateCurrentState(gameInfo, &fallCounter, &fallSpeed,
                                currentFigure, currentState);

  ck_assert_int_eq(gameInfo.score, 300);

  currentState = STATE_GAME_OVER;
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);

  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_upd_currentState_score_4) {
  GameInfo_t gameInfo = {0};
  GameState_t currentState = STATE_INIT;
  bool gameRunning = true;
  Figure_t *currentFigure = {0};
  UserAction_t action = Start;
  bool hold = true;
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  int fallCounter = 0;
  int fallSpeed = 20;

  for (int i = 17; i < HIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      gameInfo.field[i][j] = 1;
    }
  }
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  gameInfo = updateCurrentState(gameInfo, &fallCounter, &fallSpeed,
                                currentFigure, currentState);

  ck_assert_int_eq(gameInfo.score, 700);

  currentState = STATE_GAME_OVER;
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);

  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_upd_currentState_score_5) {
  GameInfo_t gameInfo = {0};
  GameState_t currentState = STATE_INIT;
  bool gameRunning = true;
  Figure_t *currentFigure = {0};
  UserAction_t action = Start;
  bool hold = true;
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  int fallCounter = 0;
  int fallSpeed = 20;

  for (int i = 16; i < HIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      gameInfo.field[i][j] = 1;
    }
  }
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  gameInfo = updateCurrentState(gameInfo, &fallCounter, &fallSpeed,
                                currentFigure, currentState);

  ck_assert_int_eq(gameInfo.score, 1500);

  currentState = STATE_GAME_OVER;
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);

  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_upd_currentState_lvl_1) {
  GameInfo_t gameInfo = {0};
  GameState_t currentState = STATE_INIT;
  bool gameRunning = true;
  Figure_t *currentFigure = {0};
  UserAction_t action = Start;
  bool hold = true;

  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  int fallCounter = 0;
  int fallSpeed = 20;
  gameInfo.level = 1;
  gameInfo.score = 1000;
  gameInfo = updateCurrentState(gameInfo, &fallCounter, &fallSpeed,
                                currentFigure, currentState);

  ck_assert_int_eq(gameInfo.level, 2);
  currentState = STATE_GAME_OVER;
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);

  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_upd_currentState_lvl_2) {
  GameInfo_t gameInfo = {0};
  GameState_t currentState = STATE_INIT;
  bool gameRunning = true;
  Figure_t *currentFigure = {0};
  UserAction_t action = Start;
  bool hold = true;

  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);
  int fallCounter = 0;
  int fallSpeed = 20;
  gameInfo.level = 11;

  gameInfo = updateCurrentState(gameInfo, &fallCounter, &fallSpeed,
                                currentFigure, currentState);

  ck_assert_int_eq(gameInfo.level, 10);

  currentState = STATE_GAME_OVER;
  userInput(action, hold, &gameRunning, &gameInfo, &currentFigure,
            &currentState);

  freeGame(&gameInfo);
}
END_TEST

Suite *test_upd_currentState_suite(void) {
  Suite *s;
  s = suite_create("\033[33mstest_upd_currentState\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("test_upd_currentState");
  tcase_add_test(tc_core, test_upd_currentState_tick_1);
  tcase_add_test(tc_core, test_upd_currentState_tick_2);
  tcase_add_test(tc_core, test_upd_currentState_tick_3);
  tcase_add_test(tc_core, test_upd_currentState_score_1);
  tcase_add_test(tc_core, test_upd_currentState_score_2);
  tcase_add_test(tc_core, test_upd_currentState_score_3);
  tcase_add_test(tc_core, test_upd_currentState_score_4);
  tcase_add_test(tc_core, test_upd_currentState_score_5);
  tcase_add_test(tc_core, test_upd_currentState_lvl_1);
  tcase_add_test(tc_core, test_upd_currentState_lvl_2);

  suite_add_tcase(s, tc_core);
  return s;
}
