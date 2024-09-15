#include "test.h"
/**

 STATE_INIT,
 STATE_RUNNING,
 STATE_PAUSED,
 STATE_GAME_OVER
 */

START_TEST(test_rotation_O_1) {
  GameInfo_t gameInfo = {0};
  bool gameRunning = true;
  Figure_t *currentFigure = {0};

  initGame(&gameInfo, &gameRunning);
  int type = 0;
  currentFigure = createFigure(type);

  rotateFigure(currentFigure, &gameInfo);
  int flag = true;
  Figure_t *temp = {0};
  temp = createFigure(7);
  for (int i = 0; i < 4; i++) {
    temp->shape[i][2] = 1;
  }
  for (int i = 0; i < 4; i++) {
    if (temp->shape[i][2] != currentFigure->shape[i][2]) flag = false;
  }
  ck_assert_int_eq(flag, true);

  destroyFigure(temp);
  destroyFigure(currentFigure);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_rotation_O_2) {
  GameInfo_t gameInfo = {0};
  bool gameRunning = true;
  Figure_t *currentFigure = {0};

  initGame(&gameInfo, &gameRunning);
  int type = 0;
  currentFigure = createFigure(type);

  rotateFigure(currentFigure, &gameInfo);
  rotateFigure(currentFigure, &gameInfo);
  int flag = true;
  Figure_t *temp = {0};
  temp = createFigure(7);
  for (int i = 0; i < 4; i++) {
    temp->shape[2][i] = 1;
  }
  for (int i = 0; i < 4; i++) {
    if (temp->shape[2][i] != currentFigure->shape[2][i]) flag = false;
  }
  ck_assert_int_eq(flag, true);
  destroyFigure(temp);
  destroyFigure(currentFigure);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_rotation_LeftG_1) {
  GameInfo_t gameInfo = {0};
  bool gameRunning = true;
  Figure_t *currentFigure = {0};

  initGame(&gameInfo, &gameRunning);
  int type = 1;
  currentFigure = createFigure(type);

  rotateFigure(currentFigure, &gameInfo);

  int flag = true;
  Figure_t *temp = createFigure(7);
  temp->shape[1][2] = 1;
  temp->shape[2][2] = 1;
  temp->shape[3][2] = 1;
  temp->shape[3][1] = 1;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (temp->shape[i][j] != currentFigure->shape[i][j]) flag = false;
    }
  }
  ck_assert_int_eq(flag, true);
  destroyFigure(temp);
  destroyFigure(currentFigure);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_rotation_LeftG_2) {
  GameInfo_t gameInfo = {0};
  bool gameRunning = true;
  Figure_t *currentFigure = {0};

  initGame(&gameInfo, &gameRunning);
  int type = 1;
  currentFigure = createFigure(type);

  rotateFigure(currentFigure, &gameInfo);
  rotateFigure(currentFigure, &gameInfo);

  int flag = true;
  Figure_t *temp = createFigure(7);
  temp->shape[1][2] = 1;
  temp->shape[2][2] = 1;
  temp->shape[1][0] = 1;
  temp->shape[1][1] = 1;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (temp->shape[i][j] != currentFigure->shape[i][j]) flag = false;
    }
  }

  ck_assert_int_eq(flag, true);
  destroyFigure(temp);
  destroyFigure(currentFigure);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_rotation_LeftG_3) {
  GameInfo_t gameInfo = {0};
  bool gameRunning = true;
  Figure_t *currentFigure = {0};

  initGame(&gameInfo, &gameRunning);
  int type = 1;
  currentFigure = createFigure(type);

  rotateFigure(currentFigure, &gameInfo);
  rotateFigure(currentFigure, &gameInfo);
  rotateFigure(currentFigure, &gameInfo);

  int flag = true;
  Figure_t *temp = createFigure(7);
  temp->shape[3][0] = 1;
  temp->shape[2][0] = 1;
  temp->shape[1][0] = 1;
  temp->shape[1][1] = 1;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (temp->shape[i][j] != currentFigure->shape[i][j]) flag = false;
    }
  }

  ck_assert_int_eq(flag, true);
  destroyFigure(temp);
  destroyFigure(currentFigure);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_rotation_LeftG_4) {
  GameInfo_t gameInfo = {0};
  bool gameRunning = true;
  Figure_t *currentFigure = {0};

  initGame(&gameInfo, &gameRunning);
  int type = 1;
  currentFigure = createFigure(type);

  rotateFigure(currentFigure, &gameInfo);
  rotateFigure(currentFigure, &gameInfo);
  rotateFigure(currentFigure, &gameInfo);
  rotateFigure(currentFigure, &gameInfo);

  int flag = true;
  Figure_t *temp = createFigure(7);
  temp->shape[2][0] = 1;
  temp->shape[3][0] = 1;
  temp->shape[3][1] = 1;
  temp->shape[3][2] = 1;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (temp->shape[i][j] != currentFigure->shape[i][j]) flag = false;
    }
  }

  ck_assert_int_eq(flag, true);
  destroyFigure(temp);
  destroyFigure(currentFigure);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_rotation_RightG_1) {
  GameInfo_t gameInfo = {0};
  bool gameRunning = true;
  initGame(&gameInfo, &gameRunning);
  int type = 2;
  Figure_t *currentFigure = createFigure(type);
  Figure_t *temp = createFigure(7);

  rotateFigure(currentFigure, &gameInfo);

  temp->shape[3][2] = 1;
  temp->shape[2][2] = 1;
  temp->shape[1][2] = 1;
  temp->shape[1][1] = 1;

  int flag = true;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (temp->shape[i][j] != currentFigure->shape[i][j]) flag = false;
    }
  }
  ck_assert_int_eq(flag, true);

  destroyFigure(temp);
  destroyFigure(currentFigure);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_rotation_RightG_2) {
  GameInfo_t gameInfo = {0};
  bool gameRunning = true;

  initGame(&gameInfo, &gameRunning);
  int type = 2;
  Figure_t *currentFigure = createFigure(type);
  Figure_t *temp = createFigure(7);

  rotateFigure(currentFigure, &gameInfo);
  rotateFigure(currentFigure, &gameInfo);

  temp->shape[1][2] = 1;
  temp->shape[2][0] = 1;
  temp->shape[1][0] = 1;
  temp->shape[1][1] = 1;

  int flag = true;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (temp->shape[i][j] != currentFigure->shape[i][j]) flag = false;
    }
  }
  ck_assert_int_eq(flag, true);

  destroyFigure(temp);
  destroyFigure(currentFigure);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_rotation_RightG_3) {
  GameInfo_t gameInfo = {0};
  bool gameRunning = true;

  initGame(&gameInfo, &gameRunning);
  int type = 2;
  Figure_t *currentFigure = createFigure(type);
  Figure_t *temp = createFigure(7);

  rotateFigure(currentFigure, &gameInfo);
  rotateFigure(currentFigure, &gameInfo);
  rotateFigure(currentFigure, &gameInfo);

  temp->shape[1][0] = 1;
  temp->shape[2][0] = 1;
  temp->shape[3][0] = 1;
  temp->shape[3][1] = 1;

  int flag = true;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (temp->shape[i][j] != currentFigure->shape[i][j]) flag = false;
    }
  }
  ck_assert_int_eq(flag, true);

  destroyFigure(temp);
  destroyFigure(currentFigure);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_rotation_RightG_4) {
  GameInfo_t gameInfo = {0};
  bool gameRunning = true;

  initGame(&gameInfo, &gameRunning);
  int type = 2;
  Figure_t *currentFigure = createFigure(type);
  Figure_t *temp = createFigure(7);

  rotateFigure(currentFigure, &gameInfo);
  rotateFigure(currentFigure, &gameInfo);
  rotateFigure(currentFigure, &gameInfo);
  rotateFigure(currentFigure, &gameInfo);

  temp->shape[3][0] = 1;
  temp->shape[3][1] = 1;
  temp->shape[3][2] = 1;
  temp->shape[2][2] = 1;

  int flag = true;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (temp->shape[i][j] != currentFigure->shape[i][j]) flag = false;
    }
  }
  ck_assert_int_eq(flag, true);

  destroyFigure(temp);
  destroyFigure(currentFigure);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_rotation_N_1) {
  GameInfo_t gameInfo = {0};
  bool gameRunning = true;

  initGame(&gameInfo, &gameRunning);
  int type = 3;
  Figure_t *currentFigure = createFigure(type);
  Figure_t *temp = createFigure(7);

  rotateFigure(currentFigure, &gameInfo);

  temp->shape[2][1] = 1;
  temp->shape[2][2] = 1;
  temp->shape[3][1] = 1;
  temp->shape[3][2] = 1;

  int flag = true;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (temp->shape[i][j] != currentFigure->shape[i][j]) flag = false;
    }
  }
  ck_assert_int_eq(flag, true);

  destroyFigure(temp);
  destroyFigure(currentFigure);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_rotation_T_1) {
  GameInfo_t gameInfo = {0};
  bool gameRunning = true;

  initGame(&gameInfo, &gameRunning);
  int type = 4;
  Figure_t *currentFigure = createFigure(type);
  Figure_t *temp = createFigure(7);

  rotateFigure(currentFigure, &gameInfo);

  temp->shape[2][1] = 1;
  temp->shape[1][2] = 1;
  temp->shape[2][2] = 1;
  temp->shape[3][2] = 1;

  int flag = true;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (temp->shape[i][j] != currentFigure->shape[i][j]) flag = false;
    }
  }
  ck_assert_int_eq(flag, true);

  destroyFigure(temp);
  destroyFigure(currentFigure);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_rotation_T_2) {
  GameInfo_t gameInfo = {0};
  bool gameRunning = true;

  initGame(&gameInfo, &gameRunning);
  int type = 4;
  Figure_t *currentFigure = createFigure(type);
  Figure_t *temp = createFigure(7);

  rotateFigure(currentFigure, &gameInfo);
  rotateFigure(currentFigure, &gameInfo);

  temp->shape[2][1] = 1;
  temp->shape[1][0] = 1;
  temp->shape[1][1] = 1;
  temp->shape[1][2] = 1;
  int flag = true;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (temp->shape[i][j] != currentFigure->shape[i][j]) flag = false;
    }
  }
  ck_assert_int_eq(flag, true);

  destroyFigure(temp);
  destroyFigure(currentFigure);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_rotation_T_3) {
  GameInfo_t gameInfo = {0};
  bool gameRunning = true;

  initGame(&gameInfo, &gameRunning);
  int type = 4;
  Figure_t *currentFigure = createFigure(type);
  Figure_t *temp = createFigure(7);

  rotateFigure(currentFigure, &gameInfo);
  rotateFigure(currentFigure, &gameInfo);
  rotateFigure(currentFigure, &gameInfo);

  temp->shape[2][1] = 1;
  temp->shape[1][0] = 1;
  temp->shape[2][0] = 1;
  temp->shape[3][0] = 1;
  int flag = true;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (temp->shape[i][j] != currentFigure->shape[i][j]) flag = false;
    }
  }
  ck_assert_int_eq(flag, true);

  destroyFigure(temp);
  destroyFigure(currentFigure);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_rotation_T_4) {
  GameInfo_t gameInfo = {0};
  bool gameRunning = true;

  initGame(&gameInfo, &gameRunning);
  int type = 4;
  Figure_t *currentFigure = createFigure(type);
  Figure_t *temp = createFigure(7);

  rotateFigure(currentFigure, &gameInfo);
  rotateFigure(currentFigure, &gameInfo);
  rotateFigure(currentFigure, &gameInfo);
  rotateFigure(currentFigure, &gameInfo);

  temp->shape[2][1] = 1;
  temp->shape[3][0] = 1;
  temp->shape[3][1] = 1;
  temp->shape[3][2] = 1;
  int flag = true;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (temp->shape[i][j] != currentFigure->shape[i][j]) flag = false;
    }
  }
  ck_assert_int_eq(flag, true);

  destroyFigure(temp);
  destroyFigure(currentFigure);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_rotation_LeftZ_1) {
  GameInfo_t gameInfo = {0};
  bool gameRunning = true;
  Figure_t *currentFigure = {0};

  initGame(&gameInfo, &gameRunning);
  int type = 5;
  currentFigure = createFigure(type);

  rotateFigure(currentFigure, &gameInfo);

  int flag = true;
  Figure_t *temp = createFigure(7);
  temp->shape[1][1] = 1;
  temp->shape[2][1] = 1;
  temp->shape[2][0] = 1;
  temp->shape[3][0] = 1;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (temp->shape[i][j] != currentFigure->shape[i][j]) flag = false;
    }
  }
  ck_assert_int_eq(flag, true);
  destroyFigure(temp);
  destroyFigure(currentFigure);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_rotation_LeftZ_2) {
  GameInfo_t gameInfo = {0};
  bool gameRunning = true;
  Figure_t *currentFigure = {0};

  initGame(&gameInfo, &gameRunning);
  int type = 5;
  currentFigure = createFigure(type);

  rotateFigure(currentFigure, &gameInfo);
  rotateFigure(currentFigure, &gameInfo);

  int flag = true;
  Figure_t *temp = createFigure(7);
  temp->shape[1][0] = 1;
  temp->shape[1][1] = 1;
  temp->shape[2][1] = 1;
  temp->shape[2][2] = 1;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (temp->shape[i][j] != currentFigure->shape[i][j]) flag = false;
    }
  }

  ck_assert_int_eq(flag, true);
  destroyFigure(temp);
  destroyFigure(currentFigure);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_rotation_RightZ_1) {
  GameInfo_t gameInfo = {0};
  bool gameRunning = true;
  Figure_t *currentFigure = {0};

  initGame(&gameInfo, &gameRunning);
  int type = 6;
  currentFigure = createFigure(type);

  rotateFigure(currentFigure, &gameInfo);

  int flag = true;
  Figure_t *temp = createFigure(7);
  temp->shape[1][0] = 1;
  temp->shape[2][1] = 1;
  temp->shape[2][0] = 1;
  temp->shape[3][1] = 1;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (temp->shape[i][j] != currentFigure->shape[i][j]) flag = false;
    }
  }

  ck_assert_int_eq(flag, true);
  destroyFigure(temp);
  destroyFigure(currentFigure);
  freeGame(&gameInfo);
}
END_TEST

