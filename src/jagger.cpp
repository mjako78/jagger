#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <jagger/jagger.h>
#include "rolling.h"

// Private methods
void current_ts(char *timestamp) {
  time_t now = time(0);
  struct tm ts;
  ts = *localtime(&now);
  char buffer[20];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %X", &ts);
  strcpy(timestamp, buffer);
}

unsigned long file_size(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL)
    return 0;
  fseek(file, 0, SEEK_END);
  unsigned long size = ftell(file);
  fclose(file);
  return size;
}

static void jagger_write_log_console(FILE *output,
  const char *timestamp,
  const char *level_name,
  const char *message
) {
  // printf("--> jagger_write_log_console called <--\n");
  // printf("... timestamp : %s\n", timestamp);
  // printf("... level_name: %s\n", level_name);
  // printf("... message   : %s\n", message);
  fprintf(output, "%s - %-10s %s\n", timestamp, level_name, message);
  fflush(output);
}

static void jagger_write_log_file(FILE *log_file,
  const char *timestamp,
  const char *level_name,
  const char *message
) {
  // printf("--> jagger_write_log_file called <--\n");
  // printf("... timestamp : %s\n", timestamp);
  // printf("... level_name: %s\n", level_name);
  // printf("... message   : %s\n", message);
  if (log_file != NULL) {
    fprintf(log_file, "%s - %-10s %s\n", timestamp, level_name, message);
    fflush(log_file);
  }
}

static int jagger_write_log(const unsigned int init_mode,
  const unsigned int init_level,
  const char *init_log_file,
  const unsigned int level,
  const char *message
) {
  // Initialize static variables
  FILE *curr_log_file = NULL;
  static unsigned int curr_mode = LOG_MODE_OFF;
  static unsigned int curr_level = LOG_LEVEL_NONE;
  static const char *curr_log_filepath = NULL;

  // printf("\n*** JAGGER_WRITE_LOG ***\n");
  // printf("--> init_mode        : %d\n", init_mode);
  // printf("--> init_level       : %d\n", init_level);
  // printf("--> init_log_file    : %s\n", init_log_file);
  // printf("--> level            : %d\n", level);
  // printf("--> message          : %s\n", message);
  // printf("--> curr_mode        : %d\n", curr_mode);
  // printf("--> curr_level       : %d\n", curr_level);
  // printf("--> curr_log_filepath: %s\n", curr_log_filepath);

  if (init_mode == LOG_MODE_OFF &&
    init_level == LOG_LEVEL_NONE &&
    init_log_file == NULL &&
    level == LOG_LEVEL_NONE &&
    message == NULL
  ) {
    // Close logging
    // printf("--> close logging\n");
    curr_mode = LOG_MODE_OFF;
    curr_level =LOG_LEVEL_NONE;
    curr_log_filepath = NULL;
    return 1;
  }

  char now[100];
  current_ts(now);

  // Set current mode and level
  if (init_mode != LOG_MODE_CURRENT)
    curr_mode = init_mode;
  if (init_level != LOG_LEVEL_CURRENT)
    curr_level = init_level;

  if (curr_mode == LOG_MODE_OFF && curr_level == LOG_LEVEL_NONE) {
    // Not initialized; abort
    // printf("--> not initialized; abort\n");
    return 0;
  }

  if (init_log_file != NULL) {
    if (curr_log_filepath == NULL) {
      curr_log_filepath = init_log_file;
    } else {
      // Already initialized; abort
      // perror("Error - jagger already initialized!")
      // printf("--> already initialized; abort\n");
      return 0;
    }
  }

  if (curr_log_filepath != NULL) {
    if ((curr_log_file = fopen(curr_log_filepath, "a+")) == NULL) {
      // Unable to open log file in append mode; abort
      // fprintf(stderr, "%s - ", curr_log_filepath);
      // perror("Error opening log file");
      curr_log_filepath = NULL;
      // printf("--> unable to open log file; abort\n");
      return 0;
    }
  }

  // Write message to expected output if level compatible
  if (curr_level <= level) {
    // printf("--> curr_level<=level\n");
    char *level_name = NULL;
    switch(level) {
    case LOG_LEVEL_TRACE:
      level_name = (char *) "TRACE";
      break;
    case LOG_LEVEL_DEBUG:
      level_name = (char *) "DEBUG";
      break;
    case LOG_LEVEL_INFO:
      level_name = (char *) "INFO";
      break;
    case LOG_LEVEL_WARNING:
      level_name = (char *) "WARNING";
      break;
    case LOG_LEVEL_ERROR:
      level_name = (char *) "ERROR";
      break;
    case LOG_LEVEL_FATAL:
      level_name = (char *) "FATAL";
      break;
    default:
      level_name = (char *) "NONE";
      break;
    }
    if (message != NULL) {
      // printf("--> message!=NULL\n");
      if (curr_mode & LOG_MODE_CONSOLE) {
        // printf("--> log_to_console\n");
        FILE *output = NULL;
        if (level & LOG_LEVEL_WARNING || level & LOG_LEVEL_ERROR || level & LOG_LEVEL_FATAL)
          output = stderr;
        else
          output = stdout;
        jagger_write_log_console(output, now, level_name, message);
      }
      if (curr_mode & LOG_MODE_FILE) {
        // printf("--> log_to_file\n");
        jagger_write_log_file(curr_log_file, now, level_name, message);
      }
    }
  }

  // Try to close log file
  if (curr_log_file != NULL && curr_log_filepath != NULL) {
    if (fclose(curr_log_file) != 0) {
      // perror("Error closing log file");
      // printf("--> unable to close log file; abort\n");
      return 0;
    }
  }
  // printf("*****\n");

  return 1;
}

