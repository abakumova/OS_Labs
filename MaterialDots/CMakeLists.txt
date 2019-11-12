cmake_minimum_required(VERSION 3.14)
project(MaterialDots C)

set(SOURCE_EXE main.c dot.h dot.c)

add_executable(main ${SOURCE_EXE})