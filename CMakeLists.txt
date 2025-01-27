﻿# CMakeList.txt : CMake project for database-cpp, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("database-cpp")

# Add source to this project's executable.
add_executable (database-cpp "src/database.cpp" "include/database.h" "include/tokenizer.h" "src/main.cpp" "src/db_parser.cpp" "src/tokenizer.cpp" "include/db_parser.h" "include/executor.h" "src/executor.cpp" "src/bplustree.cpp" "include/bplustree.h" "include/timer.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET database-cpp PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
