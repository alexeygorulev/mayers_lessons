cmake_minimum_required(VERSION 3.22)
project(yw_ch2_scoped_thread LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(yw_ch2_scoped_thread main.cpp)

if (NOT CMAKE_CROSSCOMPILING)
    target_compile_options(yw_ch2_scoped_thread PRIVATE
            -Wall -Wextra -Werror -fsanitize=thread)
    target_link_options(yw_ch2_scoped_thread PRIVATE
            -fsanitize=thread)
endif()