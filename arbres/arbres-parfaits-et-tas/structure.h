#ifndef TP_ARBRES_STRUCTURE_H
#define TP_ARBRES_STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Arbre parfait représenté par un tableau (filiation calculée par arithmétique).
typedef struct {
    int  taille;
    int  tailleMax;
    int *tab;
}ArbreParfait;

// Un tas est un arbre parfait respectant la propriété de tas (max-heap).
typedef ArbreParfait Tas;

// -------- Arbre parfait : primitives et navigation --------
int taille(ArbreParfait a);
int taille_max(ArbreParfait a);

ArbreParfait alloc_mem_ap(ArbreParfait a, int tMax);
ArbreParfait init_ap(ArbreParfait a);
int          est_vide_ap(ArbreParfait a);
int          est_plein_ap(ArbreParfait a);
int          est_exist_noeud_ap(int nd, ArbreParfait a);
int          donnee_ap(int nd, ArbreParfait a);
int          pere_noeud_ap(int nd, ArbreParfait a);
int          fils_gauche_ap(int nd, ArbreParfait a);
int          fils_droit_ap(int nd, ArbreParfait a);
int          est_feuille(int nd, ArbreParfait a);

// -------- Arbre parfait : parcours --------
void parcours_prefixe_ap(int racine, ArbreParfait a);
void parcours_infixe_ap(int racine, ArbreParfait a);
void parcours_postfixe_ap(int racine, ArbreParfait a);
void parcours_largeur_ap(int racine, ArbreParfait a);
void parcours_largeur_par_niveau(ArbreParfait a, int n);
void parcours_arbre_parfait_niveau_plein(ArbreParfait a);

// -------- Arbre parfait : construction --------
ArbreParfait inser_elt_ap(int elt, ArbreParfait a);
ArbreParfait const_ap(void);

// -------- Tas : primitives et opérations --------
int sommet_tas(Tas t);
Tas inser_tas(int elt, Tas t);
Tas rec_inser_tas(int elt, int n, Tas t);
Tas supp_tas(Tas t);
Tas rec_supp_tas(Tas t);
Tas rec_supp_tas_bis(int elt, int r, int fg, Tas t);

// -------- Tas : tests et utilitaires --------
int max(int a, int b);
int est_tas_ver1(int n, ArbreParfait a);
int est_tas_ver2(int n, ArbreParfait a);
int rec_est_tas_ver1(int n, ArbreParfait a);
int rec_est_tas_ver2(int n, int r, ArbreParfait a);

// -------- Tas : application au tri --------
Tas  convert_tab_to_tas(int n, int *tab);
Tas  rec_convert_tab_to_tas(int n, ArbreParfait tas, int *tab);
void tri_par_tas(int n, int *tab);

#endif