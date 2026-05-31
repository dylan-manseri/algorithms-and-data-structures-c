/**
 * Je ne sais pas vraiment comment organiser les fichiers du cours.
 * Donc ici ça sera tous les algos de l'exo 3.
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../include/prototype_td12.h"

/**
 * Le tableau est bizarre, et c'est un choix, l'indice 0 stocke le nombre de successeurs
 */
int* get_succ_mat_adj(int s, MatAdjacence g){
    int n = nb_som_ma(g);
    int *tab = malloc((n+1) * sizeof(int));
    int j=1;
    int i;
    for(i=0; i<n; i++){
        if(g.mat[s][i] == 1){
            tab[j] = i;
            j++;
        }
    }
    tab[0] = j-1;
    return tab;
}

/**
 * Renvoie le tableau des prédécesseurs d'un sommet dans une matrice
 * d'adjacence. L'indice 0 stocke le nombre de prédécesseurs.
 * @param s Sommet cible.
 * @param g Matrice d'adjacence.
 * @return Tableau (taille_au_premier_indice, prédécesseurs…) alloué dynamiquement.
 */
int* get_pred_mat_adj(int s, MatAdjacence g){
    int n = nb_som_ma(g);
    int j=1;
    int *tab = malloc((n+1) * sizeof(int));
    for(int i=0; i<n; i++){
        if(g.mat[i][s] == 1){
            tab[j] = i;
            j++;
        }
    }
    tab[0] = j-1;
    return tab;
}

/**
 * Ici pareil, on cherche seulement à traiter les successeurs D'UN sommets.
 * On utilise la représentation avec la file de successeur.
 * Le premier indice indique la taille du tableau
 */
int* get_succ_fs(int s, FileSuccesseur fs){
    int start = fs.APS[s];
    int end = fs.APS[s+1];
    int nb = end - start;
    int *tab = malloc((nb+1) * sizeof(int));
    int k=1;
    for(int i=start; i<end; i++){
        tab[k] = fs.FS[i];
        k++;
    }
    tab[0] = k-1;
    return tab;
}

/**
 * Renvoie le tableau des prédécesseurs d'un sommet dans une file de successeurs.
 * L'indice 0 stocke le nombre de prédécesseurs.
 * @param s Sommet cible.
 * @param fs File de successeurs.
 * @return Tableau (taille_au_premier_indice, prédécesseurs…) alloué dynamiquement.
 */
int* get_pred_fs(int s, FileSuccesseur fs){
    int l = 1;
    int *tab = malloc((fs.nbSom+1) * sizeof(int));
    for(int i=0; i<fs.nbSom; i++){
        for(int j=fs.APS[i]; j<fs.APS[i+1]; j++){
            if(fs.FS[j] == s){
                tab[l] = i;
                l++;
            }
        }
    }
    tab[0] = l-1;
    return tab;
}

/**
 * Renvoie le tableau des successeurs d'un sommet dans une liste d'adjacence.
 * L'indice 0 stocke le nombre de successeurs.
 * @param s Sommet source.
 * @param la Liste d'adjacence.
 * @return Tableau (taille_au_premier_indice, successeurs…) alloué dynamiquement.
 */
int* get_succ_l(int s, ListeAdjacence la){
    Liste succ = la.tabAdj[s];
    int* tab = malloc((la.nbSom+1) * sizeof(int));
    int i=1;
    while(!est_vide(succ)){
        tab[i] = donnee(succ);
        succ = suivant(succ);
        i++;
    }
    tab[0] = i-1;
    return tab;
}

/**
 * Renvoie le tableau des prédécesseurs d'un sommet dans une liste d'adjacence.
 * L'indice 0 stocke le nombre de prédécesseurs.
 * @param s Sommet cible.
 * @param la Liste d'adjacence.
 * @return Tableau (taille_au_premier_indice, prédécesseurs…) alloué dynamiquement.
 */
