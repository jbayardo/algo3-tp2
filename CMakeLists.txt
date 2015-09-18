cmake_minimum_required(VERSION 2.8)
project(algo3_tp2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -std=c++11 -Wall -Wpedantic -Wextra -Wshadow -Wpointer-arith -Wcast-qual")

set(SOURCE_FILES src/main.cpp src/Exercise.cpp src/Exercise1.cpp src/Exercise2.cpp src/Exercise3.cpp)
add_executable(algo3_tp2 ${SOURCE_FILES})