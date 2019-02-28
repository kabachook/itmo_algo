cmake_minimum_required(VERSION 3.12)
project(lab5)

set(CMAKE_CXX_STANDARD 11)

add_executable(set set.cpp)
add_executable(map map.cpp)
add_executable(linkedmap linkedmap.cpp)
add_executable(multimap_fail multimap_fail.cpp)
add_executable(multimap multimap.cpp)
add_executable(mmap mmap.cpp)