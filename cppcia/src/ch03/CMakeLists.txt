# cmake lists file


file(GLOB SRC_FILES . *.cpp)

foreach(SRC_FILE ${SRC_FILES})
  string(REGEX REPLACE "\.cpp$" ".out" EXE ${SRC_FILE})
  get_filename_component(EXE ${EXE} NAME)

  add_executable(${EXE} ${SRC_FILE})
  target_link_libraries(${EXE})
endforeach()


