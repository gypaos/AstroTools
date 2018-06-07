# ROOT stuff
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED)

# add the executable
add_executable(testStellarYield testStellarYield.cpp)

# link library rules
target_link_libraries(testStellarYield StellarYield ${ROOT_LIBRARIES})

# install main
#install(PROGRAMS testStellarYield DESTINATION ${CMAKE_BINARY_OUTPUT_DIRECTORY}) 

# execute and check results from test programs
include (CTest)

# libStellarYield case
# test interpolation capability of the Yield class
# interpolation in log10
add_test (Yield_Interpol_log10 testStellarYield)
set_tests_properties (Yield_Interpol_log10 PROPERTIES PASS_REGULAR_EXPRESSION "log10 interpolation 5.52773")
add_test (Yield_InterpolOutRange1_log10 testStellarYield)
set_tests_properties (Yield_InterpolOutRange1_log10 PROPERTIES PASS_REGULAR_EXPRESSION "log10 lower edge 1")
add_test (Yield_InterpolOutRange2_log10 testStellarYield)
set_tests_properties (Yield_InterpolOutRange2_log10 PROPERTIES PASS_REGULAR_EXPRESSION "log10 upper edge 9")
# interpolation in lin
add_test (Yield_Interpol_lin testStellarYield)
set_tests_properties (Yield_Interpol_lin PROPERTIES PASS_REGULAR_EXPRESSION "lin interpolation 5.5")
add_test (Yield_InterpolOutRange1_lin testStellarYield)
set_tests_properties (Yield_InterpolOutRange1_lin PROPERTIES PASS_REGULAR_EXPRESSION "lin lower edge 1")
add_test (Yield_InterpolOutRange2_lin testStellarYield)
set_tests_properties (Yield_InterpolOutRange2_lin PROPERTIES PASS_REGULAR_EXPRESSION "lin upper edge 9")
# getGraph test
#set_tests_properties (YieldGetGraph PROPERTIES PASS_REGULAR_EXPRESSION "x\[3\]=30, y\[3\]=4")
add_test (Yield_GetGraph testStellarYield)
set_tests_properties (Yield_GetGraph PROPERTIES PASS_REGULAR_EXPRESSION "graph size is 9")
# IMF integration
# yield interpolation in log
add_test (Yield_IntegrateIMF1_log10 testStellarYield)
set_tests_properties (Yield_IntegrateIMF1_log10 PROPERTIES PASS_REGULAR_EXPRESSION "log10 IMF uni = 3.00")
add_test (Yield_IntegrateIMF2_log10 testStellarYield)
set_tests_properties (Yield_IntegrateIMF2_log10 PROPERTIES PASS_REGULAR_EXPRESSION "log10 IMF = 4.44596")
# yield interpolation in lin
add_test (Yield_IntegrateIMF1_lin testStellarYield)
set_tests_properties (Yield_IntegrateIMF1_lin PROPERTIES PASS_REGULAR_EXPRESSION "lin IMF uni = 3.00")
add_test (Yield_IntegrateIMF2_lin testStellarYield)
set_tests_properties (Yield_IntegrateIMF2_lin PROPERTIES PASS_REGULAR_EXPRESSION "lin IMF = 4.44865")
# does the Star class operaotors < and == work as expected
add_test (Star_Operator<  testStellarYield)
set_tests_properties (Star_Operator<  PROPERTIES PASS_REGULAR_EXPRESSION "operator< good")
add_test (Star_Operator== testStellarYield)
set_tests_properties (Star_Operator== PROPERTIES PASS_REGULAR_EXPRESSION "operator== good")
# does the StellarYield class operators [] work as expected
add_test (StellarYield_operator[] testStellarYield)
set_tests_properties (StellarYield_operator[] PROPERTIES PASS_REGULAR_EXPRESSION "elements: 335")
# does the StellarYield class readout of LC17 yields work as expected
add_test (StellarYield_ReadLC17_isotope testStellarYield)
set_tests_properties (StellarYield_ReadLC17_isotope PROPERTIES PASS_REGULAR_EXPRESSION "registered stars: 12")
# does the StellarYield class interpolation of LC17 yields work as expected
add_test (StellarYield_EvalLC17_isotope testStellarYield)
set_tests_properties (StellarYield_EvalLC17_isotope PROPERTIES PASS_REGULAR_EXPRESSION "y = 4.32294")
# does the StellarYield class readout of CL13 yields work as expected
add_test (StellarYield_ReadCL13_isotope testStellarYield)
set_tests_properties (StellarYield_ReadCL13_isotope PROPERTIES PASS_REGULAR_EXPRESSION "elements: 291")
# does the StellarYield class interpolation of CL13 yields work as expected
add_test (StellarYield_EvalCL13_isotope_log10 testStellarYield)
set_tests_properties (StellarYield_EvalCL13_isotope_log10 PROPERTIES PASS_REGULAR_EXPRESSION "log10 1H: m = 50, y = 16.0829")
add_test (StellarYield_EvalCL13_isotope_lin testStellarYield)
set_tests_properties (StellarYield_EvalCL13_isotope_lin PROPERTIES PASS_REGULAR_EXPRESSION "lin 1H: m = 50, y = 16.05")
