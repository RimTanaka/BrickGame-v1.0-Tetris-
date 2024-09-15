#ifndef TEST_HED
#define TEST_HED

#include <check.h>
#include <time.h>

#include "../brick_game/tetris/tetris.h"

Suite *test_game_state_suite(void);
Suite *test_handle_running_suite(void);
Suite *test_rotation_suite(void);
Suite *test_upd_currentState_suite(void);
Suite *test_score_suite(void);

#endif