int* get_pred_l(int s, ListeAdjacence la){
    Liste* tabL = la.tabAdj;
    int *tab = malloc((la.nbSom+1) * sizeof(int));
    Liste iSucc;
    int k = 1;
    for(int i=0; i<la.nbSom; i++){
        iSucc = tabL[i];
        while(!est_vide(iSucc)){
            if(donnee(iSucc) == s){
                tab[k] = i;
                k++;
            }
            iSucc = suivant(iSucc);
        }
    }
    tab[0] = k-1;
    return tab;
}

/**
 * Renvoi un tableau des successeurs dépendamment du type du graphe (via généricité)
 * Le premier indice du tableau est le nombre de successeurs
 * @param s Le sommet dont on souhaite connaître les successeurs
 * @param type Le type de graphe
 * @return Le tableau des successeurs
 */
int* get_succ_by_type(int s, TypeGraphe type, void* g) {
    int* succ;
    if (type == MAT_ADJACENCE) {
        MatAdjacence* mat = (MatAdjacence*) g;
        succ = get_succ_mat_adj(s, *mat);
    }
    else if (type == FILE_SUCCESSEUR) {
        FileSuccesseur* fs = (FileSuccesseur*) g;
        succ = get_succ_fs(s, *fs);
    }
    else if (type == LISTE_ADJACENCE) {
        ListeAdjacence* la = (ListeAdjacence*) g;
        succ = get_succ_l(s, *la);
    }
    else {
        printf("\nErreur de type");
        exit(1);
    }
    return succ;
}

/**
 * Même chose pour les prédécesseurs
 * @param s Le sommet dont on souhaite connaître les prédécesseurs
 * @param type Le type de graphe
 * @param g Le graphe
 * @return Le tableau des prédécesseurs
 */
int* get_pred_by_type(int s, TypeGraphe type, void* g) {
    int* succ;
    if (type == MAT_ADJACENCE) {
        MatAdjacence* mat = (MatAdjacence*) g;
        succ = get_pred_mat_adj(s, *mat);
    }
    else if (type == FILE_SUCCESSEUR) {
        FileSuccesseur* fs = (FileSuccesseur*) g;
        succ = get_pred_fs(s, *fs);
    }
    else if (type == LISTE_ADJACENCE) {
        ListeAdjacence* la = (ListeAdjacence*) g;
        succ = get_pred_l(s, *la);
    }
    else {
        printf("\nErreur de type");
        exit(1);
    }
    return succ;
}

/**
 * Renvoie le nombre de prédécesseurs d'un sommet d'une matrice d'adjacence.
 * @param t Le sommet.
 * @param ma La matrice d'adjacence.
 * @return Le nombre de prédécesseurs.
 */
int get_nb_pred_ma(int t, MatAdjacence ma) {
    int n = ma.nbSom;
    int nb = 0;
    for (int s=0; s<n; s++) {
        if (ma.mat[s][t] == 1) {
            nb++;
        }
    }
    return nb;
}

/**
 * Renvoie le nombre de prédécesseurs d'un sommet d'une file de successeurs.
 * @param t Le sommet.
 * @param fs La file de successeurs.
 * @return Le nombre de prédécesseurs.
 */
int get_nb_pred_fs(int t, FileSuccesseur fs) {
    int n = fs.nbArcs;
    int nb = 0;
    for (int a=0; a<n; a++) {
        if (fs.FS[a] == t) {
            nb++;
        }
    }
    return nb;
}

/**
 * Renvoie le nombre de prédécesseurs d'un sommet d'une liste d'adjacence.
 * @param t Le sommet.
 * @param la La liste d'adjacence.
 * @return Le nombre de prédécesseurs.
 */
int get_nb_pred_la(int t, ListeAdjacence la) {
    int n = la.nbSom;
    Liste l;
    int nb = 0;
    for (int s=0; s<n; s++) {
        l = la.tabAdj[s];
        while (!est_vide(l)) {
            if (donnee(l) == t) {
                nb++;
            }
        }
    }
    return nb;
}

/**
 * Renvoie le nombre de prédécesseurs d'un sommet d'un graphe quelconque.
 * @param t Le sommet.
 * @param g Le graphe.
 * @param type Le type de graphe.
 * @return Le nombre de prédécesseurs.
 */
