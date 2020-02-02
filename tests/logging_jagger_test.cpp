#include <stdio.h>

#include "doctest/doctest.h"

#include "jagger/jagger.h"
#include "utils.h"

TEST_SUITE("log_message") {
  TEST_CASE("not_initialized" * doctest::description("logging message when jagger not initialized")) {
    CHECK(log_message(LOG_LEVEL_DEBUG, "Sample message") == 0);
    jagger_close();
  }

  TEST_CASE("invalid_message") {
    prepare_logdir();
    jagger_init(LOG_MODE_FILE, LOG_LEVEL_TRACE, NULL);

    SUBCASE("null_message") {
      CHECK(log_message(LOG_LEVEL_DEBUG, NULL) == 0);
    }

    SUBCASE("empty_message") {
      CHECK(log_message(LOG_LEVEL_DEBUG, "") == 0);
    }

    jagger_close();
  }

  TEST_CASE("message_with_level" * doctest::description("logging at debug level")) {
    jagger_init(LOG_MODE_CONSOLE, LOG_LEVEL_TRACE, NULL);
    CHECK(log_message(LOG_LEVEL_DEBUG, "Sample message") == 1);
    jagger_close();
  }

  TEST_CASE("info_message" * doctest::description("logging at info level")) {
    jagger_init(LOG_MODE_CONSOLE, LOG_LEVEL_TRACE, NULL);
    CHECK(log_info("Sample message") == 1);
    jagger_close();
  }

  TEST_CASE("warning_message_with_parameters" * doctest::description("logging at warning level with parameters")) {
    prepare_logdir();
    jagger_init(LOG_MODE_FILE, LOG_LEVEL_DEBUG, "test_logs/jagger.log");
    CHECK(log_warning("Sample message; param1=%d, param2=%s", 1, "string") == 1);
    jagger_close();
    CHECK(file_contains("test_logs/jagger.log", "WARNING") == 1);
    CHECK(file_contains("test_logs/jagger.log", "Sample message; param1=1, param2=string") == 1);
  }
}
