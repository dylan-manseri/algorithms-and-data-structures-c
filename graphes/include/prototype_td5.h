//
// Created by dylnm on 01/03/2026.
//

#ifndef TD_GRAPHES_PROTOTYPETD5_H
#define TD_GRAPHES_PROTOTYPETD5_H

#include "structure.h"

void re_parcours_profondeur_cc(int *s, int* visite, void* g, TypeGraphe type, int n, int* nbSomVisite, int* CC, int* nbCC);
int* get_cc(void* g, TypeGraphe type);
void re_parcours_profondeur_suffixe(int s, Pile* p, int* nbSomVisite, void* g, int* visite, int n, TypeGraphe type);
void re_parcours_profondeur_cfc_t(int s, int* nbSomVisite, void* g, int* visite, int n, int nbCFC, int* CFC, TypeGraphe type);
int* get_cfc(void* g, TypeGraphe type);
void fermeture_transitive(void* g, TypeGraphe type, int** mat);

int main_td5(void);

#endif //TD_GRAPHES_PROTOTYPETD5_H