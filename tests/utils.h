#ifndef UTILS_H
#define UTILS_H

// Define common utility methods
void prepare_logdir();
void prepare_fake_logs_with_size(const char *filename, const int size);
int file_contains(const char *filename, const char *string);
int file_exists(const char *filename);
char* read_file(const char *filename);
unsigned long file_size(const char *filename);

#endif
