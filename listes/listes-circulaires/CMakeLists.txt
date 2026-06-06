cmake_minimum_required(VERSION 3.20)
project(listes_circulaires C)

set(CMAKE_C_STANDARD 23)

add_executable(listes_circulaires
        structure.h
        fonctions_liste_c.c
        fonctions_liste_ctq.c
        exercice1.c
        main.c
)