START_TEST(test_rotation_RightZ_2) {
  GameInfo_t gameInfo = {0};
  bool gameRunning = true;
  Figure_t *currentFigure = {0};

  initGame(&gameInfo, &gameRunning);
  int type = 6;
  currentFigure = createFigure(type);

  rotateFigure(currentFigure, &gameInfo);
  rotateFigure(currentFigure, &gameInfo);

  int flag = true;
  Figure_t *temp = createFigure(7);
  temp->shape[1][1] = 1;
  temp->shape[1][2] = 1;
  temp->shape[2][1] = 1;
  temp->shape[2][0] = 1;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (temp->shape[i][j] != currentFigure->shape[i][j]) flag = false;
    }
  }

  ck_assert_int_eq(flag, true);
  destroyFigure(temp);
  destroyFigure(currentFigure);
  freeGame(&gameInfo);
}
END_TEST

Suite *test_rotation_suite(void) {
  Suite *s;
  s = suite_create("\033[33mstest_rotation_figure\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("test_rotation_figure");
  tcase_add_test(tc_core, test_rotation_O_1);
  tcase_add_test(tc_core, test_rotation_O_2);
  tcase_add_test(tc_core, test_rotation_LeftG_1);
  tcase_add_test(tc_core, test_rotation_LeftG_2);
  tcase_add_test(tc_core, test_rotation_LeftG_3);
  tcase_add_test(tc_core, test_rotation_LeftG_4);
  tcase_add_test(tc_core, test_rotation_RightG_1);
  tcase_add_test(tc_core, test_rotation_RightG_2);
  tcase_add_test(tc_core, test_rotation_RightG_3);
  tcase_add_test(tc_core, test_rotation_RightG_4);
  tcase_add_test(tc_core, test_rotation_N_1);
  tcase_add_test(tc_core, test_rotation_T_1);
  tcase_add_test(tc_core, test_rotation_T_2);
  tcase_add_test(tc_core, test_rotation_T_3);
  tcase_add_test(tc_core, test_rotation_T_4);
  tcase_add_test(tc_core, test_rotation_LeftZ_1);
  tcase_add_test(tc_core, test_rotation_LeftZ_2);
  tcase_add_test(tc_core, test_rotation_RightZ_1);
  tcase_add_test(tc_core, test_rotation_RightZ_2);

  suite_add_tcase(s, tc_core);
  return s;
}
