cmake_minimum_required(VERSION 3.22)

project(brainfuck)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message("Building with CMake version: ${CMAKE_VERSION}")

set(HEADERS
    ./include/utils.h
    ./include/opcodes.h
    ./include/parser.h
    ./include/interpreter.h
)

set(SOURCES
    ./src/main.cpp
    ./src/parser.cpp
    ./src/interpreter.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ./include/)