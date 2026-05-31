cmake_minimum_required(VERSION 3.20)
project(arbres_parfaits_et_tas C)

set(CMAKE_C_STANDARD 23)

add_executable(arbres_parfaits
        exercice_arbres/main.c
        structure.h
        exercice_arbres/exercice_arbres.c
        exercice_arbres/fonction_arbre.c
)

add_executable(tas
        exercice_tas/main.c
        structure.h
        exercice_arbres/exercice_arbres.c
        exercice_arbres/fonction_arbre.c
        exercice_tas/exercice_tas.c
)

# log / round dans <math.h> nécessitent -lm sous Linux
target_link_libraries(arbres_parfaits PRIVATE m)
target_link_libraries(tas PRIVATE m)