# ROOT stuff
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED)

# build libStellarYield shared library
add_library(StellarYield SHARED yield.cpp star.cpp stellarYield.cpp)
