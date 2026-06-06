cmake_minimum_required(VERSION 3.20)
project(fonctions_en_parametre C)

set(CMAKE_C_STANDARD 23)

add_executable(fonctions_en_parametre
        main.c
        structure.h
)

target_link_libraries(fonctions_en_parametre PRIVATE m)