#ifndef PROTOTYPETD3_H
#define PROTOTYPETD3_H

#include "structure.h"

int main_td3(void);

int som_suivant(int s, int n, int* visite);
void re_parcours_profondeur(int *s, int* visite, void* g, TypeGraphe type, int n, int* nbSomVisite);
void parcours_profondeur(int sd, void* g, TypeGraphe type);

void it_parcours_largeur(int *s, int* visite, void* g, int n, int *nbSomVisite, TypeGraphe type);
void parcours_largeur(int sd, void* g, TypeGraphe type);

#endif