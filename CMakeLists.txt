cmake_minimum_required(VERSION 3.17)
project(miniShell C)

set(CMAKE_C_STANDARD 99)

add_executable(miniShell main.c main.h Calc_time.c Calc_time.h helperFunction.c helperFunction.h)