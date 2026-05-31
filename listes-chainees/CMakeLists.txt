cmake_minimum_required(VERSION 3.20)
project(listes_chainees C)

set(CMAKE_C_STANDARD 23)

add_executable(PGCD
        exercice1_2_3/main.c
        exercice1_2_3/structure.h
        exercice1_2_3/fonctions_liste.c
        exercice1_2_3/exercice1.c
)

add_executable(exo3
        exercice3/fonctions_liste.c
        exercice3/main_exo3.c
        exercice3/exercice3.c
        exercice3/structure_exo3.h
)
