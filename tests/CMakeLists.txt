cmake_minimum_required(VERSION 3.14)
project(ProjectCT)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

set(BINARY ${CMAKE_PROJECT_NAME}_tst)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib GTest::gtest_main)