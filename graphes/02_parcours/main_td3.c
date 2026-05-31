#include "../include/prototype_td3.h"
#include "../include/prototype_td12.h"

/**
 * Point d'entrée du TD parcours : charge un graphe depuis `graphe.txt`
 * et lance un parcours en profondeur (DFS) depuis le sommet 0.
 * @return 0 en cas de succès.
 */
int main_td3(void) {
    MatAdjacence mat = loading("graphe.txt");
    parcours_profondeur(0, &mat, MAT_ADJACENCE);
    //parcours_largeur(0, &mat, MAT_ADJACENCE);
    return 0;
}