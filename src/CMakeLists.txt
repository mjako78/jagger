### Main library

# Add custom cmake modules path
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(DownloadProject)

# Download cwalk library
download_project(
  PROJ           cwalk
  GIT_REPOSITORY https://github.com/likle/cwalk.git
  GIT_TAG        stable
)
add_subdirectory(${cwalk_SOURCE_DIR} ${cwalk_BINARY_DIR})

# Define headers location
# set(HEADER_LIST "${jagger_SOURCE_DIR}/include/jagger/jagger.h")
# For CMake >= 3.12, we can use glob
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${jagger_SOURCE_DIR}/include/jagger/*.h")
file(GLOB SRC_LIST CONFIGURE_DEPENDS "${jagger_SOURCE_DIR}/src/*.cpp")

# Make a library
if(MSVC)
  # On Windows make static library
  add_library(jagger STATIC jagger.cpp rolling.cpp ${HEADER_LIST})
  add_library(jagger STATIC ${SRC_LIST} ${HEADER_LIST})
else()
  # On Unix make shared library
  # add_library(jagger SHARED jagger.cpp rolling.cpp ${HEADER_LIST})
  add_library(jagger SHARED ${SRC_LIST} ${HEADER_LIST})
endif()

# Headers directory
target_include_directories(jagger PUBLIC ../include)
include_directories(${cwalk_SOURCE_DIR}/include)

# Dependencies
target_link_libraries(jagger PRIVATE cwalk)

# At least C++11
target_compile_features(jagger PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})
