#include <stdio.h>

#include "doctest/doctest.h"

#include "jagger/jagger.h"

TEST_SUITE("log_message") {
  TEST_CASE("not_initialized" * doctest::description("logging message when jagger not initialized")) {
    CHECK(log_message(LOG_LEVEL_DEBUG, "Sample message") == 0);
  }

  TEST_CASE("invalid_message") {
    // Initialize jagger
    jagger_init(LOG_MODE_FILE, LOG_LEVEL_TRACE, NULL);

    SUBCASE("null_message") {
      CHECK(log_message(LOG_LEVEL_DEBUG, NULL) == 0);
    }

    SUBCASE("empty_message") {
      CHECK(log_message(LOG_LEVEL_DEBUG, "") == 0);
    }

    // Close jagger
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
    jagger_init(LOG_MODE_FILE, LOG_LEVEL_DEBUG, "jagger.log");
    CHECK(log_warning("Sample message; param1=%d, param2=%s", 1, "string") == 1);
    jagger_close();
  }
}
