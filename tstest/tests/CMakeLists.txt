cmake_minimum_required(VERSION 3.1)

# Get source files
file(
    GLOB_RECURSE 
    SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.[hc]pp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.[hc]
)

# Create executable
add_executable(
    ${TEST_BINARY} 
    ${SOURCES}
)

# Add executable to run by ctest
# TODO: This runs all the tests as one test. Need to use gtest_Add_test function.
add_test(NAME ${TEST_BINARY} COMMAND ${TEST_BINARY})

# Add tests folder to targets include directories
target_include_directories(
    ${TEST_BINARY}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Add libraries to link
target_link_libraries(
    ${TEST_BINARY}
    PRIVATE
    ${LIB}
    gtest
    gmock
)

# Setup code coverage
target_code_coverage(
    ${TEST_BINARY}
    EXCLUDE 
    ${CMAKE_CURRENT_SOURCE_DIR}/*
    ${PROJECT_SOURCE_DIR}/third_party/*
)