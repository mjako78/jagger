#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "whereami.h"
#include "config_loader.h"
#include "fake_inis.h"

#define INI_FILENAME "jagger.ini"
#define ROOT_LOGGER_LINE       "rootLogger=DEBUG"
#define APPENDER_TYPE_KEY      "appender.type"
#define APPENDER_FILE_FILENAME "appender.file.filename"
#define APPENDER_FILE_APPEND   "appender.file.append"
#define APPENDER_FILE_ROLLING  "appender.file.rolling"
#define APPENDER_FILE_MAXSIZE  "appender.file.maxSize"

int console_only() {
  char ini_filepath[FILENAME_MAX];
  char *path = get_executable_path();
  if (!path) {
    return 0;
  }
  sprintf(ini_filepath, "%s/%s", path, INI_FILENAME);
  free(path);
  FILE *file;
  file = fopen(ini_filepath, "w");
  if (file == NULL) {
    return 0;
  }
  fprintf(file, "%s\n", ROOT_LOGGER_LINE);
  fprintf(file, "%s=CONSOLE\n", APPENDER_TYPE_KEY);
  fclose(file);
  return 1;
}

int file_basic() {
  char ini_filepath[FILENAME_MAX];
  char *path = get_executable_path();
  if (!path) {
    return 0;
  }
  sprintf(ini_filepath, "%s/%s", path, INI_FILENAME);
  free(path);
  FILE *file = fopen(ini_filepath, "w");
  if (file == NULL) {
    return 0;
  }
  fprintf(file, "%s\n", ROOT_LOGGER_LINE);
  fprintf(file, "%s=FILE\n", APPENDER_TYPE_KEY);
  fprintf(file, "%s=jagger.log\n", APPENDER_FILE_FILENAME);
  fclose(file);
  return 1;
}

int file_full() {
  char ini_filepath[FILENAME_MAX];
  char *path = get_executable_path();
  if (!path)
  {
    return 0;
  }
  sprintf(ini_filepath, "%s/%s", path, INI_FILENAME);
  free(path);
  FILE *file = fopen(ini_filepath, "w");
  if (file == NULL)
  {
    return 0;
  }
  fprintf(file, "%s\n", ROOT_LOGGER_LINE);
  fprintf(file, "%s=FILE\n", APPENDER_TYPE_KEY);
  fprintf(file, "%s=jagger.log\n", APPENDER_FILE_FILENAME);
  fprintf(file, "%s=true\n", APPENDER_FILE_APPEND);
  fprintf(file, "%s=SIZE\n", APPENDER_FILE_ROLLING);
  fprintf(file, "%s=1\n", APPENDER_FILE_MAXSIZE);
  fclose(file);
  return 1;
}

int console_and_file() {
  char ini_filepath[FILENAME_MAX];
  char *path = get_executable_path();
  if (!path)
  {
    return 0;
  }
  sprintf(ini_filepath, "%s/%s", path, INI_FILENAME);
  free(path);
  FILE *file = fopen(ini_filepath, "w");
  if (file == NULL)
  {
    return 0;
  }
  fprintf(file, "%s\n", ROOT_LOGGER_LINE);
  fprintf(file, "%s=FILE,CONSOLE\n", APPENDER_TYPE_KEY);
  fprintf(file, "%s=jagger.log\n", APPENDER_FILE_FILENAME);
  fprintf(file, "%s=true\n", APPENDER_FILE_APPEND);
  fprintf(file, "%s=SIZE\n", APPENDER_FILE_ROLLING);
  fprintf(file, "%s=1\n", APPENDER_FILE_MAXSIZE);
  fclose(file);
  return 1;
}

int console_and_file_lowercase() {
  char ini_filepath[FILENAME_MAX];
  char *path = get_executable_path();
  if (!path)
  {
    return 0;
  }
  sprintf(ini_filepath, "%s/%s", path, INI_FILENAME);
  free(path);
  FILE *file = fopen(ini_filepath, "w");
  if (file == NULL)
  {
    return 0;
  }
  fprintf(file, "rootLogger=debug\n");
  fprintf(file, "%s=file,console\n", APPENDER_TYPE_KEY);
  fprintf(file, "%s=jagger.log\n", APPENDER_FILE_FILENAME);
  fprintf(file, "%s=true\n", APPENDER_FILE_APPEND);
  fprintf(file, "%s=size\n", APPENDER_FILE_ROLLING);
  fprintf(file, "%s=1\n", APPENDER_FILE_MAXSIZE);
  fclose(file);
  return 1;
}

void sample_cfg(jconfig *cfg) {
  cfg->root_level = "DEBUG";
  cfg->console_appender = 1;
  cfg->file_appender = 1;
  cfg->filename = "jagger.log";
  cfg->file_append = 1;
  cfg->rolling = "SIZE";
  cfg->max_size = 1;
}

void sample_cfg_roll_daily(jconfig *cfg) {
  cfg->root_level = "DEBUG";
  cfg->console_appender = 1;
  cfg->file_appender = 1;
  cfg->filename = "jagger.log";
  cfg->file_append = 1;
  cfg->rolling = "DAILY";
  cfg->max_size = 0;
}

void sample_cfg_console_only(jconfig *cfg) {
  cfg->root_level = "DEBUG";
  cfg->console_appender = 1;
  cfg->file_appender = 0;
  cfg->filename = "jagger.log";
  cfg->file_append = 1;
  cfg->rolling = "SIZE";
  cfg->max_size = 1;
}