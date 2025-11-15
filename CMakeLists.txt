cmake_minimum_required(VERSION 3.22)
project(wsh)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE WSH_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(wsh
  ${WSH_SOURCES}
)

