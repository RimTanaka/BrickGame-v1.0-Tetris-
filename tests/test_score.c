#include "test.h"
/**

 STATE_INIT,
 STATE_RUNNING,
 STATE_PAUSED,
 STATE_GAME_OVER
 */

START_TEST(test_loadHighScore_1) {
  GameInfo_t gameInfo = {0};
  int flag = loadHighScore(&gameInfo);

  ck_assert_int_eq(flag, true);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_saveHighScore_1) {
  GameInfo_t gameInfo = {0};
  gameInfo.score = 16600;
  gameInfo.high_score = 16600;
  int flag = saveHighScore(&gameInfo);

  ck_assert_int_eq(flag, true);

  freeGame(&gameInfo);
}
END_TEST

Suite *test_score_suite(void) {
  Suite *s;
  s = suite_create("\033[33mstest_score\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("test_score");
  tcase_add_test(tc_core, test_saveHighScore_1);
  tcase_add_test(tc_core, test_loadHighScore_1);

  suite_add_tcase(s, tc_core);
  return s;
}
