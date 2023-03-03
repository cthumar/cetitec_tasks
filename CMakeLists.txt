cmake_minimum_required(VERSION 3.10)
project(ProjectCT)

set(CMAKE_CXX_STANDARD 14)
enable_testing()
include(CTest)
include_directories(source)

add_subdirectory(source)
add_subdirectory(tests)
add_subdirectory(lib/googletest)
