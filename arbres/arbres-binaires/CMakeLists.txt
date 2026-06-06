cmake_minimum_required(VERSION 3.20)
project(arbres_binaires C)

set(CMAKE_C_STANDARD 23)

add_executable(arbres_binaires
        main.c
        structure.h
        fonctions_pile.c
        exercice.c
        fonctions_arbre.c)
