cmake_minimum_required(VERSION 3.22)

project(brainfuck)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")

message("Building with CMake version: ${CMAKE_VERSION}")

set(HEADERS
    ./include/utils.h
    ./include/opcodes.h
    ./include/parser.h
    ./include/interpreter.h
    ./include/compiler.h
)

set(SOURCES
    ./src/main.cpp
    ./src/parser.cpp
    ./src/interpreter.cpp
    ./src/compiler.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ./include/)

find_package(LLVM REQUIRED CONFIG)
target_link_libraries(${PROJECT_NAME} PRIVATE LLVM)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})