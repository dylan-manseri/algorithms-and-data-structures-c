#include <stdio.h>
#include <stdlib.h>

#include "../include/prototype_td6.h"
#include "../include/prototype_td12.h"

/**
 * Teste si une matrice d'adjacence représente un graphe vide.
 * @param mat Matrice d'adjacence.
 * @return 1 si aucun sommet, 0 sinon.
 */
int est_vide_ma(MatAdjacence mat) {
    return mat.nbSom == 0;
}

/**
 * Teste si une file de successeurs représente un graphe vide.
 * @param fs File de successeurs.
 * @return 1 si aucun sommet, 0 sinon.
 */
int est_vide_fs(FileSuccesseur fs) {
    return fs.nbSom == 0;
}

/**
 * Teste si une liste d'adjacence représente un graphe vide.
 * @param la Liste d'adjacence.
 * @return 1 si aucun sommet, 0 sinon.
 */
int est_vide_l_adj(ListeAdjacence la) {
    return la.nbSom == 0;
}

/**
 * Vérifie qu'un graphe est vide.
 * Il ne sert à rien pour le TP, j'avais juste mal compris le CM.
 * Mais bon, on ne sait jamais donc je garde.
 * @param g Le graphe
 * @param type Le type
 * @return Un booléen
 */
int est_vide_graphe(void* g, TypeGraphe type) {
    int est_vide;
    if (type == MAT_ADJACENCE) {
        MatAdjacence* mat = (MatAdjacence*) g;
        est_vide = est_vide_ma(*mat);
    }
    else if (type == FILE_SUCCESSEUR) {
        FileSuccesseur* fs = (FileSuccesseur*) g;
        est_vide = est_vide_fs(*fs);
    }
    else if (type == LISTE_ADJACENCE) {
        ListeAdjacence* la = (ListeAdjacence*) g;
        est_vide = est_vide_l_adj(*la);
    }
    else {
        printf("\nErreur de type");
        exit(1);
    }
    return est_vide;
}

/**
 * Parcours partiel de la matrice d'adjacence.
 * Son but est de trouver le nombre de sommets qui atteignent t.
 * @param mat La matrice d'adjacence.
 * @param t Le sommet à atteindre.
 * @return Le degré
 */
int degre_entrant_ma(MatAdjacence mat, int t) {
    int d = 0;
    int n = nb_som_ma(mat);
    for (int s=0; s<n; s++) {
        if (mat.mat[s][t] == 1) {
            d++;
        }
    }
    return d;
}

/**
 * Parcours total du tableau de la file de successeur.
 * Si on trouve arc atteignant t, alors on ajoute un degré.
 * @param fs La file de successeur.
 * @param t Le sommet.
 * @return Le degré.
 */
int degre_entrant_fs(FileSuccesseur fs, int t) {
    int d = 0;
    for (int arc=0; arc<fs.nbArcs; arc++) {
        if (fs.FS[arc] == t) {
            d++;
        }
    }
    return d;
}

/**
 * Parcours total de la liste d'adjacence.
 * Son but est de trouver le nombre de prédécesseurs de t sans stocker le sommet.
 * @param la La liste d'adjacence.
 * @param t Le sommet.
 * @return Le degré.
 */
int degre_entrant_la(ListeAdjacence la, int t) {
    int d = 0;
    int n = nb_som_gen(&la, LISTE_ADJACENCE);
    Liste l;
    for (int s=0; s<n; s++) {
        l = la.tabAdj[s];
        while (!est_vide(l)) {
            if (donnee(l) == t) {
                d++;
            }
            l = suivant(l);
        }
    }
    return d;
}

/**
 * Regroupement via généricité des precedentes fonctions.
 * Utilisé pour calculer le degré entrant d'un graphe quelconque.
 * @param g Le graphe d'un type quelconque.
 * @param type Le type du graphe.
 * @param t Le sommets.
 * @return Le degré.
 */
int degre_entrant(void* g, TypeGraphe type, int t) {
    int degre_entrant;
    if (type == MAT_ADJACENCE) {
        MatAdjacence* mat = (MatAdjacence*) g;
        degre_entrant = degre_entrant_ma(*mat, t);
    }
    else if (type == FILE_SUCCESSEUR) {
        FileSuccesseur* fs = (FileSuccesseur*) g;
        degre_entrant = degre_entrant_fs(*fs, t);
    }
    else if (type == LISTE_ADJACENCE) {
        ListeAdjacence* la = (ListeAdjacence*) g;
        degre_entrant = degre_entrant_la(*la, t);
    }
    else {
        printf("\nErreur de type");
        exit(1);
    }
    return degre_entrant;
}

/**
 * Effectue le tri topologique d'un graphe quelconque.
 * Ce tri renvoi l'ordre des sommets dans les chemins.
 * Si A→B alors A apparaitra avant B dans le tri.
 * @param g Le graphe
 * @param type Le type du graphe
 * @return La file du tri
 */
File tri_topologique_acyclique(void* g, TypeGraphe type) {
    // Initialisation
    File f = init_l();
    int n = nb_som_gen(g, type);
    int* D = alloc_tab(n);
    Liste M = init_l();
    int de;
    for (int s=0; s<n; s++) {           // On remplit notre liste des sommets sans prédécesseurs
        de = degre_entrant(g, type, s);
        if (de == 0) {
            M = inser_tete(s, M);
        }
        D[s] = de;                      // On remplit notre tableau des degrés
    }
    // Traitement
    while (!est_vide(M)) {
        int t = donnee(M);              // On choisit un sommet sans pred quelconque
        M = supp_tete(M);
        D[t] = D[t] - 1;
        f = inser_queue(t, f);
        int* succ = get_succ_by_type(t, type, g);      // On met à jour le degré de ces successeurs.
        for (int i=1; i<succ[0]+1; i++) {
            D[succ[i]] = D[succ[i]] - 1;
            if (D[succ[i]] == 0) {                  // On met à jour M, si besoin.
                M = inser_tete(succ[i], M);
            }
        }
    }
    D = lib_tab_f(D);
    return f;
}

