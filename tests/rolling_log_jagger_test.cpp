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

    SUBCASE("wrong size specified") {
      CHECK(jagger_rolling_init(LOG_MODE_FILE, LOG_LEVEL_INFO, "test_logs/jagger.log", LOG_ROLL_SIZE, 0) == 0);
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
    prepare_logdir();
    prepare_fake_logs_with_size("test_logs/jagger.log", 1);

    SUBCASE("no archived log exists yet") {
      unsigned long fsize_before = file_size("test_logs/jagger.log");
      CHECK(jagger_rolling_init(LOG_MODE_FILE, LOG_LEVEL_INFO, "test_logs/jagger.log", LOG_ROLL_SIZE, 1) == 1);
      CHECK(log_error("Error; something went wrong") == 1);
      CHECK(jagger_close() == 1);
      unsigned long fsize_after = file_size("test_logs/jagger.log");
      CHECK(file_contains("test_logs/jagger.log", "Error") == 1);
      CHECK(file_contains("test_logs/jagger.log", "Error; something went wrong") == 1);
      CHECK(file_size("test_logs/jagger.log") < 1024 * 1024);
      CHECK(fsize_after < fsize_before);
      CHECK(file_exists("test_logs/jagger.1.log") == 1);
    }

    SUBCASE("an archived log already exists") {
      prepare_fake_logs_with_size("test_logs/jagger.1.log", 1);
      CHECK(jagger_rolling_init(LOG_MODE_FILE, LOG_LEVEL_INFO, "test_logs/jagger.log", LOG_ROLL_SIZE, 1) == 1);
      CHECK(log_error("Error; something went wrong") == 1);
      CHECK(jagger_close() == 1);
      CHECK(file_contains("test_logs/jagger.log", "ERROR") == 1);
      CHECK(file_contains("test_logs/jagger.log", "Error; something went wrong") == 1);
      CHECK(file_size("test_logs/jagger.log") < 1024 * 1024);
      CHECK(file_exists("test_logs/jagger.2.log") == 1);
    }
  }

  TEST_CASE("daily" * doctest::description("start new logfile each day")) {
    // If last modified date is before today, rename file as jagger.YYYY-MM-DD.log
    prepare_logdir();

    SUBCASE("no log file exists yet") {
      CHECK(jagger_rolling_init(LOG_MODE_FILE, LOG_LEVEL_INFO, "test_logs/jagger.log", LOG_ROLL_DAILY, 1) == 1);
      CHECK(log_error("Error; something went wrong") == 1);
      CHECK(jagger_close() == 1);
      CHECK(file_contains("test_logs/jagger.log", "Error; something went wrong") == 1);
    }

    SUBCASE("a log file exists yet") {
      prepare_fake_logs_with_date("test_logs/jagger.log");
      CHECK(jagger_rolling_init(LOG_MODE_FILE, LOG_LEVEL_INFO, "test_logs/jagger.log", LOG_ROLL_DAILY, 1) == 1);
      CHECK(log_error("Error; something went wrong") == 1);
      CHECK(jagger_close() == 1);
      CHECK(file_contains("test_logs/jagger.log", "ERROR") == 1);
      CHECK(file_contains("test_logs/jagger.log", "Error; something went wrong") == 1);
      CHECK(file_contains("test_logs/jagger.log", "INFO") == 0);
      CHECK(file_contains("test_logs/jagger.log", "Sample message") == 0);
    }
  }
}
