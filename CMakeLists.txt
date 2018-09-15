cmake_minimum_required(VERSION 3.10)
project(untitled)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER /usr/bin/g++-7)

#add_executable(untitled main.cpp vector.h)

add_executable(untitled vector_tests.cpp vector.h doctest.h)