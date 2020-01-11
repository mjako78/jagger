#ifndef UTILS_H
#define UTILS_H

// Define common utility methods
void prepare_logdir();
int file_contains(const char *filename, const char *string);
char* read_file(const char *filename);

#endif
