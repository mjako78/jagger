#ifndef FAKE_INIS_H
#define FAKE_INIS_H

#include "config_loader.h"

// Utilities to create sample ini configuration file
int console_only();
int file_basic();
int file_full();
int console_and_file();
int console_and_file_lowercase();
// Utilities to create sample configuration struct
void sample_cfg(jconfig *cfg);
void sample_cfg_roll_daily(jconfig *cfg);
void sample_cfg_console_only(jconfig * cfg);

#endif
