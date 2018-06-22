# ROOT stuff
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIRS})

# build libStellarYield shared library
add_library(StellarYield SHARED yield.cpp star.cpp stellarYield.cpp)

# build libStellarYield shared library
add_library(Isotope SHARED isotope.cpp abundances.cpp nucleusProperties.cpp)

# build libStarClusterMC shared library
add_library(StarClusterMC SHARED starClusterMC.cpp)