int get_nb_pred(int t, void* g, TypeGraphe type) {
    int nb;
    if (type == MAT_ADJACENCE) {
        MatAdjacence* mat = (MatAdjacence*) g;
        nb = get_nb_pred_ma(t, *mat);
    }
    else if (type == FILE_SUCCESSEUR) {
        FileSuccesseur* fs = (FileSuccesseur*) g;
        nb = get_nb_pred_fs(t, *fs);
    }
    else if (type == LISTE_ADJACENCE) {
        ListeAdjacence* la = (ListeAdjacence*) g;
        nb = get_nb_pred_la(t, *la);
    }
    else {
        printf("\nErreur de type");
        exit(1);
    }
    return nb;
}


/**
 * Vérifie si un graphe contient une boucle
 * @param ma
 * @return
 */
int est_boucle_ma(MatAdjacence ma){
    int i=0;
    int trouve = 0;
    while(!trouve && i<ma.nbSom){
        if(ma.mat[i][i] == 1){
            trouve = 1;
        }
        i++;
    }
    return trouve;
}

/**
 * Teste si une file de successeurs contient une boucle (arc (s, s)).
 * @param fs File de successeurs.
 * @return 1 si une boucle est trouvée, 0 sinon.
 */
int est_boucle_fs(FileSuccesseur fs){
    int trouve = 0;
    int i=0, j;
    while(!trouve && i<fs.nbSom){
        j=fs.APS[i];
        while(!trouve && j<fs.APS[i+1]){
            if(fs.FS[j] == i){
                trouve = 1;
            }
            j++;
        }
        i++;
    }
    return trouve;
}

/**
 * Teste si une liste d'adjacence contient une boucle (arc (s, s)).
 * @param la Liste d'adjacence.
 * @return 1 si une boucle est trouvée, 0 sinon.
 */
int est_boucle_la(ListeAdjacence la){
    int i=1;
    int trouve=0;
    Liste* tabL = la.tabAdj;
    Liste succ;
    while(!trouve && i<la.nbSom){
        succ=tabL[i];
        while(!est_vide(succ) && donnee(succ)<i){
            succ=suivant(succ);
        }
        if(!est_vide(succ) && donnee(succ) == i){
            trouve=1;
        }
        i++;
    }
    return trouve;
}

/**
 * Recherche le sommet avec le plus de successeurs
 * @param mat
 * @return
 */
int max_succ_ma(MatAdjacence mat){
    int n = mat.nbSom;
    int** matrice = mat.mat;
    int current;
    int maxSucc = 0;
    int somMax = 0;
    for(int s=0; s<n; s++){
        current=0;
        for(int t=0; t<n; t++){
            if(matrice[s][t] == 1) current++;
        }
        if(current > maxSucc){
                maxSucc = current;
                somMax = s+1;
            }
    }
    return somMax;
}

/**
 * Recherche le sommet ayant le plus de successeurs dans une file de successeurs.
 * @param fs File de successeurs.
 * @return L'indice (1-based) du sommet ayant le plus grand degré sortant.
 */
int max_succ_fs(FileSuccesseur fs){
    int n=fs.nbSom;
    int max=0;
    int maxSucc=0;
    int current;
    for(int i=0; i<n; i++){
        current = fs.APS[i+1] - fs.APS[i];
        if(current > maxSucc){
            maxSucc=current;
            max=i+1;
        }

    }
    return max;
}

/**
 * Recherche le sommet ayant le plus de successeurs dans une liste d'adjacence.
 * @param la Liste d'adjacence.
 * @return L'indice du sommet ayant le plus grand degré sortant.
 */
int max_succ_la(ListeAdjacence la){
    int max=0;
    int maxSucc=0;
    Liste* tabL = la.tabAdj;
    int n = la.nbSom;
    Liste succ;
    int current;
    for(int i=0; i<n; i++){
        succ = tabL[i];
        current=0;
        while(!est_vide(succ)){
            current++;
            succ=suivant(succ);
        }
        if(current>maxSucc){
            maxSucc=current;
            max=i;
        }
    }
    return max;
}