cmake_minimum_required(VERSION 3.22)
project(yw_ch3_task1_transfer)

set(CMAKE_CXX_STANDARD 20)

add_executable(yw_ch3_task1_transfer main.cpp
        deadlock_demo.cpp
        deadlock_demo.h
        transfer.cpp
        transfer.h)
