

cmake_minimum_required(VERSION 3.20)
project(sstruct LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(SSTRUCT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/sstruct")

include_directories(
  ${SSTRUCT_PATH} # sstruct.hpp, tests.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/external # catch2/catch.hpp
)

set(SSTRUCT_FILES
  ${SSTRUCT_PATH}/sstruct.hpp
  ${SSTRUCT_PATH}/tests.cpp
)

add_executable(test ${SSTRUCT_FILES})


# IDE-------------------------------------
# Add source groups for Visual Studio IDE
source_group(TREE ${SSTRUCT_PATH} FILES ${SSTRUCT_FILES})
