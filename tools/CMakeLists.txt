cmake_minimum_required (VERSION 2.6)
project (AstroTools)
set (AstroTools_VERSION_MAJOR 0)
set (AstroTools_VERSION_MINOR 1)
set(CMAKE_BUILD_TYPE Release)

# set directories
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_BINARY_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin )

# add include directory
include_directories(src)

# add source directory
add_subdirectory(src)
add_subdirectory(tests)

# Link executable against the local lib
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

