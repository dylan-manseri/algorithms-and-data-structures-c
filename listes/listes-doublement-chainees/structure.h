#ifndef STRUCTURE_LISTE_DOUBLE_H
#define STRUCTURE_LISTE_DOUBLE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double coef;
    int    degre;
} Monome;

typedef struct cellule {
    Monome          monome;
    struct cellule *suivant;
    struct cellule *precedent;
} *Polynome;

typedef struct {
    Polynome tete;
    Polynome queue;
} PolynomeTQ;

// Primitives Monome / Polynome
int      degre(Monome mon);
double   coef(Monome mon);
Monome   monome(Polynome p);
Polynome suivant(Polynome p);
Polynome precedent(Polynome p);

// Primitives polynôme vide
Polynome initP(void);
int      estVideP(Polynome p);
Monome   newMon(double coef, int degre);
void     printPolynome(Polynome p);

// Exercice 1 — insertion, suppression, opérations algébriques (LDC)
Polynome allocMemRemp(Monome m);
Polynome inserTete(Monome m, Polynome p);
Polynome suppTete(Polynome p);
Polynome adresseInsertion(Monome m, Polynome p);
int      zero(double d);
Polynome inserQueue(Monome m, Polynome der, Polynome p);
Polynome inserApres(Monome m, Polynome ai, Polynome p);
Polynome suppQueue(Polynome as, Polynome p);
Polynome suppAilleurs(Polynome ai, Polynome p);
Polynome inserMonPoly(Monome m, Polynome p);
Polynome rechMonPoly(Monome m, Polynome p);
Polynome suppMonPoly(Monome m, Polynome p);
Polynome delPolynome(Polynome p);

double   maxCoef(Polynome p);
double   somCoef(Polynome p);
Polynome generPoly(int n, int *tab);
Polynome derivPoly(Polynome p);
Polynome somPoly(Polynome p1, Polynome p2);

#endif