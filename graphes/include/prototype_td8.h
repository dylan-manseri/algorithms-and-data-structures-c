//
// Created by dylanm on 25/03/2026.
//

#ifndef TD_GRAPHES_PROTOTYPETD8_H
#define TD_GRAPHES_PROTOTYPETD8_H

#include <stdio.h>
#include "structure.h"

int est_chemin_simple(int S, int P, int** g, int n, int* visite, int* parent);
int** create_graphe_ecart(MatAdjacence g);
int capacite_residuelle(int S, int P, int** ge, int* parent);
int ford_fulkerson(int S, int P, MatAdjacence g);

#endif //TD_GRAPHES_PROTOTYPETD8_H