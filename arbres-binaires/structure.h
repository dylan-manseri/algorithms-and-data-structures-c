#ifndef TP_AB_STRUCT
#define TP_AB_STRUCT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Donnée d'un nœud d'arbre d'expression : opérateur (char) OU opérande (double).
typedef union {
    char   operateur;
    double operande;
}DNoeud;

// Établit la nature du nœud (le tag du union).
typedef enum {
    OPERATEUR,
    OPERANDE
}NNoeud;

// Élément complet d'un nœud d'arbre d'expression : tag + valeur.
typedef struct {
    NNoeud nNoeud;
    DNoeud dNoeud;
}TElementA;

// Arbre binaire d'expression (chaînage explicite des fils).
typedef struct noeud {
    TElementA donnee;
    struct noeud *filsGauche;
    struct noeud *filsDroit;
}*ArbreExp;

// Pile chaînée générique (sommet pointe sur la tête).
typedef struct cel {
    void* donnee;
    struct cel *suivant;
}*Pile;

// Pile — primitives
Pile  suivant(Pile p);
Pile  init_p(void);
int   est_vide_p(Pile p);
Pile  alloc_mem_pile(void);
void* sommet_p(Pile p);
Pile  empiler(void* donnee, Pile p);
Pile  depiler(Pile p);

// Arbre d'expression — primitives et constructeurs
char       operateur(DNoeud dnoeud);
double     operande(DNoeud dnoeud);
DNoeud     d_noeud(TElementA elt);
ArbreExp   fils_gauche(ArbreExp a);
ArbreExp   fils_droit(ArbreExp a);
TElementA  donnee_a(ArbreExp a);
int        est_vide_a(ArbreExp a);
int        est_feuille(ArbreExp a);
ArbreExp   create_feuille(TElementA elt);
ArbreExp   create_noeud(TElementA elt, ArbreExp fg, ArbreExp fd);

// Analyse lexicale du flux de caractères
int est_po(char c);
int est_pf(char c);
int est_chiffre(char c);
int est_operateur(char c);
int est_sep(char c);
int est_point(char c);
int code_ascii(char c);

// Construction et évaluation de l'arbre d'expression
double   extraire_nb_reel(int *i, char* exp);
ArbreExp cons_a(char* exp);
double   eval_oper(char oper, double vd, double vg);
double   eval_a_exp(ArbreExp aExp);

#endif