#include <stdio.h>

#include "../include/prototype_td4.h"

/**
 * Point d'entrée du TD bipartisme & carré : charge un graphe depuis
 * `graphe.txt` puis teste s'il est biparti.
 * @return 0 en cas de succès.
 */
int main_td4(void) {
    MatAdjacence ma = loading("graphe.txt");
    //MatAdjacence ma2 = get_carre_ma(ma);
    //print_mat(&ma2, MAT_ADJACENCE);

    /*ListeAdjacence la;
    alloc_la(4, &la);
    la.tabAdj[0] = inser_queue(1, la.tabAdj[0]);
    la.tabAdj[1] = inser_queue(2, la.tabAdj[1]);
    la.tabAdj[2] = inser_queue(0, la.tabAdj[2]);
    la.tabAdj[2] = inser_queue(1, la.tabAdj[2]);
    la.tabAdj[3] = inser_queue(3, la.tabAdj[3]);
    ListeAdjacence l2 = get_carre_la(la);
    print_la(l2);*/

    if (est_biparti(&ma, MAT_ADJACENCE)) {
        printf("Le graphe est biparti\n");
    }
    else {
        printf("Le graphe n'est pas biparti\n");
    }

    return 0;
}