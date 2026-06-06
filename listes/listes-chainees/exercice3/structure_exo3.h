#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct cellule {
    int donnee;
    struct cellule *suivant;
}*Liste;

// Primitives
int   donnee(Liste l);
Liste suivant(Liste l);
int   est_vide(Liste l);

// Construction et insertion
Liste init_l(void);
Liste alloc_mem(void);
Liste search_elt(Liste l, int elt);
Liste inser_tete(Liste l, int elt);
Liste inser_triee(Liste l, int elt);

#endif