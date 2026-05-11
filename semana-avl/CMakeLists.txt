cmake_minimum_required(VERSION 3.10)
project(semana_avl)

set(CMAKE_CXX_STANDARD 17)

add_executable(semana_avl
    src/main.cpp
    src/AVL.cpp
)

target_include_directories(semana_avl PRIVATE src)
