#include <stdio.h>
#include <stdlib.h>

#include "../include/prototype_td12.h"

/**
 * Renvoie le nombre de sommets d'un graphe quelle que soit sa représentation.
 * @param g Pointeur générique sur la structure de graphe.
 * @param type Discriminant de la représentation (MAT_ADJACENCE, MAT_INCIDENCE,
 *             FILE_SUCCESSEUR ou LISTE_ADJACENCE).
 * @return Le nombre de sommets.
 */
int nb_som_gen(void* g, TypeGraphe type) {
    if (type == MAT_ADJACENCE) {
        MatAdjacence* mat = (MatAdjacence*) g;
        return mat->nbSom;
    }
    else if (type == MAT_INCIDENCE) {
        MatIncidence* mat = (MatIncidence*) g;
        return mat->nbSom;
    }
    else if (type == FILE_SUCCESSEUR) {
        FileSuccesseur* file = (FileSuccesseur*) g;
        return file->nbSom;
    }
    else if (type == LISTE_ADJACENCE) {
        ListeAdjacence* liste = (ListeAdjacence*) g;
        return liste->nbSom;
    }
    else {
        printf("\n Erreur de type");
        exit(1);
    }
}

/**
 * Renvoie le coût de l'arc (s, t) dans une matrice d'adjacence.
 * @param s Sommet source.
 * @param t Sommet cible.
 * @param ma Matrice d'adjacence valuée.
 * @return Le coût de l'arc s → t.
 */
int cout_ma(int s, int t, MatAdjacence ma) {
    return ma.cout[s][t];
}

/**
 * Renvoie le coût de l'arc (s, t) dans une matrice d'incidence.
 * @param s Sommet source.
 * @param t Sommet cible.
 * @param mi Matrice d'incidence valuée.
 * @return Le coût de l'arc s → t.
 */
int cout_mi(int s, int t, MatIncidence mi) {
    return mi.cout[s][t];
}

/**
 * Renvoie le coût de l'arc (s, t) dans une file de successeurs.
 * @param s Sommet source.
 * @param t Sommet cible.
 * @param fs File de successeurs valuée.
 * @return Le coût de l'arc s → t.
 */
int cout_fs(int s, int t, FileSuccesseur fs) {
    int i = fs.APS[s];
    while (fs.FS[i] != t) {
        i++;
    }
    return fs.cout[i];
}

/**
 * Renvoie le coût de l'arc (s, t) dans une liste d'adjacence.
 * @param s Sommet source.
 * @param t Sommet cible.
 * @param la Liste d'adjacence valuée.
 * @return Le coût de l'arc s → t.
 */
int cout_la(int s, int t, ListeAdjacence la) {
    Liste l = la.tabAdj[s];
    while (donnee(l) != t) {
        l = suivant(l);
    }
    return l->cout;
}

/**
 * Renvoie le coût de l'arc (s, t) quelle que soit la représentation du graphe.
 * @param s Sommet source.
 * @param t Sommet cible.
 * @param g Pointeur générique sur la structure.
 * @param type Discriminant de la représentation.
 * @return Le coût de l'arc s → t.
 */
int cout(int s, int t, void* g, TypeGraphe type) {
    if (type == MAT_ADJACENCE) {
        MatAdjacence* mat = (MatAdjacence*) g;
        return cout_ma(s, t, *mat);
    }
    else if (type == MAT_INCIDENCE) {
        MatIncidence* mat = (MatIncidence*) g;
        return cout_mi(s, t, *mat);
    }
    else if (type == FILE_SUCCESSEUR) {
        FileSuccesseur* file = (FileSuccesseur*) g;
        return cout_fs(s, t, *file);
    }
    else if (type == LISTE_ADJACENCE) {
        ListeAdjacence* liste = (ListeAdjacence*) g;
        return cout_la(s, t, *liste);
    }
    else {
        printf("\n Erreur de type");
        exit(1);
    }
}

/**
 * Teste l'existence d'un arc (s, t) dans une matrice d'adjacence.
 * @param s Sommet source.
 * @param t Sommet cible.
 * @param ma Matrice d'adjacence.
 * @return 1 si l'arc existe, 0 sinon.
 */
int exist_ma(int s, int t, MatAdjacence ma) {
    return ma.mat[s][t] == 1;
}

/**
 * Teste l'existence d'un arc (s, t) dans une matrice d'incidence.
 * @param s Sommet source.
 * @param t Sommet cible.
 * @param mi Matrice d'incidence.
 * @return 1 si l'arc existe, 0 sinon.
 */
int exist_mi(int s, int t, MatIncidence mi) {
    return mi.mat[s][t] == 1;
}

/**
 * Teste l'existence d'un arc (s, t) dans une file de successeurs.
 * @param s Sommet source.
 * @param t Sommet cible.
 * @param fs File de successeurs.
 * @return 1 si l'arc existe, 0 sinon.
 */
int exist_fs(int s, int t, FileSuccesseur fs) {
    int iaps = fs.APS[s];
    int n = fs.APS[s+1] - fs.APS[s];
    int exist = 0;
    while (!exist && iaps<n) {
        if (fs.FS[iaps] == t) {
            exist = 1;
        }
        iaps++;
    }
    return exist;
}

/**
 * Teste l'existence d'un arc (s, t) dans une liste d'adjacence.
 * @param s Sommet source.
 * @param t Sommet cible.
 * @param la Liste d'adjacence.
 * @return 1 si l'arc existe, 0 sinon.
 */
int exist_la(int s, int t, ListeAdjacence la) {
    Liste l = la.tabAdj[s];
    int exist = 0;
    while (!exist && !est_vide(l)) {
        if (donnee(l) == t) {
            exist = 1;
        }
        l = suivant(l);
    }
    return exist;
}

/**
 * Teste l'existence d'un arc (s, t) quelle que soit la représentation.
 * @param s Sommet source.
 * @param t Sommet cible.
 * @param g Pointeur générique sur la structure.
 * @param type Discriminant de la représentation.
 * @return 1 si l'arc existe, 0 sinon.
 */
int exist(int s, int t, void* g, TypeGraphe type) {
    if (type == MAT_ADJACENCE) {
        MatAdjacence* mat = (MatAdjacence*) g;
        return exist_ma(s, t, *mat);
    }
    else if (type == MAT_INCIDENCE) {
        MatIncidence* mat = (MatIncidence*) g;
        return exist_mi(s, t, *mat);
    }
    else if (type == FILE_SUCCESSEUR) {
        FileSuccesseur* file = (FileSuccesseur*) g;
        return exist_fs(s, t, *file);
    }
    else if (type == LISTE_ADJACENCE) {
        ListeAdjacence* liste = (ListeAdjacence*) g;
        return exist_la(s, t, *liste);
    }
    else {
        printf("\n Erreur de type");
        exit(1);
    }
}

/**
 * Renvoie le nombre de sommets d'une matrice d'adjacence.
 * @param ma Matrice d'adjacence.
 * @return Le nombre de sommets.
 */
int nb_som_ma(MatAdjacence ma) {
    return ma.nbSom;
}
