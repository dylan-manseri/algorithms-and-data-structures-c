

#ifndef TD_GRAPHES_PROTOTYPETD7_H
#define TD_GRAPHES_PROTOTYPETD7_H

#include <stdio.h>
#include "structure.h"
void ford(int sd, void* g, TypeGraphe type, int* D, int* P);
void dijkstra(int sd, void* g, TypeGraphe type, int* D, int* P);
void bellman(int sd, void*g, TypeGraphe type, int* D, int* P);
void floyd(void* g, TypeGraphe type, int** D, int** P);

#endif //TD_GRAPHES_PROTOTYPETD7_H