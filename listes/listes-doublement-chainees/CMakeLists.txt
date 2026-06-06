cmake_minimum_required(VERSION 3.20)
project(listes_doublement_chainees C)

set(CMAKE_C_STANDARD 23)

add_executable(listes_doublement_chainees_exo1
        structure.h
        exercice1/fonctions_liste_dc.c
        exercice1/exercice1.c
        exercice1/main.c
)

add_executable(listes_doublement_chainees_exo2
        structure.h
        exercice2/fonctions_liste_dctq.c
        exercice2/exercice2.c
        exercice2/main.c
)