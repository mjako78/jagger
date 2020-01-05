#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest/doctest.h"

// One single main to rule all tests, splitted into meaningful files
int main(int argc, char **argv) {
  doctest::Context context;
  context.applyCommandLine(argc, argv);

  auto res = context.run();

  return res;
}
