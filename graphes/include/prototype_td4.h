//
// Created by dylanm on 14/02/2026.
//

#ifndef TD_GRAPHES_PROTOTYPETD4_H
#define TD_GRAPHES_PROTOTYPETD4_H

#include "prototype_td12.h"
#include "structure.h"

MatAdjacence get_carre_ma(MatAdjacence g);
ListeAdjacence get_carre_la(ListeAdjacence g);

int* marquage_pl(void* g, TypeGraphe type);
void partition(int n, int* marquage, Liste* s1, Liste* s2);
int est_liaison(Liste group, TypeGraphe type, void* g);
int est_biparti(void* g, TypeGraphe type);
int main_td4(void);

#endif //TD_GRAPHES_PROTOTYPETD4_H