

cmake_minimum_required(VERSION 3.20)
project(sstruct)

set(CMAKE_CXX_STANDARD 20)

# Directories-------------------------------------

set(SSTRUCT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/sstruct")
set(SSTRUCT_TEST_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tests")

include_directories(
  ${SSTRUCT_PATH} # sstruct.hpp, sstruct.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/external # catch2/catch.hpp
)

# Main-------------------------------------

set(SSTRUCT_FILES
  ${SSTRUCT_PATH}/sstruct.hpp
  ${SSTRUCT_PATH}/sstruct.cpp
  ${SSTRUCT_PATH}/main.cpp
)
add_executable(sstruct ${SSTRUCT_FILES})


# Tests-------------------------------------

set(TEST_FILES
  ${SSTRUCT_TEST_PATH}/test_a.hpp
  ${SSTRUCT_TEST_PATH}/test_b.hpp
)
add_executable(sstruct_test ${TEST_FILES})


# IDE-------------------------------------

# Add source groups for Visual Studio IDE
source_group(TREE "sstruct" FILES ${SSTRUCT_FILES})
source_group(TREE "tests" FILES ${TEST_FILES})