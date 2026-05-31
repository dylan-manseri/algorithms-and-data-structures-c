/**
 * Fichier regroupant toutes les allocations et libérations des structures
 * de représentation de graphes (matrices, listes, files…).
 * Convention de suffixe :
 *   - _f : version « fonction » qui renvoie la structure allouée.
 *   - _p : version « pointeur » qui modifie la structure passée par adresse.
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../include/prototype_td12.h"

/**
 * Alloue un tableau d'entiers de taille nMax (sortie sur erreur).
 * @param nMax Taille du tableau.
 * @return Le pointeur sur le tableau alloué.
 */
int* alloc_tab(int nMax) {
    int* tab = malloc(nMax * sizeof(int));
    if (tab == NULL) {
        printf("Erreur d'allocation");
        exit(1);
    }
    return tab;
}

/**
 * Alloue un tableau d'entiers passé par pointeur de pointeur (sortie sur erreur).
 * @param nMax Taille du tableau.
 * @param tab Pointeur sur le pointeur à allouer.
 */
void alloc_tab_p(int nMax, int **tab) {
    *tab = (int*) malloc(nMax * sizeof(int));
    if (*tab == NULL) {
        printf("Erreur d'allocation");
        exit(1);
    }
}

/**
 * Remplit une matrice carrée n×n de zéros.
 * @param mat Matrice à zéroter.
 * @param n Dimension de la matrice.
 */
void full_zero(int** mat, int n) {
    for (int s=0; s<n; s++) {
        for (int t=0; t<n; t++) {
            mat[s][t] = 0;
        }
    }
}

/**
 * Alloue une matrice d'entiers nbLig × nbCol (version fonction).
 * @param nbLig Nombre de lignes.
 * @param nbCol Nombre de colonnes.
 * @return Le pointeur sur la matrice allouée.
 */
int** alloc_mem_mat_f(int nbLig, int nbCol) {
    int **mat = malloc(nbLig * sizeof(int*));
    if (mat == NULL) {
        printf("Erreur d'allocation");
        exit(1);
    }
    for (int i=0; i<nbLig; i++) {
        mat[i] = alloc_tab(nbCol);
        if (mat[i] == NULL) {
            printf("Erreur d'allocation");
            exit(1);
        }
    }
    return mat;
}

/**
 * Alloue une matrice d'entiers (version pointeur) :
 *   - ***mat est de type int  : premier élément de la première ligne
 *   - **mat  est de type int* : pointeur de la première ligne
 *   - *mat   est de type int**: contenu de la matrice
 *   - mat    est de type int***: pointeur vers la matrice passée en paramètre
 * @param nbLig Nombre de lignes.
 * @param nbCol Nombre de colonnes.
 * @param mat Pointeur sur la matrice à allouer.
 */
void alloc_mem_mat_p(int nbLig, int nbCol, int ***mat) {
    *mat = malloc(nbLig * sizeof(int*));
    if (*mat == NULL) {
        printf("Erreur d'allocation");
        exit(1);
    }
    for (int i=0; i<nbLig; i++) {
        *mat[i] = alloc_tab(nbCol);
        if (mat[i] == NULL) {
            printf("Erreur d'allocation");
            exit(0);
        }
    }
}

/**
 * Alloue et initialise une matrice d'adjacence carrée n×n (version fonction).
 * @param n Nombre de sommets.
 * @return La matrice d'adjacence allouée.
 */
MatAdjacence alloc_sma_f(int n) {
    MatAdjacence mat;
    mat.nbSom = n;
    mat.mat = alloc_mem_mat_f(n, n);
    return mat;
}

/**
 * Alloue et initialise (à zéro) une matrice d'incidence nbSom × nbArcs.
 * @param nbSom Nombre de sommets.
 * @param nbArcs Nombre d'arcs.
 * @return La matrice d'incidence allouée.
 */
MatIncidence alloc_smi_f(int nbSom, int nbArcs) {
    MatIncidence mat;
    mat.nbSom = nbSom;
    mat.nbArc = nbArcs;
    mat.mat = alloc_mem_mat_f(nbSom, nbArcs);
    for (int i=0; i<nbSom; i++) {
        for (int j=0; j<nbArcs; j++) {
            mat.mat[i][j] = 0;
        }
    }
    return mat;
}

/**
 * Alloue une matrice d'adjacence n×n via pointeur (version pointeur).
 * @param n Nombre de sommets.
 * @param mat Pointeur sur la matrice à allouer.
 */
