# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/ToxLite_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/ToxLite_autogen.dir/ParseCache.txt"
  "ToxLite_autogen"
  )
endif()
