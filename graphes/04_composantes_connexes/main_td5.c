#include <stdio.h>

#include "../include/prototype_td5.h"
#include "../include/prototype_td12.h"

/**
 * Point d'entrée du TD composantes connexes : charge un graphe depuis
 * `graphe.txt`, calcule les composantes connexes puis les affiche.
 * @return 0 en cas de succès.
 */
int main_td5(void) {
    MatAdjacence mat = loading("graphe.txt");
    int* CC = get_cc(&mat, MAT_ADJACENCE);
    int n = nb_som_gen(&mat, MAT_ADJACENCE);
    printf("|");
    for (int i=0; i<n; i++) {
        printf(" %d |", CC[i]);
    }
    return 0;
}