#include <math.h>

#include "structure.h"

/** Sentinelle utilisée par le tri fusion (mise à jour au runtime). */
int VMAX=-1;

/** Somme de deux entiers — exemple de fonction passée en paramètre. */
int somme(int a, int b) {
    return a+b;
}

/** Produit de deux entiers — exemple de fonction passée en paramètre. */
int produit(int a, int b) {
    return a*b;
}

/** Division entière de a par b — exemple de fonction passée en paramètre. */
int division(int a, int b) {
    return a/b;
}

/**
 * Affiche les n premiers entiers d'un tableau entre accolades.
 * @param tab Tableau d'entiers.
 * @param n   Nombre d'éléments à afficher.
 */
void printTab(int *tab, int n) {
    printf("{ ");
    for (int i=0; i<n; i++) {
        printf("%d ", *(tab+i));
    }
    printf("}\n");
}

/**
 * Affiche les n premiers complexes d'un tableau sous la forme {pr, pi}.
 * @param tab Tableau de complexes.
 * @param n   Nombre d'éléments à afficher.
 */
void printTabComplexe(Complexe *tab, int n) {
    printf("{ ");
    for (int i=0; i<n; i++) {
        printf("{%d, %d}", (*(tab+i)).pr, (*(tab+i)).pi);
    }
    printf("}\n");
}

/**
 * Recherche séquentielle avec sentinelle : place elt en tab[n] puis scanne
 * tab jusqu'à trouver une cellule satisfaisant le prédicat comp.
 * @param n    Taille effective du tableau (place [n] réservée à la sentinelle).
 * @param tab  Tableau d'entiers de taille au moins n+1.
 * @param elt  Élément recherché.
 * @param comp Prédicat de comparaison passé en paramètre.
 * @return 1 si elt est trouvé avant la sentinelle, 0 sinon.
 */
int recherche(int n, int *tab, int elt, Fcomp comp) {
    int i;
    tab[n]=elt;
    i=0;
    while (!(*comp)(elt,tab[i])) {
        i++;
    }
    return i<n;
}

/** Prédicat strict : renvoie 1 si i < j. */
int estInferieur(int i, int j) {
    return i<j;
}

/** Prédicat strict : renvoie 1 si i > j. */
int estSuperieur(int i, int j) {
    return i>j;
}

/** Indice médian d'un intervalle (division entière). */
int indiceMilieu(int n) {
    return n/2;
}

/** Compare deux complexes par module : renvoie 1 si |i| < |j|. */
int estInferieurComp(Complexe i, Complexe j) {
    double z1 = sqrt(i.pr*i.pr+i.pi*i.pi);
    double z2 = sqrt(j.pr*j.pr+j.pi*j.pi);
    return z1<z2;
}

/** Compare deux complexes par module : renvoie 1 si |i| > |j|. */
int estSuperieurComp(Complexe i, Complexe j) {
    double z1 = sqrt(i.pr*i.pr+i.pi*i.pi);
    double z2 = sqrt(j.pr*j.pr+j.pi*j.pi);
    return z1>z2;
}

/**
 * Copie tab[indInf..indSup] dans tmp[0..indSup-indInf].
 * @param tab    Tableau source.
 * @param indInf Indice de début (inclus).
 * @param indSup Indice de fin   (inclus).
 * @param tmp    Tableau de destination, suffisamment grand.
 */
void copie(int *tab, int indInf, int indSup, int *tmp) {
    int j=0;
    for (int i=indInf; i<indSup+1; i++) {
        *(tmp+j) = *(tab+i);
        j++;
    }
}

/**
 * Étape de fusion du tri fusion. Fusionne tab[indInf..indMil] et
 * tab[indMil+1..indSup], déjà triés selon fcomp, dans tab[indInf..indSup].
 * Utilise tmp1/tmp2 comme tampons et VMAX comme sentinelle.
 * @param tab    Tableau à fusionner.
 * @param indInf Borne inférieure.
 * @param indMil Borne médiane.
 * @param indSup Borne supérieure.
 * @param tmp1   Tampon pour la moitié gauche.
 * @param tmp2   Tampon pour la moitié droite.
 * @param fcomp  Prédicat d'ordre (ex. `estInferieur` pour un tri croissant).
 */
void fusion(int *tab, int indInf, int indMil, int indSup, int *tmp1, int *tmp2, Fcomp fcomp) {
    copie(tab, indInf, indMil, tmp1);
    copie(tab, indMil+1, indSup, tmp2);
    tmp1[indMil-indInf+1] = VMAX;
    tmp2[indSup-indMil] = VMAX;
    int i=0;
    int j=0;
    for (int k=indInf; k<=indSup; k++) {
        if ((*fcomp)(*(tmp1+i), *(tmp2+j))) {
            *(tab+k) = *(tmp1+i);
            i++;
        }
        else {
            *(tab+k) = *(tmp2+j);
            j++;
        }
    }
}

/**
 * Tri fusion paramétré par un prédicat d'ordre.
 * @param tab    Tableau à trier sur place.
 * @param indMin Indice de début (inclus).
 * @param indSup Indice de fin   (inclus).
 * @param tmp1   Tampon auxiliaire.
 * @param tmp2   Tampon auxiliaire.
 * @param fcomp  Prédicat de comparaison (`estInferieur` ou `estSuperieur`).
 */
void triFusion(int *tab, int indMin, int indSup, int *tmp1, int *tmp2, Fcomp fcomp) {
    if (indMin<indSup) {
        int indMil = indiceMilieu(indMin+indSup);
        triFusion(tab, indMin, indMil, tmp1, tmp2, fcomp);
        triFusion(tab, indMil+1, indSup, tmp1, tmp2, fcomp);
        fusion(tab, indMin, indMil, indSup, tmp1, tmp2, fcomp);
    }
}

/**
 * Démonstration : trie un tableau d'entiers dans les deux ordres en
 * variant à la fois le prédicat et la valeur de la sentinelle VMAX.
 * @return 0 en cas de succès.
 */
int main(void) {
    //Fcomp tabFonc[3] = {somme, produit, division};
    int tab[10] = {8,4,6,9,7,2,8,4,1,2};
    int n=10;
    printTab(tab, 10);
    int *tmp1=malloc(n*sizeof(int));
    int *tmp2=malloc(n*sizeof(int));
    triFusion(tab, 0, n-1,tmp1, tmp2, estSuperieur);
    printTab(tab, n);
    VMAX=100;
    triFusion(tab, 0, n-1,tmp1, tmp2, estInferieur);
    printTab(tab, n);
    Complexe tabC[5]= {{10,5}, {5,6},{8,9},{2,3},{4,3}};
    printTabComplexe(tabC, 5);
}