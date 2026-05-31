#include "structure.h"

/**
 * Teste la primalité d'un entier par divisions successives jusqu'à √n.
 * @param nbr Entier à tester.
 * @return 1 si nbr est premier, 0 sinon.
 */
int est_premier(int nbr) {
    int i = 2;
    while (i*i <= nbr && nbr%i != 0) {
        i++;
    }
    return i*i > nbr;
}

/**
 * Divise nbr par p tant que p divise nbr et compte le nombre de divisions.
 * Modifie nbr en place.
 * @param nbr Pointeur sur le nombre à diviser (modifié).
 * @param p Diviseur.
 * @return Le nombre de divisions effectuées (= multiplicité de p dans nbr).
 */
int nbr_division(int *nbr, int p) {
    int cpt = 0;
    while ((*nbr) % p == 0) {
        *nbr = (*nbr)/p;
        cpt++;
    }
    return cpt;
}

/**
 * Décompose un entier en produit de facteurs premiers, stocké dans une liste.
 * Chaque cellule contient (facteur, multiplicité).
 * @param nbr Entier à décomposer.
 * @param l Liste d'accumulation (peut être vide).
 * @return La liste enrichie de la décomposition.
 */
Liste decomposition(int nbr, Liste l) {
    int i = 2;
    int div;
    while (i <= nbr) {
        if (est_premier(i) && nbr%i == 0) {
            div = nbr_division(&nbr, i);
            FactPremier fp = create_fact_premier(i, div);
            l = inser_queue(fp, l);
        }
        i++;
    }
    return l;
}

/**
 * Construit un tableau de TabLDFP associant chaque entier du tableau d'entrée
 * à sa décomposition en facteurs premiers.
 * @param tab Tableau d'entiers d'entrée.
 * @param taille Taille du tableau.
 * @return Tableau de TabLDFP alloué dynamiquement (à libérer par l'appelant).
 */
TabLDFP* convert_tab_to_liste(int *tab, int taille) {
    TabLDFP *tab_ldfp = malloc(taille * sizeof(TabLDFP));
    int nbr;
    for (int i=0; i<taille; i++) {
        Liste current = create_liste();
        nbr = tab[i];
        current = decomposition(nbr, current);
        TabLDFP cel = create_tab_ldfp(nbr, current);
        *(tab_ldfp+i) = cel;
    }
    return tab_ldfp;
}

/**
 * Renvoie le minimum de deux entiers.
 * @param a Premier entier.
 * @param b Second entier.
 * @return Le plus petit des deux.
 */
int minimum(int a, int b) {
    if (a<b) return a;
    else return b;
}

/**
 * Calcule nbr^exp par produit itéré.
 * @param nbr Base.
 * @param exp Exposant entier positif.
 * @return La puissance entière nbr^exp.
 */
int puissance(int nbr, int exp){
    for (int i=1; i<exp; i++) {
        nbr *= nbr;
    }
    return nbr;
}

/**
 * Calcule l'intersection multiplicative de deux listes de facteurs premiers :
 * pour chaque facteur commun, conserve le minimum des deux multiplicités.
 * @param l1 Première décomposition.
 * @param l2 Seconde décomposition.
 * @return Une liste à une cellule contenant le produit des facteurs communs.
 */
Liste intersection(Liste l1, Liste l2) {
    int f1, f2, occ1, occ2;
    Liste l = create_liste();
    l = malloc(sizeof(struct cellule));
    FactPremier fp;
    fp.fact = 1;
    fp.nbOcc = 1;
    l->donnee = fp;
    l->suivant = NULL;
    while (!est_vide(l1) && !est_vide(l2)) {
        f1 = fact(donnee(l1));
        f2 = fact(donnee(l2));
        occ1 = nb_occ(donnee(l1));
        occ2 = nb_occ(donnee(l2));
        if (f1 == f2) {
            fp.fact *= puissance(f1, minimum(occ1, occ2));
            fp.nbOcc = 1;
            l->donnee = fp;
            l1 = suivant(l1);
            l2 = suivant(l2);
        }
        else {
            if (f1 < f2) {
                l1 = suivant(l1);
            }
            else {
                l2 = suivant(l2);
            }
        }
    }
    return l;
}

/**
 * Calcule le PGCD d'un tableau de n entiers par intersection successive des
 * décompositions en facteurs premiers.
 * @param tab Tableau des entiers.
 * @param n Nombre d'entiers.
 * @return Le PGCD.
 */
int pgcd(int *tab, int n) {
    if (n < 1) {
        return tab[n];
    }
    TabLDFP *tab_ldfp = convert_tab_to_liste(tab, n);
    Liste l = intersection(liste(tab_ldfp[0]), liste(tab_ldfp[1]));
    for (int i=2; i<n; i++) {
        l = intersection(liste(tab_ldfp[i]), l);
    }
    free(tab_ldfp);
    return fact(donnee(l));
}