#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int fact;
    int nbOcc;
}FactPremier;

typedef struct cellule {
    FactPremier donnee;
    struct cellule *suivant;
}*Liste;

typedef struct {
    int nbr;
    Liste ldfp;
}TabLDFP;

// Primitives
int         fact(FactPremier f);
int         nb_occ(FactPremier f);
FactPremier donnee(Liste l);
Liste       suivant(Liste l);
int         nombre(TabLDFP cel);
Liste       liste(TabLDFP cel);

// Construction
Liste       create_liste(void);
FactPremier create_fact_premier(int fact, int nbOcc);
TabLDFP     create_tab_ldfp(int nbr, Liste l);

// Manipulation de liste
int   est_vide(Liste l);
Liste adr_dernier(Liste l);
Liste inser_tete(FactPremier fp, Liste l);
Liste inser_queue(FactPremier fp, Liste l);

// Affichage
void print_fact_premier(FactPremier fp);
void print_liste(Liste l);
void print_tab_ldfp(TabLDFP* tab, int taille);

// Exercice 1 — décomposition en facteurs premiers et PGCD
int    est_premier(int nbr);
int    nbr_division(int *nbr, int p);
Liste  decomposition(int nbr, Liste l);

TabLDFP* convert_tab_to_liste(int *tab, int taille);

int   minimum(int a, int b);
int   puissance(int nbr, int exp);
Liste intersection(Liste l1, Liste l2);
int   pgcd(int* tab, int n);

#endif