cmake_minimum_required(VERSION 3.21)
project(530Program2)

set(CMAKE_CXX_STANDARD 14)

add_executable(530Program2 main.cpp Library.h Instruction.cpp Instruction.h Conversion.h Conversion.cpp Formatting.h Formatting.cpp Table.cpp Table.h Disassembly.cpp Disassembly.h Library.cpp)