int internal_log_message(const unsigned int level, const char *message, va_list params, va_list params_copy) {
  // printf("*** internal_log_message ***\n");
  // printf("--> level: %d\n", level);
  // printf("--> message: %s\n", message);
  char *out = NULL;
  size_t out_len = vsnprintf(NULL, 0, message, params);
  out = (char *) malloc((out_len + 1) * sizeof(char));
  if (out == NULL)
    return 0;
  vsnprintf(out, (out_len + 1), message, params_copy);
  // printf("--> out: %s\n", out);
  // printf("*****\n");
  int rc = jagger_write_log(LOG_MODE_CURRENT, LOG_LEVEL_CURRENT, NULL, level, out);
  free(out);
  return rc;
}

// Library methods
int jagger_init(const unsigned int mode,
  const unsigned int level,
  const char *log_file
) {
  if ((mode & LOG_MODE_FILE) && log_file == NULL) {
    // perror("No filename specified!");
    return 0;
  }

  return jagger_write_log(mode, level, log_file, LOG_LEVEL_NONE, NULL);
}

int jagger_rolling_init(const unsigned int mode,
  const unsigned int level,
  const char *log_file,
  const unsigned int roll_mode,
  const unsigned int max_size
) {
  if ((mode & LOG_MODE_FILE) && log_file == NULL) {
    return 0;
  }
  if ((mode & LOG_MODE_CONSOLE) && !(mode & LOG_MODE_FILE)) {
    return 0;
  }
  if ((roll_mode & LOG_ROLL_SIZE) && max_size <= 0) {
    return 0;
  }
  if (roll_mode & LOG_ROLL_SIZE) {
    unsigned long fsize = file_size(log_file);
    unsigned long cutoff_size = max_size * 1024 * 1024;
    if (fsize > cutoff_size) {
      if (roll_file(log_file) == -1)
        return 0;
    }
  }
  return jagger_write_log(mode, level, log_file, LOG_LEVEL_NONE, NULL);
}

int jagger_close() {
  return jagger_write_log(LOG_MODE_OFF, LOG_LEVEL_NONE, NULL, LOG_LEVEL_NONE, NULL);
}

int log_message(const unsigned int level, const char *message, ...) {
  if (message == NULL)
    return 0;
  va_list params, params_copy;
  va_start(params, message);
  va_copy(params_copy, params);
  int rc = internal_log_message(level, message, params, params_copy);
  va_end(params);
  va_end(params_copy);
  return rc;
}

int log_trace(const char *message, ...) {
  if (message == NULL)
    return 0;
  va_list params, params_copy;
  va_start(params, message);
  va_copy(params_copy, params);
  int rc = internal_log_message(LOG_LEVEL_TRACE, message, params, params_copy);
  va_end(params);
  va_end(params_copy);
  return rc;
}

int log_debug(const char *message, ...) {
  if (message == NULL)
    return 0;
  va_list params, params_copy;
  va_start(params, message);
  va_copy(params_copy, params);
  int rc = internal_log_message(LOG_LEVEL_DEBUG, message, params, params_copy);
  va_end(params);
  va_end(params_copy);
  return rc;
}

int log_info(const char *message, ...) {
  if (message == NULL)
    return 0;
  va_list params, params_copy;
  va_start(params, message);
  va_copy(params_copy, params);
  int rc = internal_log_message(LOG_LEVEL_INFO, message, params, params_copy);
  va_end(params);
  va_end(params_copy);
  return rc;
}

int log_warning(const char *message, ...) {
  if (message == NULL)
    return 0;
  va_list params, params_copy;
  va_start(params, message);
  va_copy(params_copy, params);
  int rc = internal_log_message(LOG_LEVEL_WARNING, message, params, params_copy);
  va_end(params);
  va_end(params_copy);
  return rc;
}

int log_error(const char *message, ...) {
  if (message == NULL)
    return 0;
  va_list params, params_copy;
  va_start(params, message);
  va_copy(params_copy, params);
  int rc = internal_log_message(LOG_LEVEL_ERROR, message, params, params_copy);
  va_end(params);
  va_end(params_copy);
  return rc;
}

int log_fatal(const char *message, ...) {
  if (message == NULL)
    return 0;
  va_list params, params_copy;
  va_start(params, message);
  va_copy(params_copy, params);
  int rc = internal_log_message(LOG_LEVEL_FATAL, message, params, params_copy);
  va_end(params);
  va_end(params_copy);
  return rc;
}
