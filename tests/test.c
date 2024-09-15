#include "test.h"

int main() {
  srand(time(NULL));
  int all = 0, successed = 0, failed = 0;
  Suite *suite[] = {test_game_state_suite(), test_handle_running_suite(),
                    test_rotation_suite(),   test_upd_currentState_suite(),
                    test_score_suite(),      NULL};

  for (int i = 0; suite[i] != NULL; i++) {
    SRunner *sr = srunner_create(suite[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    all += srunner_ntests_run(sr);
    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }

  successed = all - failed;

  printf(
      "========= ALL: %d ========= SUCCESSED: %d ========= FAILED: %d "
      "=========\n",
      all, successed, failed);
  return failed == 0 ? 0 : 1;
}
