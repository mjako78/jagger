#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "whereami.h"
#include "jagger/jagger.h"
#include "config_loader.h"

void touppercase(char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      str[i] = str[i] - 32;
    }
  }
}

void tolowercase(char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      str[i] = str[i] + 32;
    }
  }
}

char *get_executable_path() {
  char *path = NULL;
  int len, dirname_len;
  len = wai_getExecutablePath(NULL, 0, &dirname_len);
  if (len > 0) {
    path = (char *)malloc(len + 1);
    if (!path) {
      return NULL;
    }
    wai_getExecutablePath(path, len, &dirname_len);
    path[len] = '\0';
    path[dirname_len] = '\0';
    return path;
  }
  return NULL;
}

int handler(void *data, const char *section, const char *name,
            const char *value) {
  jconfig *cfg = (jconfig *)data;
  touppercase((char *)value);
  if (strcmp(KEY_ROOT_LOGGER, name) == 0) {
    cfg->root_level = strdup(value);
  }
  if (strcmp(KEY_APPENDER_TYPE, name) == 0) {
    cfg->console_appender = strstr(value, VAL_APPENDER_CONSOLE) != NULL ? 1 : 0;
    cfg->file_appender = strstr(value, VAL_APPENDER_FILE) != NULL ? 1 : 0;
  }
  if (strcmp(KEY_APPENDER_FILE_FILENAME, name) == 0) {
    tolowercase((char *)value);
    cfg->filename = strdup(value);
  }
  if (strcmp(KEY_APPENDER_FILE_APPEND, name) == 0) {
    cfg->file_append = strstr(value, VAL_APPENDER_APPEND_FALSE) != NULL ? 0 : 1;
  } else {
    cfg->file_append = 1;
  }
  if (strcmp(KEY_APPENDER_FILE_ROLLING, name) == 0) {
    if (strstr(value, VAL_APPENDER_ROLLING_SIZE) == 0 ||
        strstr(value, VAL_APPENDER_ROLLING_DAILY) == 0) {
      cfg->rolling = strdup(value);
    }
  }
  if (strcmp(KEY_APPENDER_FILE_MAXSIZE, name) == 0) {
    cfg->max_size = atoi(value);
  }
  return 1;
}

void config_init(jconfig *cfg) {
  cfg->root_level = NULL;
  cfg->console_appender = 0;
  cfg->file_appender = 0;
  cfg->filename = NULL;
  cfg->file_append = 0;
  cfg->rolling = NULL;
  cfg->max_size = 0;
}

void config_free(jconfig *cfg) {
  free((void *)cfg->root_level);
  free((void *)cfg->filename);
  free((void *)cfg->rolling);
  cfg->console_appender = 0;
  cfg->file_appender = 0;
  cfg->file_append = 0;
  cfg->max_size = 0;
}

unsigned int config_get_mode(jconfig cfg) {
  unsigned int mode = LOG_MODE_OFF;
  if (cfg.console_appender == 1) {
    mode |= LOG_MODE_CONSOLE;
  }
  if (cfg.file_appender == 1) {
    mode |= LOG_MODE_FILE;
  }
  return mode;
}

unsigned int config_get_level(jconfig cfg) {
  if (strcmp(cfg.root_level, VAL_LEVEL_TRACE) == 0) {
    return LOG_LEVEL_TRACE;
  }
  if (strcmp(cfg.root_level, VAL_LEVEL_DEBUG) == 0) {
    return LOG_LEVEL_DEBUG;
  }
  if (strcmp(cfg.root_level, VAL_LEVEL_INFO) == 0) {
    return LOG_LEVEL_INFO;
  }
  if (strcmp(cfg.root_level, VAL_LEVEL_WARNING) == 0) {
    return LOG_LEVEL_WARNING;
  }
  if (strcmp(cfg.root_level, VAL_LEVEL_ERROR) == 0) {
    return LOG_LEVEL_ERROR;
  }
  if (strcmp(cfg.root_level, VAL_LEVEL_FATAL) == 0) {
    return LOG_LEVEL_FATAL;
  }
  return LOG_LEVEL_NONE;
}

unsigned int config_get_rolling(jconfig cfg) {
  if (!cfg.rolling) {
    return LOG_ROLL_NONE;
  }
  if (strcmp(cfg.rolling, VAL_APPENDER_ROLLING_DAILY) == 0) {
    return LOG_ROLL_DAILY;
  }
  if (strcmp(cfg.rolling, VAL_APPENDER_ROLLING_SIZE) == 0) {
    return LOG_ROLL_SIZE;
  }
  return LOG_ROLL_NONE;
}

char *config_get_filename(jconfig cfg) {
  return cfg.file_appender ? (char *)cfg.filename : NULL;
}

int config_get_maxsize(jconfig cfg) {
  if (cfg.file_appender == 0) {
    return 0;
  }
  return strcmp(cfg.rolling, VAL_APPENDER_ROLLING_SIZE) == 0 ?
    cfg.max_size :
    0;
}