#include "../include/prototype_td3.h"
#include "../include/prototype_td12.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Renvoi le sommet suivant, selon l'ordre lexicographique
 * @param s Le sommet actuel
 * @param n Le nombre de sommets
 * @param visite Le tableau des visites
 * @return Le prochain sommet à visiter
 */
int som_suivant(int s, int n, int* visite) {
    int trouve = 0;
    while (!trouve) {
        if (visite[s] != 1) {
            trouve = 1;
        }
        else {
           s++;
            if (s > n) {
            s=0;
            }
        }
    }
    return s;
}

/**
 * Algorithme récursif de parcours en profondeur d'un graphe.
 * On parcourt le plus profondement possible, s'il n'est plus possible d'avancer, on retourne d'un pas en arrière.
 * Ensuite, on recommence avec un autre sommet non visité
 * @param s Le sommet de départ
 * @param visite Le tableau des visites
 * @param g Le graphe à parcourir
 * @param type Le type du graphe
 * @param n Le nombre de sommets
 * @param nbSomVisite Le nombre de sommets visité
 */
void re_parcours_profondeur(int *s, int* visite, void* g, TypeGraphe type, int n, int* nbSomVisite)  {
    if (*nbSomVisite < n) {
        visite[*s] = 1;
        printf(" %d |", *s);       // Traiter
        *nbSomVisite = *nbSomVisite+1;
        int* succ = get_succ_by_type(*s, type, g);
        for (int i=1; i<succ[0]+1; i++) {
            if (!visite[succ[i]]) {
                *s = succ[i];
                re_parcours_profondeur(s, visite, g, type, n, nbSomVisite);
            }
        }
    }
}

/**
 * Debut de l'algorithme de parcours en profondeur
 * @param sd Sommet de départ
 * @param g Le graphe
 * @param type Le type du graphe
 */
void parcours_profondeur(int sd, void* g, TypeGraphe type) {
    int n = nb_som_gen(g, type);
    int* visite = alloc_tab(n);
    for (int s=0; s<n; s++) {
        visite[s] = 0;
    }
    int s = sd;
    int nbSomVisite = 0;
    int finParcours = 0;
    printf("Sommets rencontrés : |");
    while (!finParcours) {
        re_parcours_profondeur(&s, visite, g, type, n, &nbSomVisite);
        if (nbSomVisite < n) {
            s = som_suivant(s, n, visite);
        }
        else {
            finParcours = 1;
        }
    }
}

/**
 * Algorithme de parcours en largeur itératif d'un graphe.
 * On parcourt les successeurs les un après les autres.
 * Une fois les successeurs parcourut, on fait de même leurs successeurs
 * @param s Le sommet de départ
 * @param visite Le tableau des visites
 * @param g Le graphe
 * @param n Le nombre de sommets
 * @param nbSomVisite Le nombre de sommets visité
 * @param type Le type du graphe
 */
void it_parcours_largeur(int *s, int* visite, void* g, int n, int* nbSomVisite, TypeGraphe type) {
    File f = init_l();
    f = inser_queue(*s, f);       // Enfiler
    int arret = 0;
    int u;
    while (!est_vide(f) && !arret) {
        u = donnee(f);
        f = supp_tete(f);
        if (!visite[u]) {
            visite[u] = 1;
            printf(" %d |", u);   // Traiter
            *nbSomVisite = *nbSomVisite+1;
            if (*nbSomVisite == n) {
                arret = 1;
            }
            else {
                int* succ = get_succ_by_type(u, type, g);     // succ[0] stocke le nombre de successeurs
                for (int i=1; i<succ[0]+1; i++) {
                    if (!visite[succ[i]]) {
                        f = inser_queue(succ[i], f);           // Enfiler
                    }
                }
            }
        }

    }
}

/**
 * Debut de l'algorithme de parcours en largeur.
 * @param sd Le sommet de départ.
 * @param g Le graphe
 * @param type Le type du graphe
 */
void parcours_largeur(int sd, void* g, TypeGraphe type) {
    int n = nb_som_gen(g, type);
    int* visite = alloc_tab(n);
    for (int i=0; i<n; i++) {
        visite[i] = 0;
    }
    int nbSomVisite = 0;
    int s = sd;
    int finParcours = 0;
    printf("Sommets rencontrés : |");
    while (!finParcours) {
        it_parcours_largeur(&s, visite, g, n, &nbSomVisite, type);
        if (nbSomVisite < n) {
            s = som_suivant(s, n, visite);
        }
        else {
            finParcours = 1;
        }
    }
    visite = lib_tab_f(visite);
}