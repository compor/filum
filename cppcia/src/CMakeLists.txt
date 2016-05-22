# cmake lists file

cmake_minimum_required(VERSION 3.2)
project(CCIA)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lc++abi -lboost_thread -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++ -pthread")

#find_package(Boost COMPONENTS thread system REQUIRED)

#include_directories(${Boost_INCLUDE_DIRS})
#link_directories(${Boost_LIBRARYDIR})


#file(GLOB SRC_FILES . *.cpp)

#foreach(SRC_FILE ${SRC_FILES})
  #string(REGEX REPLACE "\.cpp$" ".out" EXE ${SRC_FILE})
  #get_filename_component(EXE ${EXE} NAME)

  #add_executable(${EXE} ${SRC_FILE})
  #target_link_libraries(${EXE} ${Boost_LIBRARIES})
#endforeach()

add_subdirectory(ch02)

