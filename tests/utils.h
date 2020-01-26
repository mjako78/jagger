#ifndef UTILS_H
#define UTILS_H

#define SECONDS_PER_DAY 60 * 60 * 24

// Define common utility methods
void current_ts(char *timestamp);
void prepare_logdir();
void prepare_fake_logs_with_size(const char *filename, const int size);
void prepare_fake_logs_with_date(const char *filename);
void prepare_fake_logs(const char *filename);
int file_contains(const char *filename, const char *string);
int file_exists(const char *filename);
char* read_file(const char *filename);
unsigned long file_size(const char *filename);

#endif
