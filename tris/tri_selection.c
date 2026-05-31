#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*--------------------------ALGORITHMES DE TRI--------------------------*/

/**
 * Échange en place les valeurs des indices i1 et i2 du tableau.
 * @param tab Tableau d'entiers.
 * @param i1 Premier indice.
 * @param i2 Second indice.
 */
void permutation(int *tab, int i1, int i2) {
    int cpt = *(tab+i1);
    *(tab+i1) = *(tab+i2);
    *(tab+i2) = cpt;
}

/**
 * Recherche l'indice du minimum dans la plage [start, end[ du tableau.
 * @param tab Tableau d'entiers.
 * @param start Indice de début (inclus).
 * @param end Indice de fin (exclu).
 * @return L'indice de la plus petite valeur dans la plage.
 */
int indice_min(int *tab, int start, int end) {
    int mini = *(tab+start);
    int indMini = start;
    for (int i=start; i<end; i++) {
        if (*(tab+i) < mini){
            mini = *(tab+i);
            indMini = i;
        }
    }
    return indMini;
}

/**
 * Trie un tableau d'entiers par sélection (in-place).
 * Complexité : O(n²) dans tous les cas.
 * @param tab Tableau à trier.
 * @param n Taille du tableau.
 */
void tri_selection(int* tab, int n) {
    int iMin;
    for (int i=0; i<n; i++) {
        iMin = indice_min(tab, i, n);
        if (*(tab+i) != iMin) {
            permutation(tab, iMin, i);
        }
    }
}

/*--------------------------UTILITAIRES--------------------------*/

/**
 * Alloue et remplit un tableau d'entiers aléatoires dans [100, 199].
 * @param n Taille du tableau à générer.
 * @return Pointeur vers le tableau alloué (à libérer par l'appelant).
 */
int* random_tab(int n) {
    int *tab = malloc(n * sizeof(int));
    for (int i=0; i<n; i++) {
        *(tab+i) = (rand() % 100) + 100;
    }
    return tab;
}

/**
 * Affiche les n premières valeurs d'un tableau sur la sortie standard.
 * @param tab Tableau d'entiers.
 * @param n Nombre de valeurs à afficher.
 */
void print_tab(int* tab, int n) {
    for (int i=0; i<n; i++) {
        printf("%d ", *(tab+i));
    }
    printf("\n\n");
}

/*--------------------------EXERCICES--------------------------*/

/**
 * Exo 1.a — Trie un petit tableau codé en dur, pour valider l'algorithme.
 */
void exo1a(){
    int tab[5] = {8,3,2,10,7};
    printf("Le tableau avant le tri : \n");
    print_tab(tab, 5);
    printf("\n");
    tri_selection(tab, 5);
    printf("Le tableau apres le tri : \n");
    print_tab(tab, 5);
}

/**
 * Exo 1.b — Saisie d'un tableau au clavier puis tri par sélection.
 */
void exo1b() {
    int n;
    printf("Merci d'indiquer une taille pour votre tableau.\n");
    scanf("%d", &n);
    int *tab = malloc(n * sizeof(int));
    printf("Merci d'indiquer les valeurs de votre tableau à la suite\n");
    for (int i=0; i<n; i++) {
        scanf("%d",tab+i);
    }
    printf("Le tableau que vous avez entre : \n");
    print_tab(tab, n);
    printf("\n");
    tri_selection(tab, n);
    printf("Le tableau trie : \n");
    print_tab(tab, n);
    free(tab);
    tab=NULL;
}

/**
 * Exo 2.a — Génère un tableau aléatoire puis le trie.
 */
void exo2a() {
    int *tab;
    int n = rand() % 100 + 100;
    tab=random_tab(n);
    printf("Le tableau genere aleatoirement : \n");
    print_tab(tab, 5);
    printf("\n");
    tri_selection(tab, n);
    printf("Le tableau trie : \n");
    print_tab(tab, 5);
    free(tab);
    tab=NULL;
}

/**
 * Exo 2.b — Charge un tableau depuis `data/donnees.txt` puis le trie.
 */
void exo2b() {
    int n;
    FILE *f = fopen("data/donnees.txt", "r");
    fscanf(f, "%d", &n);
    int *tab = malloc(n * sizeof(int));
    for (int i=0; i<n; i++) {
        fscanf(f, "%d", tab+i);
    }
    printf("Le tableau cree a partir du fichier : \n");
    print_tab(tab, n);
    printf("\n");
    tri_selection(tab, n);
    printf("Le tableau trie : \n");
    print_tab(tab, n);
    free(tab);
    tab=NULL;
}

/**
 * Exo 3 — Mesures expérimentales : trie 40 tableaux aléatoires de tailles
 * croissantes (pas de 1000), et écrit les couples (n, durée) dans
 * `data/resultSel.txt` pour exploitation gnuplot.
 */
void exo3() {
    FILE *f = fopen("../data/resultSel.txt", "w");
    int n=0;
    double t;
    int *tab;
    int i;
    for (i=0; i<40; i++) {
        tab = random_tab(n=n+1000);
        clock_t start = clock();
        tri_selection(tab, n);
        clock_t end = clock();
        t = (double)(end - start) / CLOCKS_PER_SEC;
        fprintf(f, "%d %f\n", n, t);
        free(tab);
        tab=NULL;
    }
    fclose(f);
    printf("Tris realises avec succes, resultats dans data/resultSel.txt");
}

/**
 * Point d'entrée — exécute par défaut l'exo 3 (mesures de performance).
 * Décommenter exo1a/exo1b/exo2a/exo2b pour les autres scénarios.
 * @return 0 en cas de succès.
 */
int main(void) {
    srand(time(NULL));
    //exo1a();
    //exo1b();
    //exo2a();
    //exo2b();
    exo3();
}