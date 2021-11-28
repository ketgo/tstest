cmake_minimum_required(VERSION 3.1)

project(tstest VERSION 0.0.1 LANGUAGES CXX)

# Add package modules to cmake module path
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# ------------------------------------------------
# Including C++ Related Modules
# -------------------------------------------------
include(c++-standards)
include(code-coverage)
include(sanitizers)
include(tools)
# --------------------------------------------------

# --------------------------------------------------
# MAIN_PROJECT CHECK: determine if tstest is built 
# as a subproject (using add_subdirectory) or if it 
# is the main project
# --------------------------------------------------
set(MAIN_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(MAIN_PROJECT ON)
endif()

option(PROJECT_BUILD_TESTS "Build the unit tests when BUILD_TESTING is enabled." ${MAIN_PROJECT})
option(PROJECT_BUILD_INSTALL "Install CMake targets during install step." ${MAIN_PROJECT})

if(PROJECT_BUILD_TESTS)
    # Enable testing
    enable_testing()

    # --------------------------------------------------
    # Adding sub-directories to build
    # ---------------------------------------------------
    add_subdirectory(${PROJECT_SOURCE_DIR}/third_party)
    # ----------------------------------------------------
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/tstest)