void alloc_sma_p(int n, MatAdjacence *mat) {
    mat->nbSom = n;
    mat->mat = alloc_mem_mat_f(n, n);
}

/**
 * Alloue une liste d'adjacence pour nbSom sommets.
 * Chaque entrée du tableau est initialisée à liste vide.
 * @param nbSom Nombre de sommets.
 * @param la Pointeur sur la liste d'adjacence à allouer.
 */
void alloc_la(int nbSom, ListeAdjacence* la){
    la->nbSom = nbSom;
    la->tabAdj = malloc(la->nbSom * sizeof(struct cel));
    for(int i=0; i<nbSom; i++){
        la->tabAdj[i] = init_l();
    }
}

/**
 * Alloue les tableaux FS et APS d'une file de successeurs.
 * @param n Nombre de sommets.
 * @param nbArcs Nombre d'arcs.
 * @param fs Pointeur sur la structure à allouer.
 */
void alloc_fs(int n, int nbArcs, FileSuccesseur* fs) {
    fs->nbArcs = nbArcs;
    fs->nbSom = n;
    fs->APS = malloc(n+1 * sizeof(int));
    fs->FS = malloc(nbArcs+1 * sizeof(int));
}

/**
 * Alloue un tableau de cellules Succ/Pred (un par sommet) et initialise.
 * @param n Nombre de sommets.
 * @param lsp Pointeur sur la structure à allouer.
 */
void alloc_lsp(int n, ListeAdjSuccPred* lsp) {
    lsp->nbSom = n;
    lsp->tabAdjSP = malloc(n * sizeof(ListeSuccPred));
    for (int i=0; i<n; i++) {
        lsp->tabAdjSP[i].lPred = init_lp();
        lsp->tabAdjSP[i].lSucc = init_ls();
    }
}

/**
 * Libère un tableau d'entiers et renvoie un pointeur NULL.
 * @param tab Tableau à libérer.
 * @return NULL (pour assignation sûre côté appelant).
 */
void *lib_tab_f(int *tab) {
    free(tab);
    tab = NULL;
    return tab;
}

/**
 * Libère un tableau d'entiers passé par pointeur et le met à NULL.
 * @param tab Pointeur sur le tableau à libérer.
 */
void lib_tab_p(int **tab) {
    free(*tab);
    *tab = NULL;
}

/**
 * Libère une matrice d'entiers (toutes les lignes puis le tableau de têtes).
 * @param mat Matrice à libérer.
 * @param nbLig Nombre de lignes.
 * @return NULL (pour assignation sûre côté appelant).
 */
void *lib_mat_f(int **mat, int nbLig) {
    for (int i=0; i<nbLig; i++) {
        free(mat[i]);
    }
    free(mat);
    mat = NULL;
    return mat;
}

/**
 * Libère une matrice d'entiers passée par pointeur et la met à NULL.
 * @param mat Pointeur sur la matrice à libérer.
 * @param nbLig Nombre de lignes.
 */
void lib_mat_p(int ***mat, int nbLig) {
    for (int i=0; i<nbLig; i++) {
        free(*mat[i]);
    }
    free(*mat);
    *mat = NULL;
}

/**
 * Libère le tableau interne d'une matrice d'adjacence et renvoie la struct
 * remise à zéro (version fonction).
 * @param mat Matrice à libérer.
 * @return La matrice avec nbSom = 0 et tableau NULL.
 */
MatAdjacence lib_mat_adj_f(MatAdjacence mat) {
    mat.mat = lib_mat_f(mat.mat, mat.nbSom);
    mat.nbSom = 0;
    return mat;
}

/**
 * Libère le tableau interne d'une matrice d'adjacence (version pointeur).
 * @param mat Pointeur sur la matrice à libérer.
 */
void lib_mat_adj_p(MatAdjacence *mat) {
    mat->mat = lib_mat_f(mat->mat, mat->nbSom);
    mat->nbSom = 0;
}

/**
 * Alloue et initialise une matrice d'incidence CC (alpha, beta, cout).
 * Représentation utilisée par Kruskal : alpha[i] = origine de l'arête i,
 * beta[i] = destination, cout[i] = poids.
 * @param n Nombre d'arêtes.
 * @return La structure allouée.
 */
MatriceIncidenceCC alloc_smicc(int n){
    MatriceIncidenceCC mat;
    mat.nbSom = n;
    mat.alpha = malloc(n * sizeof(int));
    mat.beta = malloc(n * sizeof(int));
    mat.cout = malloc(n * sizeof(int));
    return mat;
}
