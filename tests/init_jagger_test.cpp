#include <stdio.h>

#include "doctest/doctest.h"

#include "jagger/jagger.h"

TEST_SUITE("init_jagger") {
  TEST_CASE("console" * doctest::description("console logging only")) {
    CHECK(jagger_init(LOG_MODE_CONSOLE, LOG_LEVEL_DEBUG, NULL) == 1);
    CHECK(jagger_close() == 1);
  }

  TEST_CASE("file_ok" * doctest::description("file logging only")) {
    CHECK(jagger_init(LOG_MODE_CONSOLE, LOG_LEVEL_DEBUG, "/tmp/jagger.log") == 1);
    CHECK(jagger_close() == 1);
  }

  TEST_CASE("file_error" * doctest::description("file logging only, in error")) {
    CHECK(jagger_init(LOG_MODE_FILE, LOG_LEVEL_DEBUG, NULL) == 0);
    CHECK(jagger_close() == 1);
  }

  TEST_CASE("multiple" * doctest::description("both console and file logging")) {
    CHECK(jagger_init(LOG_MODE_CONSOLE | LOG_MODE_FILE, LOG_LEVEL_DEBUG, "/tmp/jagger.log") == 1);
    CHECK(jagger_close() == 1);
  }

  TEST_CASE("multiple_file_error" * doctest::description("both console and file logging, in error")) {
    CHECK(jagger_init(LOG_MODE_CONSOLE | LOG_MODE_FILE, LOG_LEVEL_DEBUG, NULL) == 0);
    CHECK(jagger_close() == 1);
  }
}
