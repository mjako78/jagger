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
  # launch test suite
  # ./tests/bin/testlib
  run-parts ./tests/bin
  rc=$?
fi

cd $BASE_DIR

exit $rc
