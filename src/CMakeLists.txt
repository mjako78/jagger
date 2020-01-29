### Main library

# Add additional cmake module
include(FetchContent)

# Download cwalk library
FetchContent_Declare(
  cwalk
  GIT_REPOSITORY https://github.com/likle/cwalk.git
  GIT_TAG        master
)
FetchContent_GetProperties(cwalk)
if(NOT cwalk_POPULATED)
  FetchContent_Populate(cwalk)
  message(STATUS "cwalk source dir: ${cwalk_SOURCE_DIR}")
  message(STATUS "cwalk binary dir: ${cwalk_BINARY_DIR}")
  add_subdirectory(${cwalk_SOURCE_DIR} ${cwalk_BINARY_DIR})
endif()

# Download tinydir library
FetchContent_Declare(
  tinydir
  GIT_REPOSITORY https://github.com/cxong/tinydir.git
  GIT_TAG        master
)
FetchContent_GetProperties(tinydir)
if(NOT tinydir_POPULATED)
  FetchContent_Populate(tinydir)
  message(STATUS "tinydir source dir: ${tinydir_SOURCE_DIR}")
  message(STATUS "tinydir binary dir: ${tinydir_BINARY_DIR}")
endif()

# Define headers location
# set(HEADER_LIST "${jagger_SOURCE_DIR}/include/jagger/jagger.h")
# For CMake >= 3.12, we can use glob
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${jagger_SOURCE_DIR}/include/jagger/*.h")
file(GLOB SRC_LIST CONFIGURE_DEPENDS "${jagger_SOURCE_DIR}/src/*.cpp")

# Make a library
if(MSVC)
  # On Windows make static library
  add_library(jagger STATIC ${SRC_LIST} ${HEADER_LIST})
else()
  # On Unix make shared library
  add_library(jagger SHARED ${SRC_LIST} ${HEADER_LIST})
endif()

# Headers directory
target_include_directories(jagger PUBLIC ../include)
include_directories(${cwalk_SOURCE_DIR}/include ${tinydir_SOURCE_DIR})

# Dependencies
target_link_libraries(jagger PRIVATE cwalk)

# At least C++11
target_compile_features(jagger PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})
