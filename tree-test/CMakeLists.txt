cmake_minimum_required(VERSION 3.5)
project(tree_test)

set(CMAKE_CXX_STANDARD 14)

add_executable(tests test/tree_test.cpp src/tree_gen.cpp)