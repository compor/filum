# cmake lists file

cmake_minimum_required(VERSION 3.2)

project(taompp)

find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++ -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")


function(exe_per_source DIR)
  file(GLOB SRC_FILES ${DIR} *.cpp)

  foreach(SRC_FILE ${SRC_FILES})
    string(REGEX REPLACE "\.cpp$" ".out" EXE ${SRC_FILE})
    get_filename_component(EXE ${EXE} NAME)

    add_executable(${EXE} ${SRC_FILE})
    target_link_libraries(${EXE} ${CMAKE_THREAD_LIBS_INIT})
  endforeach()
endfunction(exe_per_source)

add_subdirectory(ch01)


