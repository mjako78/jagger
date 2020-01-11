#include <stdio.h>

#include "doctest/doctest.h"

#include "jagger/jagger.h"
#include "utils.h"

TEST_SUITE("rolling_log") {
  TEST_CASE("invalid_configuration") {
    prepare_logdir();

    SUBCASE("no file specified") {
      CHECK(jagger_rolling_init(LOG_MODE_FILE, LOG_LEVEL_INFO, NULL, LOG_ROLL_SIZE, 10) == 0);
    }

    SUBCASE("wrong mode specified") {
      CHECK(jagger_rolling_init(LOG_MODE_CONSOLE, LOG_LEVEL_INFO, NULL, LOG_ROLL_SIZE, 10) == 0);
    }

    CHECK(jagger_close() == 1);
  }

  TEST_CASE("valid_configuration") {
    prepare_logdir();

    SUBCASE("only logging to file") {
      CHECK(jagger_rolling_init(LOG_MODE_FILE, LOG_LEVEL_INFO, "test_logs/jagger.log", LOG_ROLL_SIZE, 10) == 1);
    }

    SUBCASE("logging both to file and console") {
      CHECK(jagger_rolling_init(LOG_MODE_FILE | LOG_MODE_CONSOLE, LOG_LEVEL_INFO, "test_logs/jagger.log", LOG_ROLL_SIZE, 10) == 1);
    }

    CHECK(jagger_close() == 1);
  }

  TEST_CASE("logfile_size" * doctest::description("start new logfile when size reach limit")) {
    // TODO: roll by file size
    prepare_logdir();

    CHECK(jagger_rolling_init(LOG_MODE_FILE, LOG_LEVEL_INFO, "test_logs/jagger.log", LOG_ROLL_SIZE, 10) == 1);
    CHECK(jagger_close() == 1);
  }

  TEST_CASE("daily" * doctest::description("start new logfile each day")) {
    // TODO: roll daily
    prepare_logdir();
  }
}
