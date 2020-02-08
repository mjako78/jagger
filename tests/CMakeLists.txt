### Testing library

# Using C++11 in the test
add_definitions("-std=c++11")

# Using conan for dependencies
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Download whereami library via FetchContent CMake module
include(FetchContent)
FetchContent_Declare(
  whereami
  GIT_REPOSITORY https://github.com/gpakosz/whereami.git
  GIT_TAG        master
)
FetchContent_GetProperties(whereami)
if (NOT whereami_POPULATED)
  FetchContent_Populate(whereami)
  message(STATUS "whereami source dir: ${whereami_SOURCE_DIR}")
  message(STATUS "whereami binary dir: ${whereami_BINARY_DIR}")
endif()

# Download inih library
FetchContent_Declare(
  inih
  GIT_REPOSITORY https://github.com/benhoyt/inih.git
  GIT_TAG        master
)
FetchContent_GetProperties(inih)
if (NOT inih_POPULATED)
  FetchContent_Populate(inih)
  message(STATUS "inih source dir: ${inih_SOURCE_DIR}")
  message(STATUS "inih binary dir: ${inih_BINARY_DIR}")
endif()

# Tests need to be added as executables first
# add_executable(testlib testlib.cpp)

# Should be linked to the main library, as well as the Doctest testing library
# target_link_libraries(testlib PRIVATE jagger ${CONAN_LIBS})

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
# add_test(NAME testlibtest COMMAND testlib) # Command can be a target

# Using foreach; each source file will be compiled into his own executable
# file(GLOB TEST_SOURCES "*.cpp")
# foreach(test_srcfile ${TEST_SOURCES})
#   get_filename_component(testname ${test_srcfile} NAME_WE)
#   add_executable(${testname} ${test_srcfile})
#   target_link_libraries(${testname} PRIVATE jagger ${CONAN_LIBS})
# endforeach()

include_directories(${whereami_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src ${inih_SOURCE_DIR})

# Using DOCTEST_CONFIG_IMPLEMENT; one main to rule them all :)
file(GLOB TEST_SOURCES "*_test.cpp")
add_executable(testsuite main.cpp ${TEST_SOURCES}
  utils.cpp
  fake_inis.cpp
  ${whereami_SOURCE_DIR}/src/whereami.c
)
target_link_libraries(testsuite PRIVATE jagger ${CONAN_LIBS})
