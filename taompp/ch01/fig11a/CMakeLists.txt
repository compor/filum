
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project("fig1.1a")

find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pthread")

add_executable(fig11a fig11a.cpp)

target_link_libraries(fig11a ${CMAKE_THREADS_LIB_INIT})

