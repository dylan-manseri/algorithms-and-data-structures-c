#ifndef STRUCTURE_FONCTIONS_EN_PARAMETRE_H
#define STRUCTURE_FONCTIONS_EN_PARAMETRE_H

#include <stdio.h>
#include <stdlib.h>

/** Type d'une fonction de comparaison passée en paramètre (prédicat sur int). */
typedef int (*Fcomp)(int, int);

typedef struct {
    int pr;  /* partie réelle */
    int pi;  /* partie imaginaire */
} Complexe;

#endif