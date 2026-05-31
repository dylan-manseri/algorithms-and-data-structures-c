#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Échange en place les valeurs des indices indice1 et indice2 du tableau.
 * @param indice1 Premier indice.
 * @param indice2 Second indice.
 * @param tab Tableau d'entiers.
 */
void permutation(int indice1, int indice2, int *tab) {
    int tmp = *(tab+indice1);
    *(tab+indice1) = *(tab+indice2);
    *(tab+indice2) = tmp;
}

/**
 * Partition de Lomuto/Hoare (version manuelle, double curseur).
 * Place le pivot (premier élément) à sa position définitive dans la plage.
 * @param ind_inf Borne inférieure de la plage.
 * @param ind_sup Borne supérieure de la plage.
 * @param tab Tableau à partitionner.
 * @return L'indice définitif du pivot après partition.
 */
int partitionner(int ind_inf, int ind_sup, int *tab) {
    int indPivot = ind_inf;
    int pivot = *(tab+indPivot);
    int l=ind_inf+1;
    int k=ind_sup;
    while (l<=k) {
        if (*(tab+l)<=pivot) {
            l++;
        }
        else {
            if (*(tab+k)>pivot) {
                k--;
            }
            else {
                if (l<k) {
                    permutation(l, k, tab);
                    l++;
                    k--;
                }
            }
        }
    }
    if (indPivot != k) {
        permutation(indPivot, k, tab);
    }
    return k;
}

/**
 * Variante de partition à deux boucles imbriquées.
 * @param ind_inf Borne inférieure de la plage.
 * @param ind_sup Borne supérieure de la plage.
 * @param tab Tableau à partitionner.
 * @return L'indice définitif du pivot après partition.
 */
int partitionner2(int ind_inf, int ind_sup, int *tab) {
    int ind_pivot=ind_inf;
    int pivot = *(tab+ind_pivot);
    int l = ind_inf+1;
    int k = ind_sup;
    while (l<=k) {
        while ((l<=k) && (*(tab+l)<=pivot)) {
            l++;
        }
        while ((l<=k) && (*(tab+1)<pivot)) {
            k--;
        }
        if (l<k) {
            l++;
            k--;
        }
    }
    if (ind_pivot!=k) {
        permutation(ind_pivot,k,tab);
    }
    return k;
}

/**
 * Trie un tableau par la méthode du tri rapide (quicksort) — diviser pour régner.
 * Complexité : O(n log n) en moyenne, O(n²) au pire cas (pivots déséquilibrés).
 * @param ind_inf Borne inférieure de la plage à trier.
 * @param ind_sup Borne supérieure de la plage à trier.
 * @param tab Tableau à trier.
 */
void tri_rapide(int ind_inf, int ind_sup, int *tab) {
    if (ind_inf<ind_sup) {
        int indPivot = partitionner2(ind_inf, ind_sup, tab);
        tri_rapide(ind_inf, indPivot-1, tab);
        tri_rapide(indPivot+1, ind_sup, tab);
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
 * Affiche les n premières valeurs d'un tableau entre accolades.
 * @param tab Tableau d'entiers.
 * @param n Nombre de valeurs à afficher.
 */
void print_tab(int *tab, int n) {
    printf("{ ");
    for (int i=0; i<n; i++) {
        printf("%d ", *(tab+i));
    }
    printf("}\n");
}

/*--------------------------EXERCICES--------------------------*/

/**
 * Exo 1.a — Trie un petit tableau codé en dur, pour valider l'algorithme.
 */
void exo1a(){
    int tab[8] = {7,8,3,5,9,1,1,8};
    printf("Le tableau avant le tri : \n");
    print_tab(tab, 8);
    printf("\n");
    tri_rapide(0,7,tab);
    printf("Le tableau apres le tri : \n");
    print_tab(tab, 8);
}

/**
 * Exo 1.b — Saisie d'un tableau au clavier puis tri rapide.
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
    tri_rapide(0,n-1,tab);
    printf("Le tableau trie : \n");
    print_tab(tab, n);
}

/**
 * Exo 2.a — Génère un tableau aléatoire puis le trie.
 */
void exo2a() {
    int n = rand() % 100 + 100;
    int *tab = random_tab(n);
    printf("Le tableau genere aleatoirement : \n");
    print_tab(tab, n);
    printf("\n");
    tri_rapide(0,n-1,tab);
    printf("Le tableau trie : \n");
    print_tab(tab, n);
    free(tab);
    tab=NULL;
}

/**
 * Exo 2.b — Charge un tableau depuis `data/donnees.txt` puis le trie.
 */
void exo2b() {
    int n;
    FILE *f = fopen("../data/donnees.txt", "r");
    fscanf(f, "%d", &n);
    int *tab = malloc(n * sizeof(int));
    for (int i=0; i<n; i++) {
        fscanf(f, "%d", tab+i);
    }
    printf("Le tableau cree a partir du fichier : \n");
    print_tab(tab, n);
    printf("\n");
    tri_rapide(0,n-1,tab);
    printf("Le tableau trie : \n");
    print_tab(tab, n);
    free(tab);
    tab=NULL;
}

/**
 * Exo 3 — Mesures expérimentales : trie 40 tableaux aléatoires de tailles
 * croissantes (pas de 10000), et écrit les couples (n, durée) dans
 * `data/resultRapide.txt` pour exploitation gnuplot.
 */
void exo3() {
    FILE *f = fopen("../data/resultRapide.txt", "w");
    int n=0;
    double t;
    int *tab;
    int i;
    for (i=0; i<40; i++) {
        n=n+10000;
        tab = random_tab(n);
        clock_t start = clock();
        tri_rapide(0,n-1,tab);
        clock_t end = clock();
        t = (double)(end - start) / CLOCKS_PER_SEC;
        fprintf(f, "%d %f\n", n, t);
    }
    free(tab); tab=NULL;
    fclose(f);
    printf("Tris realises avec succes, resultats dans data/resultRapide.txt");
}

/**
 * Point d'entrée — exécute par défaut l'exo 3 (mesures de performance).
 * Décommenter exo1a/exo1b/exo2a/exo2b pour les autres scénarios.
 */
void main() {
    srand(time(NULL));
    //exo1a();
    //exo1b();
    //exo2a();
    //exo2b();
    exo3();
}