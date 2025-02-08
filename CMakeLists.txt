cmake_minimum_required(VERSION 3.5)

project(moving_average_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJ_SOURCES main.cpp ${PROJECT_SOURCE_DIR}/test/TestFunctions.cpp)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/test)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(moving_average_test ${PROJ_SOURCES})
