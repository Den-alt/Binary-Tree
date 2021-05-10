cmake_minimum_required(VERSION 3.19)
project(Binary_Tree C)

set(CMAKE_C_STANDARD 99)

set(SOURCES Sources/file.c Sources/tree.c)

set(HEADERS Headers/inform.h)

add_executable(Binary_Tree main.c ${SOURCES} ${HEADERS})