cmake_minimum_required(VERSION 3.28)
project(yw_ch2_scoped_thread LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(yw_ch2_scoped_thread main.cpp)

if (WIN32)
    target_compile_options(yw_ch2_scoped_thread PRIVATE -Wall -Wextra -Werror)
else()
    # Linux / WSL / macOS
    target_compile_options(yw_ch2_scoped_thread PRIVATE -Wall -Wextra -Werror
            -fsanitize=thread,address)
    target_link_options(yw_ch2_scoped_thread    PRIVATE -fsanitize=thread,address)
endif()
