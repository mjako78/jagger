#include <stdio.h>

#include "doctest/doctest.h"

#include "jagger/jagger.h"

TEST_SUITE("log_message") {
  TEST_CASE("not_initialized" * doctest::description("logging message when jagger not initialized")) {
    CHECK(log_message(LOG_LEVEL_DEBUG, "Sample message") == 0);
  }

  TEST_CASE("invalid_message") {
    // Initialize jagger
    printf("### INVALID_MESSAGE ###\n");
    printf("--> jagger_init\n");
    jagger_init(LOG_MODE_FILE, LOG_LEVEL_TRACE, NULL);

    SUBCASE("null_message") {
      printf(">>> null_message <<<\n");
      CHECK(log_message(LOG_LEVEL_DEBUG, NULL) == 0);
    }

    SUBCASE("empty_message") {
      printf(">>> empty_message <<<\n");
      CHECK(log_message(LOG_LEVEL_DEBUG, "") == 0);
    }

    // Close jagger
    jagger_close();
    printf("--> jagger_close\n");
    printf("##########\n");
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
    printf("### JAGGER_INIT ###\n");
    jagger_init(LOG_MODE_FILE, LOG_LEVEL_DEBUG, "jagger.log");
    printf("..........\n");
    printf("### LOG_WARNING ###\n");
    CHECK(log_warning("Sample message; param1=%d, param2=%s", 1, "string") == 1);
    printf("..........\n");
    jagger_close();
  }
}
