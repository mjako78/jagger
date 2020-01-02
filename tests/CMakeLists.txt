# # Testing library
# FetchContent_Declare(
#   doctest
#   GIT_REPOSITORY https://github.com/onqtam/doctest.git
#   GIT_TAG        2.3.6
# )
# FetchContent_MakeAvailable(doctest)
#
# # Tests need to be added as executables first
# add_executable(testlib testlib.cpp)
#
# # I'm using C++17 in the test
# target_compile_features(testlib PRIVATE cxx_std_17)
#
# # Should be linked to the main library, as well as the Doctest testing library
# # target_link_libraries(testlib PRIVATE modern_library Catch2::Catch2)
# target_link_libraries(testlib PRIVATE Catch2::Catch2)
#
# # If you register a test, then ctest and make test will run it.
# # You can also run examples and check the output, as well.
# add_test(NAME testlibtest COMMAND testlib) # Command can be a target

# Using conan for dependencies
add_definitions("-std=c++11")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(testlib testlib.cpp)

# target_compile_features(testlib PRIVATE cxx_std_11)

target_link_libraries(testlib PRIVATE ${CONAN_LIBS})
