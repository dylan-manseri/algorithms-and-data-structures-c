/**
 *Exercice du TP sur la lecture d'un fichier
 */

#include <stdio.h>
#include "../../include/prototype_td12.h"

/**
 * Nature du graphe : 1 si orienté, 0 sinon
 * @param nom Nom du fichier
 * @return Matrice adjacence assosciée au graphe
 */
MatAdjacence loading(char *nom) {
    FILE *fe = fopen(nom, "r");
    int nature, nbSom;
    fscanf(fe, "Nature du graphe = %d;\n", &nature);
    fscanf(fe,"Nombre de sommets = %d;\n", &nbSom);
    MatAdjacence mat;
    mat.nbSom = nbSom;
    int s, t;
    mat = alloc_sma_f(nbSom);
    for (int j=0; j < nbSom; j++) {
        for (int k=0; k < nbSom; k++) {
            mat.mat[j][k] = 0;
        }
    }
    fscanf(fe, "START");
    if (nature == 1) {
       while (fscanf(fe, "END") == 0){
        fscanf(fe, "%d-%d;\n", &s, &t);
        mat.mat[s-1][t-1] = 1;                  // On commence à 0 en algo, à 1 dans la vraie vie donc on enlève 1
        }
    } else {
        while (fscanf(fe, "END") == 0){
            fscanf(fe, "%d-%d;\n", &s, &t);
            mat.mat[s-1][t-1] = 1;                  // On commence à 0 en algo, à 1 dans la vraie vie donc on enlève 1
            mat.mat[t-1][s-1] = 1;
        }
    }

    fclose(fe);
    return mat;
}