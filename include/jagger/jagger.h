#pragma once

#ifndef JAGGER_H
#define JAGGER_H

#define JAGGER_VERSION "0.1.0"

// Constants; mode and level
#define LOG_MODE_OFF      0x00000000
#define LOG_MODE_CONSOLE  0x00000001
#define LOG_MODE_FILE     0x00000010
#define LOG_LEVEL_TRACE   0x00000001
#define LOG_LEVEL_DEBUG   0x00000010
#define LOG_LEVEL_INFO    0x00000100
#define LOG_LEVEL_WARNING 0x00001000
#define LOG_LEVEL_ERROR   0x00010000
#define LOG_LEVEL_FATAL   0x00100000

int jagger_init(const unsigned int mode, const unsigned int level, const char *log_file);

#endif