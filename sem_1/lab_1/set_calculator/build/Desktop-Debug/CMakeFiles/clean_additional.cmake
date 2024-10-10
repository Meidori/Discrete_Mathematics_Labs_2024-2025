# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/set_calculator_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/set_calculator_autogen.dir/ParseCache.txt"
  "set_calculator_autogen"
  )
endif()
