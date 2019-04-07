cmake_minimum_required(VERSION 3.0.0)

project(lab4)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(spantree spantree.cpp)
add_executable(spantree_fast spantree_fast.cpp)
add_executable(spantree_revenge spantree_revenge.cpp)
add_executable(chinese chinese.cpp)
