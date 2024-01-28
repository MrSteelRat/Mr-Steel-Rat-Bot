file(GLOB SOURCE *.cpp)

foreach(target IN LISTS SOURCE)
	message(STATUS ${target}	)
  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR} "" target ${target})
  string(REPLACE "/" "" target ${target})
  string(REPLACE ".cpp" "" target ${target})
  add_executable(${target} ${target}.cpp)

  #target_link_libraries(${target} PRIVATE learning_compile_options learning_dependencies)
endforeach()