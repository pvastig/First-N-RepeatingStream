cmake_minimum_required(VERSION 3.5)

project(FirstNRepeatingStream LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(FirstNRepeatingStream main.cpp utils.cpp utils.h)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(FirstNRepeatingStream PUBLIC
        -O3
        -g3 -ggdb3
        )
endif()
