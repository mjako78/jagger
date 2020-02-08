#pragma once

#ifndef JAGGER_H
#define JAGGER_H

#define JAGGER_VERSION "0.3.0"

// Constants; mode and level
#define LOG_MODE_OFF      0x00000000
#define LOG_MODE_CONSOLE  0x00000001
#define LOG_MODE_FILE     0x00000010
#define LOG_MODE_CURRENT  0x10000000
#define LOG_LEVEL_NONE    0x00000000
#define LOG_LEVEL_TRACE   0x00000001
#define LOG_LEVEL_DEBUG   0x00000010
#define LOG_LEVEL_INFO    0x00000100
#define LOG_LEVEL_WARNING 0x00001000
#define LOG_LEVEL_ERROR   0x00010000
#define LOG_LEVEL_FATAL   0x00100000
#define LOG_LEVEL_CURRENT 0x10000000
#define LOG_ROLL_NONE     0x00000000
#define LOG_ROLL_SIZE     0x00000001
#define LOG_ROLL_DAILY    0x00000010
#define LOG_ROLL_CURRENT  0x10000000

#define JAGGER_INI_FILENAME "jagger.ini"

int jagger_init(const unsigned int mode, const unsigned int level, const char *log_file);
int jagger_rolling_init(const unsigned int mode, const unsigned int level, const char *log_file, const unsigned int roll_mode, const unsigned int max_size);
int jagger_config_init();
int jagger_close();
int log_message(const unsigned int level, const char *message, ...);
int log_trace(const char *message, ...);
int log_debug(const char *message, ...);
int log_info(const char *message, ...);
int log_warning(const char *message, ...);
int log_error(const char *message, ...);
int log_fatal(const char *message, ...);

#endif
