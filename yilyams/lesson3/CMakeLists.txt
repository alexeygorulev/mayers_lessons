cmake_minimum_required(VERSION 3.22)
project(lesson3)

set(CMAKE_CXX_STANDARD 20)

add_executable(lesson3 main.cpp
        hierarchial_mutex.h
        test.h)
