#pragma once

#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

// define available keys
#define KEY_ROOT_LOGGER            "rootLogger"
#define KEY_APPENDER_TYPE          "appender.type"
#define KEY_APPENDER_FILE_FILENAME "appender.file.filename"
#define KEY_APPENDER_FILE_APPEND   "appender.file.append"
#define KEY_APPENDER_FILE_ROLLING  "appender.file.rolling"
#define KEY_APPENDER_FILE_MAXSIZE  "appender.file.maxSize"
// define available values
#define VAL_LEVEL_TRACE            "TRACE"
#define VAL_LEVEL_DEBUG            "DEBUG"
#define VAL_LEVEL_INFO             "INFO"
#define VAL_LEVEL_WARNING          "WARNING"
#define VAL_LEVEL_ERROR            "ERROR"
#define VAL_LEVEL_FATAL            "FATAL"
#define VAL_APPENDER_CONSOLE       "CONSOLE"
#define VAL_APPENDER_FILE          "FILE"
#define VAL_APPENDER_APPEND_TRUE   "TRUE"
#define VAL_APPENDER_APPEND_FALSE  "FALSE"
#define VAL_APPENDER_ROLLING_DAILY "DAILY"
#define VAL_APPENDER_ROLLING_SIZE  "SIZE"

typedef struct {
  const char *root_level;
  int console_appender;
  int file_appender;
  const char *filename;
  int file_append;
  const char *rolling;
  int max_size;
} jconfig;

void touppercase(char *str);
void tolowercase(char *str);
char *get_executable_path();
int handler(void *data, const char *section, const char *name, const char *value);
void config_init(jconfig *cfg);
void config_free(jconfig *cfg);
unsigned int config_get_mode(jconfig cfg);
unsigned int config_get_level(jconfig cfg);
unsigned int config_get_rolling(jconfig cfg);
char *config_get_filename(jconfig cfg);
int config_get_maxsize(jconfig cfg);

#endif