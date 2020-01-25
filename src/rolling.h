#pragma once

#ifndef ROLLING_G
#define ROLLING_H

int roll_file(const char *filename);
int count_old_logfiles(const char *logdir, const char *logname, const char *logext);
char *strip_extension(const char *filename, const char *ext);

#endif
