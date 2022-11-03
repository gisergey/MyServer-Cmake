# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\MyServerCmake_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MyServerCmake_autogen.dir\\ParseCache.txt"
  "MyServerCmake_autogen"
  )
endif()
