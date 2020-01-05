### Testing library

# Using C++11 in the test
add_definitions("-std=c++11")

# Using conan for dependencies
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Tests need to be added as executables first
# add_executable(testlib testlib.cpp)

# Should be linked to the main library, as well as the Doctest testing library
# target_link_libraries(testlib PRIVATE jagger ${CONAN_LIBS})

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
# add_test(NAME testlibtest COMMAND testlib) # Command can be a target

# Using foreach
file(GLOB TEST_SOURCES "*.cpp")
foreach(test_srcfile ${TEST_SOURCES})
  get_filename_component(testname ${test_srcfile} NAME_WE)
  add_executable(${testname} ${test_srcfile})
  target_link_libraries(${testname} PRIVATE jagger ${CONAN_LIBS})
endforeach()
