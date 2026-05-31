#include <stdio.h>
#include <stdlib.h>

#include "../include/prototype_td12.h"
#include "../include/prototype_td3.h"
#include "../include/prototype_td4.h"
#include "../include/prototype_td5.h"

/**
 * Algorithme de parcours en profondeurs (cf. TD4) adapté à la recherche de composantes connexes.
 * Chaque appel INITIAL (cad ceux non récursif) traite UNE composante connexe
 * @param s Le sommet en cours
 * @param visite Le tableau des visites indicé par le sommet
 * @param g Le graphe
 * @param type Le type du graphe
 * @param n Le nombre de sommets
 * @param nbSomVisite Le nombre de sommets visités
 * @param CC Le tableau des composantes connexes indicé par le sommet
 * @param nbCC Le numéro de la composante connexe actuel (ou le nombre de CC, on peut le voir des deux façons).
 */
void re_parcours_profondeur_cc(int *s, int* visite, void* g, TypeGraphe type, int n, int* nbSomVisite, int* CC, int* nbCC)  {
    if (*nbSomVisite < n) {
        visite[*s] = 1;
        CC[*s] = *nbCC;     // On indique le numéro de la composante connexe du sommet actuel
        *nbSomVisite = *nbSomVisite+1;
        int* succ = get_succ_by_type(*s, type, g);
        for (int i=1; i<succ[0]+1; i++) {
            if (!visite[succ[i]]) {
                *s = succ[i];
                re_parcours_profondeur_cc(s, visite, g, type, n, nbSomVisite, CC, nbCC);
            }
        }
    }
}

/**
 * Un graphe est connexe si pour tout (u,v) il existe un chemin entre u et v.
 * On parcourt en profondeur depuis un sommet de départ.
 * L'ensemble des sommets rencontrés représente une composante connexe.
 * On réitère pour chaque sommet non visité.
 * @param g
 * @param type
 * @return
 */
int* get_cc(void* g, TypeGraphe type) {
    int n = nb_som_gen(g, type);
    int* visite = alloc_tab(n);      // Tableau de visite du parcours
    int* CC = alloc_tab(n);          // Tableau indicé par le sommet indiquant le numéro de la CC du sommet
    for (int i=0; i<n; i++) {
        visite[i] = 0;
    }
    int nbSomVisite = 0;
    int nbCC = 1;
    int finParcours = 0;
    int s = 0;
    while (!finParcours) {
        re_parcours_profondeur_cc(&s, visite, g, type, n, &nbSomVisite, CC, &nbCC);
        if (nbSomVisite < n) {      // Si on a pas tous visité, il reste des CCs.
            s = som_suivant(s, n, visite);
            nbCC++;                 // On augmente le nombre pour préparer le prochain parcours.
        }
        else {
            finParcours = 1;
        }
    }
    visite = lib_tab_f(visite);
    free(visite);
    return CC;
}

/**
 * Parcours en profondeurs du graphe inital.
 * On dit qu'il est suffixe, car on traite le sommet une fois avoir traité ses déscendants.
 * @param s Le sommet de départ
 * @param p La pile, on empile à chaque impasse
 * @param nbSomVisite Le nombre de sommets visité
 * @param g Le graphe
 * @param visite Le tableau des visite
 * @param n Le nombre de sommets dans le graphe
 * @param type Le type du graphe
 */
void re_parcours_profondeur_suffixe(int s, Pile* p, int* nbSomVisite, void* g, int* visite, int n, TypeGraphe type) {
    if (*nbSomVisite < n) {
        visite[s] = 1;
        *nbSomVisite = *nbSomVisite +1;
        int* succ = get_succ_by_type(s, type, g);
        for (int i=0; i<succ[0]; i++) {
            if (!visite[succ[i]]) {
                re_parcours_profondeur_suffixe(succ[i], p, nbSomVisite, g, visite, n, type);
            }
        }
        *p = inser_tete(s, *p);
    }
}

