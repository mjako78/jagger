#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <doctest/doctest.h>
#include <ini.h>
#include "jagger/jagger.h"
#include "config_loader.h"
#include "fake_inis.h"

TEST_SUITE("config_file") {
  TEST_CASE("load_values_as_uppercase" * doctest::description("should load all string values as uppercase")) {
    // Prepare
    char *executable_path = get_executable_path();
    if (executable_path == NULL) {
      return;
    }
    char ini_filepath[FILENAME_MAX];
    sprintf(ini_filepath, "%s/%s", executable_path, JAGGER_INI_FILENAME);
    free(executable_path);

    CHECK(console_and_file_lowercase() == 1);
    jconfig cfg;
    config_init(&cfg);
    ini_parse(ini_filepath, handler, &cfg);

    CHECK(strcmp(cfg.root_level, VAL_LEVEL_DEBUG) == 0);

    SUBCASE("filename_must_remains_lowercase") {
      CHECK(strcmp(cfg.filename, "jagger.log") == 0);
    }

    config_free(&cfg);
  }

  TEST_CASE("console_only" * doctest::description("should load a console only configuration")) {
    CHECK(console_only() == 1);
    CHECK(jagger_config_init() == 1);
    CHECK(log_info("Sample message") == 1);
    CHECK(jagger_close() == 1);
  }
}