cmake_minimum_required(VERSION 3.22)
project(wsh)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 23)

include(FindModules)

file(GLOB_RECURSE WSH_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(wsh
  ${WSH_SOURCES}
)

target_include_directories(wsh PRIVATE ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(wsh PRIVATE frozen::frozen)