/**
 * Parcours en profondeurs de la transposer du graphe.
 * @param s Le sommet de départ
 * @param nbSomVisite Le nombre de sommets visités
 * @param g Le graphe
 * @param visite Le tableau des vistes
 * @param n Le nombre de sommets du graphe
 * @param nbCFC Le nombre de composantes fortement connexes
 * @param CFC Le teableau indicé par les sommets indiquant les composantes connexes du graphe
 * @param type le type du graphe
 */
void re_parcours_profondeur_cfc_t(int s, int* nbSomVisite, void* g, int* visite, int n, int nbCFC, int* CFC, TypeGraphe type) {
    if (*nbSomVisite < n) {
        visite[s] = 1;
        *nbSomVisite = *nbSomVisite +1;
        CFC[s] = nbCFC;
        int* succ = get_pred_by_type(s, type, g);
        for (int i=0; i<succ[0]; i++) {
            if (!visite[succ[i]]) {
                re_parcours_profondeur_cfc_t(succ[i], nbSomVisite, g, visite, n, nbCFC, CFC, type);
            }
        }
    }
}

/**
 * On veut trouver les composantes fortement connexes d'un graphe.
 * Etape 1 : On réalise un parcours en profondeur du graphe en empilant à chaque impasse.
 * Etape 2 : On réalise un parcours en profondeurs de la transposer du graphe et suivant l'ordre de la pile.
 * Etape 2bis : À chaque impasse, on incrémente le nombre de la composante fortement connexe.
 * @param g Le graphe
 * @param type Le type du graphe
 * @return
 */
int* get_cfc(void* g, TypeGraphe type) {
    int n = nb_som_gen(&g, type);
    int* visite = alloc_tab(n);
    int* CFC = alloc_tab(n);
    for (int i=0; i<n; i++) {
        CFC[i] = 0;
    }
    int nbSomVisite = 0;
    int nbCFC = 1;
    int finParcours = 0;
    Pile p = init_l();
    int s = 0;
    while (!finParcours) {      // Premier parcours en créant la file
        re_parcours_profondeur_suffixe(s, &p, &nbSomVisite, g, visite, n, type);
        if (nbSomVisite < n) {
            s = som_suivant(s, n, visite);
        }
        else {
            finParcours = 1;
        }
    }
    finParcours = 0;
    nbSomVisite = 0;
    for (int i=0; i<n; i++) {
        visite[i] = 0;
    }
    s = donnee(p);
    p = supp_tete(p);
    while (!finParcours) {
        re_parcours_profondeur_cfc_t(s, &nbSomVisite, g, visite, n, nbCFC, CFC, type);
        if (nbSomVisite < n) {
            s = donnee(p);
            p = supp_tete(p);
            nbCFC++;
        }
        else {
            finParcours = 1;
        }
    }
    return CFC;
}

/**
 * Calcul de la fermeture transitive (j'ai juste appliqué la formule)
 * Dans le CM, on a M(1), M(2), etc.
 * Ici, on modifie directement la nouvelle valeur de m[s][t] en prenant l'actuel donc c'est comme fait M(1) avec M(0).
 * m[s][t] == m[t][s] == 1 → s et t appartiennent à un même composante connexe.
 * m[s][s] == 1 → Il existe un cycle passant par s.
 * @param g
 * @param type
 * @param mat
 */
void fermeture_transitive(void* g, TypeGraphe type, int** mat) {
    int n = nb_som_gen(g, type);
    full_zero(mat, n);
    for (int s=0; s<n; s++) {
        int* succ = get_succ_by_type(s, type, g);
        for (int t=0; t<succ[0]; t++) {
            mat[s][succ[t]] = 1;
        }
    }
    for (int k=0; k<n; k++) {
        for (int s=0; s<n; s++) {
            for (int t=0; t<n; t++) {
                mat[s][t] = mat[s][t] || (mat[s][k] && mat[k][t]);
            }
        }
    }
}