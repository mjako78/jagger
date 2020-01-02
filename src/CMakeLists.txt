### Main library

# Define headers location
# set(HEADER_LIST "${jagger_SOURCE_DIR}/include/jagger/jagger.h")
# For CMake >= 3.12, we can use glob
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${jagger_SOURCE_DIR}/include/jagger/*.h")

# Make a library
add_library(jagger SHARED jagger.cpp ${HEADER_LIST})

# Headers directory
target_include_directories(jagger PUBLIC ../include)

# Dependencies
# target_link_libraries(jagger PRIVATE Boost::boost)

# At least C++11
target_compile_features(jagger PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})
