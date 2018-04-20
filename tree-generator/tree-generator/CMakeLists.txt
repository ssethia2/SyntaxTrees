cmake_minimum_required(VERSION 3.5)
project(tree-generator)

set(CMAKE_CXX_STANDARD 14)

add_executable(tree-gen-ssethia2 test/pos_tag_tests.cpp src/pos_tag.h src/pos_tag.cpp)