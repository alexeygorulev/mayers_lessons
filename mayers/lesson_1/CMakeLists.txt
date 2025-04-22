cmake_minimum_required(VERSION 3.30)
project(mayers)
set(CMAKE_CXX_STANDARD 20)

add_executable(mayers
        main.cpp
        lesson1.h
)

target_include_directories(mayers PRIVATE
        "C:/local/boost_1_88_0"
)
