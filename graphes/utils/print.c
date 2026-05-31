#include <stdio.h>

#include "../include/prototype_td12.h"

// Fonctions d'affichage utilisées pour le débogage et la mise en forme.

/**
 * Affiche un tableau d'entiers entre barres verticales.
 * @param n Taille du tableau.
 * @param tab Tableau à afficher.
 */
void print_tab(int n, int* tab){
    printf("\n|");
    for(int l=0; l<n; l++){
        printf(" %d |", tab[l]);
    }
    printf("\n");
}

/**
 * Affiche une liste chaînée d'entiers entre barres verticales.
 * @param l Liste à afficher.
 */
void print_liste(Liste l) {
    printf("| ");
    while (!est_vide(l)) {
        printf("%d | ", donnee(l));
        l = suivant(l);
    }
}

/**
 * Affiche une liste d'adjacence (une ligne par sommet).
 * @param la Liste d'adjacence à afficher.
 */
void print_la(ListeAdjacence la) {
    for (int i=0; i<la.nbSom; i++) {
        printf("%d : ", i);
        print_liste(la.tabAdj[i]);
        printf("\n");
    }
}

/**
 * Affiche une file de successeurs : le vecteur FS puis le vecteur APS.
 * @param fs File de successeurs à afficher.
 */
void print_fs(FileSuccesseur fs) {
    printf("FS : | ");
    for (int i=0; i<fs.nbArcs; i++) {
        printf("%d | ", fs.FS[i]);
    }
    printf("\nAPS : | ");
    for (int j=0; j<fs.nbSom; j++) {
        printf("%d | ", fs.APS[j]);
    }
    printf("\n");
}

/**
 * Affiche une liste de successeurs (indices 1-based dans la sortie).
 * @param ls Liste de successeurs à afficher.
 */
void print_ls(ListeSucc ls) {
    printf("| ");
    while (!est_vide_ls(ls)) {
        printf("%d | ", donnee_ls(ls)+1);
        ls = suivant_ls(ls);
    }
    printf("\n");
}

/**
 * Affiche une liste de prédécesseurs (indices 1-based dans la sortie).
 * @param lp Liste de prédécesseurs à afficher.
 */
void print_lp(ListePred lp) {
    printf("| ");
    while (!est_vide_lp(lp)) {
        printf("%d | ", donnee_lp(lp)+1);
        lp = suivant_lp(lp);
    }
    printf("\n");
}

/**
 * Affiche une liste d'adjacence avec succ. et préd. distincts par sommet.
 * @param lsp Liste d'adjacence Succ/Pred à afficher.
 */
void print_lsp(ListeAdjSuccPred lsp) {
    for (int i=0; i<lsp.nbSom; i++) {
        printf("---------------\n");
        printf("%d\nSuccesseur : ", i+1);
        print_ls(lsp.tabAdjSP[i].lSucc);
        printf("Predecesseur : ");
        print_lp(lsp.tabAdjSP[i].lPred);
    }
}

/**
 * Affiche une matrice générique (adjacence ou incidence) sous forme tabulaire.
 * Dispatch sur le type pour adopter le bon comportement.
 * @param mat Pointeur sur la matrice (adjacence ou incidence).
 * @param type Discriminant de la représentation.
 */
void print_mat(void* mat, TypeGraphe type) {
    int lig, col;
    if (type == MAT_ADJACENCE) {
        MatAdjacence *matA = (MatAdjacence*) mat;
        lig = matA->nbSom;
        col = lig;
        for (int i=0; i<lig; i++) {
            for (int j=0; j<col; j++) {
                printf("%d  ", matA->mat[i][j]);
            }
            printf("\n");
        }
    }
    else if (type == MAT_INCIDENCE) {
        MatIncidence* matI = (MatIncidence*) mat;
        lig = matI->nbSom;
        col = matI->nbArc;
        for (int i=0; i<lig; i++) {
            for (int j=0; j<col; j++) {
                printf("%d ", matI->mat[i][j]);
            }
            printf("\n");
        }
    }
    else{
        printf("\n Erreur de type\n");
        return;
    }
}
