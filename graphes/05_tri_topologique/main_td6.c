#include "../include/prototype_td6.h"
#include "../include/prototype_td12.h"

/**
 * Point d'entrée du TD tri topologique : charge un graphe depuis
 * `graphe.txt`, calcule un tri topologique et affiche la file résultante.
 * @return 0 en cas de succès.
 */
int main_td6(void) {
    MatAdjacence mat = loading("graphe.txt");
    File f = tri_topologique_acyclique(&mat, MAT_ADJACENCE);

    while (!est_vide(f)) {
        printf("%d | ",donnee(f)+1);
        f = supp_tete(f);
    }
}