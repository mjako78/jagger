#include <stdio.h>
#include <jagger/jagger.h>

int jagger_init(const unsigned int mode, const unsigned int level, const char *log_file) {
  // printf("mode    : %d\n", mode);
  // printf("level   : %d\n", level);
  // printf("log_file: %s\n", log_file);
  if ((mode & LOG_MODE_FILE) && log_file == NULL) {
    // perror("No filename specified!");
    return 0;
  }

  return 1;
}
