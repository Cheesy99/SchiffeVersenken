# CMake generated Testfile for 
# Source directory: /Users/tobia/Desktop/Uni/Master/C_Project_praktikum/BonusAufgabe_03
# Build directory: /Users/tobia/Desktop/Uni/Master/C_Project_praktikum/BonusAufgabe_03/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[tests]=] "./tests")
set_tests_properties([=[tests]=] PROPERTIES  ENVIRONMENT "CTEST_OUTPUT_ON_FAILURE=1" _BACKTRACE_TRIPLES "/Users/tobia/Desktop/Uni/Master/C_Project_praktikum/BonusAufgabe_03/CMakeLists.txt;60;add_test;/Users/tobia/Desktop/Uni/Master/C_Project_praktikum/BonusAufgabe_03/CMakeLists.txt;0;")
subdirs("_deps/catch2-build")
