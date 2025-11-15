cmake_minimum_required(VERSION 3.22)
project(wsh)

set(CMAKE_CXX_STANDARD 23)

add_executable(wsh
  ${PROJECT_SOURCE_DIR}/src/main.cpp
)
