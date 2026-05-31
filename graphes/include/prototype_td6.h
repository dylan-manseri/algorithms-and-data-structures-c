#include <stdio.h>


#ifndef TD_GRAPHES_PROTOTYPETD6_H
#define TD_GRAPHES_PROTOTYPETD6_H

#include "structure.h"

int est_vide_ma(MatAdjacence ma);
int est_vide_fs(FileSuccesseur fs);
int est_vide_l_adj(ListeAdjacence la);
int est_vide_graphe(void* g, TypeGraphe type);

int degre_entrant_ma(MatAdjacence ma, int t);
int degre_entrant_fs(FileSuccesseur fs, int t);
int degre_entrant_la(ListeAdjacence la, int t);
int degre_entrant(void* g, TypeGraphe type, int t);

File tri_topologique_acyclique(void* g, TypeGraphe type);

int main_td6();
#endif //TD_GRAPHES_PROTOTYPETD6_H