#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "jagger/jagger.h"

TEST_SUITE("another_suite") {
  TEST_CASE("case_1") {
    CHECK(jagger_init(LOG_MODE_CONSOLE, LOG_LEVEL_DEBUG, NULL) == 2);
  }
}
