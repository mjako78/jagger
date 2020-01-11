#include <stdio.h>
#include <stdlib.h>

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
