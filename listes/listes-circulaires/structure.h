#ifndef STRUCTURE_CIRCULAIRE_H
#define STRUCTURE_CIRCULAIRE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct cel{
    int elt;
    struct cel *suivant;
}*ListeC;

typedef struct {
    int taille;
    ListeC tete;
    ListeC queue;
}ListeCTQ;

// Primitives ListeC
ListeC suivant(ListeC l);
int    donnee(ListeC l);

// Primitives ListeCTQ
ListeC tete(ListeCTQ l);
ListeC queue(ListeCTQ l);
int    taille(ListeCTQ l);

// Fonctions ListeC
ListeC init_l(void);
ListeC alloc_mem(int elt);
ListeC inser_vide_lc(int elt);
ListeC inser_tete(int elt, ListeC l);
ListeC inser_queue(int elt, ListeC l);
void   print_liste(ListeC l);

// Fonctions ListeCTQ
ListeCTQ init_lctq(void);
void     inser_vide_lctq(int elt, ListeCTQ *l);
void     inser_tete_lctq(int elt, ListeCTQ *l);
void     inser_queue_lctq(int elt, ListeCTQ *l);
void     print_liste_ctq(ListeCTQ l);

// Exercice 1 — comptage d'occurrences
int nb_occ(int elt, ListeC der);
int nb_occ_lctq(int elt, ListeCTQ l);

#endif