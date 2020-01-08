#include <stdio.h>

#include "doctest/doctest.h"

#include "jagger/jagger.h"

TEST_SUITE("log_message") {
  TEST_CASE("exception" * doctest::description("logging message when jagger not initialized")) {
    CHECK_THROWS(log_message(LOG_LEVEL_DEBUG, "Sample message"));
  }

  TEST_CASE("message_with_level" * doctest::description("logging at debug level")) {
    // Initialize jagger
    CHECK_NOTHROW(log_message(LOG_LEVEL_DEBUG, "Sample message"));
    // Close jagger
  }

  TEST_CASE("info_message" * doctest::description("logging at info level")) {
    // Initialize jagger
    CHECK_NOTHROW(log_info("Sample message"));
    // Close jagger
  }
}
