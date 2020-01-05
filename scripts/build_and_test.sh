#!/bin/bash

BASE_DIR=`pwd`

# cd to build directory and build project
cd build
printf "\n### BUILD PROJECT ###\n\n"
cmake --build . --config Release

# check for successfull build
rc=$?
if [ "$rc" -eq 0 ]; then
  printf "\n### LAUNCH TESTS ###\n\n"
  # ./tests/bin/testlib
  # run-parts ./tests/bin
  # launch test suite
  ./tests/bin/testsuite
  rc=$?
fi

cd $BASE_DIR

exit $rc
