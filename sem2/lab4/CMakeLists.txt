cmake_minimum_required(VERSION 3.0.0)

project(lab4)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions")

add_executable(pathmgep pathmgep.cpp)
add_executable(pathmgep2 pathmgep2.cpp)
add_executable(pathbgep pathbgep.cpp)
add_executable(negcycle negcycle.cpp)
add_executable(path path.cpp)