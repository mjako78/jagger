### Testing library

# Using C++11 in the test
add_definitions("-std=c++11")

# Using conan for dependencies
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Tests need to be added as executables first
add_executable(testlib testlib.cpp)

# Should be linked to the main library, as well as the Doctest testing library
# # target_link_libraries(testlib PRIVATE modern_library Catch2::Catch2)
target_link_libraries(testlib PRIVATE ${CONAN_LIBS})

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME testlibtest COMMAND testlib) # Command can be a target
