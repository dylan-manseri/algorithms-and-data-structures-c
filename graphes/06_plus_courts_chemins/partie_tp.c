#include <stdlib.h>
#include "../include/prototype_td7.h"
#include "../include/prototype_td12.h"

#define INFINI 1000

/**
 * Algorithme de Ford.
 * Il sert à déterminer le plus cours chemin depuis un sommet vers tous les sommets du graphe.
 * La particularité de Ford est qu'il n'optimise rien et parcours sans cesse jusqu'à avoir optimisé les chemins.
 * Il fonctionne tout le temps, mais est lent.
 * @param sd Le sommet de départ.
 * @param g Le graphe.
 * @param type Le type de representation du graphe.
 * @param D Le tableau des couts, chaque indice t indique le coût pour arriver à t depuis @param sd
 * @param P Le tableau des prédécesseurs, chaque indice t indique le prédécesseur de t de ce chemin.
 */
void ford(int sd, void* g, TypeGraphe type, int* D, int* P) {
    D[sd] = 0;
    P[sd] = sd;
    int n = nb_som_gen(g, type);
    for (int s=0; s<n; s++) {
        if (s!=sd) {
            D[s] = INFINI;
            P[s] = -1;
        }
    }
    int modif, tmp, *succ;
    do {
        modif = 0;
        for (int s=0; s<n; s++) {
            succ = get_succ_by_type(s, type, g);
            for (int t=1; t<succ[0]+1; t++) {
                tmp = D[s] + cout(s, succ[t], g, type);
                if (tmp < D[succ[t]]) {
                    D[succ[t]] = tmp;
                    P[succ[t]] = s;
                    modif = 1;
                }
            }
        }
    } while (modif);
}

/**
 * Algorithme de Dijkstra.
 * Il sert à trouver le plus cours chemin entre un sommet et tous les autres.
 * La particularité de Dijkstra est qu'il parcourt les sommets selon leur coût.
 * En effet, il ne parcourt pas en boucle tous les sommets comme Ford, il choisit.
 * Cependant, il ne traite pas les graphes avec des sommets négatifs.
 * @param s Le sommet de départ
 * @param g Le graphe
 * @param type Le type de représentation du graphe
 * @param D Le tableau des coûts
 * @param P Le tableau des prédécesseurs
 */
void dijkstra(int s, void* g, TypeGraphe type, int* D, int* P) {
    int n = nb_som_gen(g, type);
    Liste M = NULL;
    for (int t=0; t<n; t++) {       // Le mieux est de le faire avec un Tas, mais je n'ai pas le temps là
        if (s!=t) {
            if (exist(s, t, g, type) ){
                D[t] = cout(s, t, g, type);
                P[t] = s;
            }
            else {
                D[t] = INFINI;
                P[t] = -1;
            }
            M = inser_triee_cout(t, M, D);
        }
    }
    D[s] = 0;
    P[s] = s;
    int accessible = 1;
    int m;
    while (accessible && !est_vide(M)) {
        m = donnee(M);
        if (D[m] == INFINI) {
            accessible = 0;
        }
        else {
            M = supp_tete(M);
            int* succ = get_succ_by_type(m, type, g);
            int tmp;
            for (int t=1; t<succ[0]+1; t++) {
                tmp = D[m] + cout(m, succ[t], g, type);
                if (tmp < D[succ[t]]) {
                    D[succ[t]] = tmp;
                    P[succ[t]] = m;
                    M = supp_elt_cout(succ[t], M);
                    M = inser_triee_cout(succ[t], M, D);    // Mise à jour de la liste
                }
            }
        }
    }
}

/**
 * Algorithme de Bellman-Ford.
 * Il sert à trouver le plus court chemin entre un sommet et tous les autres sommets.
 * À chaque itération, il vérifie dans M quel sommet n'a AUCUN prédécesseur présent aussi dans M.
 * Cela lui permet de traiter chaque sommet en prenant compte du dernier coût enregistré pour arriver à ses prédesseceurs.
 * @param sd Le sommet de départ.
 * @param g Le graphe de réprésentation quelconque.
 * @param type Le type du graphe.
 * @param D Le tableau des coûts.
 * @param P Le tableau des prédécesseurs.
 */
void bellman(int sd, void* g, TypeGraphe type, int* D, int* P) {
    // Initialisation
    int n = nb_som_gen(g, type);
    int* deg = malloc(n * sizeof(int)); // Tableau des degrés entrants
    File M = init_l();                       // File des sommets avec un degré entrant de 0
    for (int s=0; s<n; s++) {
        deg[s] = get_nb_pred(s, g, type);
        if (deg[s] == 0) {
            M = inser_queue(s, M);
        }
        D[s] = INFINI;
        P[s] = -1;
    }
    D[sd] = 0;
    P[sd] = sd;

    // Traitement
    int t, tmp;
    while (!est_vide(M)) {
        t = donnee(M);
        M = supp_tete(M);
        int* pred = get_pred_by_type(t, type, g);
        for (int s=1; s<pred[0]+1; s++) {
            tmp = D[pred[s]] + cout(pred[s], t, g, type);
            if (tmp < D[t]) {
                D[t] = tmp;
                P[t] = pred[s];
            }
        }

        // Mise à jour
        int* succ = get_succ_by_type(t, type, g);
        for (int s=1; s<succ[0]+1; s++) {
            deg[succ[s]]--;
            if (deg[succ[s]] == 0) {
                M = inser_queue(succ[s], M);
            }
        }
    }
}

/**
 * Algorithme de Floyd
 * Même principe que la fermeture transitive.
 * On compare le cout du chemin (s→t) avec le cout du chemin ((s→k) + (k→t)).
 * Cela nous fait une escale, mais si c'est bien inferieur alors, on gagne en coût.
 * @param g Le graphe
 * @param type Le type de représentation
 * @param D La matrice des coûts
 * @param P La matrice des prédécesseurs
 */
void floyd(void* g, TypeGraphe type, int** D, int** P) {
    // Initialisation
    int n = nb_som_gen(g, type);
    for (int s=0; s<n; s++) {
        for (int t=0; t<n; t++) {
            D[s][t] = cout(s, t, g, type);
            if (D[s][t] != INFINI) {
                P[s][t] = s;
            }
            else {
                P[s][t] = -1;
            }
        }
    }
    // Traitement
    for (int k=0; k<n; k++) {
        for (int s=0; s<n; s++) {
            for (int t=0; t<n; t++) {
                if (D[s][k] + D[k][t] < D[s][t]){       // Est-ce qu'on a une alternative moins couteuse via k ?
                    D[s][t] = D[s][k] + D[k][t];
                    P[s][t] = P[k][t];
                }
            }
        }
    }
}