#include <stdio.h>
#include <string.h>
#include <doctest/doctest.h>
#include "jagger/jagger.h"
#include "config_loader.h"
#include "fake_inis.h"

TEST_SUITE("config_loader") {
  TEST_CASE("toupcase" * doctest::description("convert string into uppercase")) {
    char s[100] = "sample string";
    touppercase(s);
    CHECK(strcmp(s, "SAMPLE STRING") == 0);
  }

  TEST_CASE("tolowercase" * doctest::description("convert string into lowercase")) {
    char s[100] = "SAMPLE STRING";
    tolowercase(s);
    CHECK(strcmp(s, "sample string") == 0);
  }

  TEST_CASE("get_values" * doctest::description("get configuration values")) {
    jconfig cfg;
    sample_cfg(&cfg);

    SUBCASE("get_mode") {
      CHECK(config_get_mode(cfg) == (LOG_MODE_CONSOLE | LOG_MODE_FILE));
    }

    SUBCASE("get_level") {
      CHECK(config_get_level(cfg) == LOG_LEVEL_DEBUG);
    }

    SUBCASE("get_rolling") {
      CHECK(config_get_rolling(cfg) == LOG_ROLL_SIZE);
    }
  }

  TEST_CASE("get_filename" * doctest::description("get filename")) {
    jconfig cfg;

    SUBCASE("when_mode_is_file") {
      sample_cfg(&cfg);
      CHECK(strcmp(config_get_filename(cfg), "jagger.log") == 0);
    }

    SUBCASE("when_mode_is_console") {
      sample_cfg_console_only(&cfg);
      CHECK(!config_get_filename(cfg));
    }
  }

  TEST_CASE("get_maxsize" * doctest::description("get logfile max size")) {
    jconfig cfg;

    SUBCASE("when_mode_is_console") {
      sample_cfg_console_only(&cfg);
      CHECK(config_get_maxsize(cfg) == 0);
    }

    SUBCASE("when_mode_is_rolling_daily") {
      sample_cfg_roll_daily(&cfg);
      CHECK(config_get_maxsize(cfg) == 0);
    }

    SUBCASE("when_mode_is_rolling_size") {
      sample_cfg(&cfg);
      CHECK(config_get_maxsize(cfg) == 1);
    }
  }
}