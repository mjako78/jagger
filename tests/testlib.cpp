#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
// #include "../include/jagger/jagger.h"
#include "jagger/jagger.h"

// int factorial(int number) {
//   return number > 1 ? factorial(number - 1) * number : 1;
// }
//
// TEST_CASE("Testing the factorial method") {
//   CHECK(factorial(0) == 1);
//   CHECK(factorial(1) == 1);
//   CHECK(factorial(2) == 2);
//   CHECK(factorial(3) == 6);
//   CHECK(factorial(10) == 3628800);
// }

TEST_CASE("Init console") {
  // TODO: testing logging to console
  CHECK(jagger_init(LOG_MODE_CONSOLE, LOG_LEVEL_DEBUG, NULL) == 1);
}

TEST_CASE("Init file") {
  // TODO: testing logging to file
  CHECK(jagger_init(LOG_MODE_CONSOLE, LOG_LEVEL_DEBUG, "/tmp/file.log") == 1);
}

TEST_CASE("Init file error") {
  // TODO: testing logging to file
  CHECK(jagger_init(LOG_MODE_FILE, LOG_LEVEL_DEBUG, NULL) == 0);
}

TEST_CASE("Init multiple") {
  // TODO: testing logging to both file and console
  CHECK(jagger_init(LOG_MODE_CONSOLE | LOG_MODE_FILE, LOG_LEVEL_DEBUG, "/tmp/file.log") == 1);
}

TEST_CASE("Init multiple and no file specified") {
  // TODO: testing logging to both file and console
  CHECK(jagger_init(LOG_MODE_CONSOLE | LOG_MODE_FILE, LOG_LEVEL_DEBUG, NULL) == 0);
}
