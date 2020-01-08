#include <stdio.h>
#include <string.h>
#include <time.h>
#include <jagger/jagger.h>

// Private methods
void current_ts(char *timestamp) {
  time_t now = time(0);
  struct tm ts;
  ts = *localtime(&now);
  char buffer[20];
  strftime(buffer, sizeof(buffer), "%Y-%m-%d %X", &ts);
  strcpy(timestamp, buffer);
}

static void jagger_write_log_console(const char *timestamp,
  const unsigned int level,
  const char *message
) {
  // TODO: logging to console
}

static void jagger_write_log_file(FILE *log_file,
  const char *timestamp,
  const unsigned int level,
  const char *message
) {
  // TODO: logging to console
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

  printf("--> static vars\n");
  printf("... curr_mode        : %d\n", curr_mode);
  printf("... curr_level       : %d\n", curr_level);
  printf("... curr_log_filepath: %s\n", curr_log_filepath);
  printf("... curr_log_file    : %s\n", curr_log_file);

  if (init_mode == LOG_MODE_OFF &&
    init_level == LOG_LEVEL_NONE &&
    init_log_file == NULL &&
    level == LOG_LEVEL_NONE &&
    message == NULL
  ) {
    // Close logging
    curr_mode = LOG_MODE_OFF;
    curr_level =LOG_LEVEL_NONE;
    curr_log_filepath = NULL;
    return 1;
  }

  char now[100];
  current_ts(now);

  printf("--> now: %s\n", now);

  // Set current mode and level
  if (init_mode != LOG_MODE_CURRENT)
    curr_mode = init_mode;
  if (init_level != LOG_LEVEL_CURRENT)
    curr_level = init_level;

  if (curr_mode == LOG_MODE_OFF && curr_level == LOG_LEVEL_NONE) {
    // Not initialized; abort
    printf("--> Not initialized; abort\n");
    return 0;
  }

  if (init_log_file != NULL) {
    if (curr_log_filepath == NULL) {
      curr_log_filepath = init_log_file;
    } else {
      // Already initialized; abort
      // perror("Error - jagger already initialized!")
      printf("--> Already initialized; abort\n");
      return 0;
    }
  }

  if (curr_log_filepath != NULL) {
    if ((curr_log_file = fopen(curr_log_filepath, "a+")) == NULL) {
      // Unable to open log file in append mode; abort
      // fprintf(stderr, "%s - ", curr_log_filepath);
      // perror("Error opening log file");
      curr_log_filepath = NULL;
      printf("--> Error opening log_file\n");
      return 0;
    }
  }

  // Write message to expected output if level compatible
  if (curr_level >= level) {
    printf("--> valid level!\n");
    if (message != NULL) {
      printf("--> valid message!\n");
      if (curr_mode & LOG_MODE_CONSOLE) {
        printf("--> to console!\n");
        jagger_write_log_console(now, level, message);
      }
      if (curr_mode & LOG_MODE_FILE) {
        printf("--> to file!\n");
        jagger_write_log_file(curr_log_file, now, level, message);
      }
    }
  }

  // Try to close log file
  if (curr_log_file != NULL && curr_log_filepath != NULL) {
    if (fclose(curr_log_file) != 0) {
      // perror("Error closing log file");
      printf("--> Error closing log file\n");
      return 0;
    }
  }

  printf("--> Good!\n");
  printf("--> static vars after init\n");
  printf("... curr_mode        : %d\n", curr_mode);
  printf("... curr_level       : %d\n", curr_level);
  printf("... curr_log_filepath: %s\n", curr_log_filepath);
  printf("... curr_log_file    : %s\n", curr_log_file);

  return 1;
}

// Library methods
int jagger_init(const unsigned int mode,
  const unsigned int level,
  const char *log_file
) {
  printf("*** JAGGER_INIT ***\n");
  printf("--> mode    : %d\n", mode);
  printf("--> level   : %d\n", level);
  printf("--> log_file: %s\n", log_file);
  if ((mode & LOG_MODE_FILE) && log_file == NULL) {
    // perror("No filename specified!");
    printf("--> no filename specified\n");
    return 0;
  }

  return jagger_write_log(mode, level, log_file, LOG_LEVEL_NONE, NULL);
}

int jagger_close() {
  return jagger_write_log(LOG_MODE_OFF, LOG_LEVEL_NONE, NULL, LOG_LEVEL_NONE, NULL);
}

void log_message(const unsigned int level, const char *message, ...) {
  // TODO: log message with given level
}

void log_info(const char *message, ...) {
  // TODO: log message at info level
}
