#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void prepare_logdir() {
  #ifdef _WIN32
    system("rmdir /S /Q test_logs 2> nul");
    system("mkdir test_logs 2> nul");
  #else
    system("rm -rf test_logs 2> /dev/null");
    system("mkdir test_logs 2> /dev/null");
  #endif
}

void prepare_fake_logs_with_size(const char *filename, const int size) {
  const char *log_line = "2020-01-12 22:00:39 - INFO       Sample message";
  int line_len = strlen(log_line);
  FILE *file = fopen(filename, "w");
  unsigned long file_size = 0;
  unsigned long max_size = size * 1024 * 1024;
  while (file_size < max_size) {
    fprintf(file, "%s\n", log_line);
    file_size = file_size + line_len;
  }
  fclose(file);
}

int file_contains(const char *filename, const char *string) {
  char *file_content = read_file(filename);
  return strstr(file_content, string) != NULL ? 1 : 0;
}

int file_exists(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL)
    return 0;
  fclose(file);
  return 1;
}

char* read_file(const char *filename) {
  char *buffer = NULL;
  int string_size, read_size;
  FILE *file = fopen(filename, "r");
  if (file == NULL)
    return NULL;
  // Seek end of file to retrieve size; then rewind
  fseek(file, 0, SEEK_END);
  string_size = ftell(file);
  rewind(file);
  // Allocate memory to store file content
  buffer = (char *) malloc(sizeof(char) * (string_size + 1));
  read_size = fread(buffer, sizeof(char), string_size, file);
  buffer[string_size] = '\0';
  if (string_size != read_size) {
    // Something went wrong, throw away buffer and set buffer to null
    free(buffer);
    buffer = NULL;
  }
  fclose(file);
  return buffer;
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
