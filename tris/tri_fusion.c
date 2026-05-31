#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int VMAX = 1000000;

/**
 * Calcule l'indice du milieu d'un intervalle de longueur n.
 * @param n Longueur de l'intervalle.
 * @return La position centrale (division entière par 2).
 */
int indice_milieu(int n) {
    return n/2;
}

/*--------------------------ALGORITHMES DE TRI--------------------------*/

/**
 * Copie la plage [indInf, indSup] de `tab` au début de `tmp`.
 * @param tab Tableau source.
 * @param indInf Indice de début (inclus).
 * @param indSup Indice de fin (inclus).
 * @param tmp Tableau de destination.
 */
void copie(int *tab, int indInf, int indSup, int *tmp) {
    int j=0;
    for (int i=indInf; i<indSup+1; i++) {
        *(tmp+j) = *(tab+i);
        j++;
    }
}

/**
 * Fusionne deux sous-tableaux triés [indInf, indMil] et [indMil+1, indSup]
 * de `tab` en utilisant la technique des sentinelles (VMAX en fin de tampon).
 * @param tab Tableau dont les deux moitiés sont triées.
 * @param indInf Indice de début de la fusion.
 * @param indMil Indice de fin de la première moitié.
 * @param indSup Indice de fin de la seconde moitié.
 * @param tmp1 Tampon de travail pour la première moitié.
 * @param tmp2 Tampon de travail pour la seconde moitié.
 */
void fusion(int *tab, int indInf, int indMil, int indSup, int *tmp1, int *tmp2) {
    copie(tab, indInf, indMil, tmp1);
    copie(tab, indMil+1, indSup, tmp2);
    tmp1[indMil-indInf+1] = VMAX;
    tmp2[indSup-indMil] = VMAX;
    int i=0;
    int j=0;
    for (int k=indInf; k<=indSup; k++) {
        if (*(tmp1+i) < *(tmp2+j)) {
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
 * Trie un tableau par fusion (mergesort) — diviser pour régner récursif.
 * Complexité : O(n log n) dans tous les cas.
 * @param tab Tableau à trier.
 * @param indMin Borne inférieure de la plage à trier.
 * @param indSup Borne supérieure de la plage à trier.
 * @param tmp1 Tampon de travail (taille >= indSup-indMin+2).
 * @param tmp2 Tampon de travail (taille >= indSup-indMin+2).
 */
void tri_fusion(int *tab, int indMin, int indSup, int *tmp1, int *tmp2) {
    if (indMin<indSup) {
        int indMil = indice_milieu(indMin+indSup);
        tri_fusion(tab, indMin, indMil, tmp1, tmp2);
        tri_fusion(tab, indMil+1, indSup, tmp1, tmp2);
        fusion(tab, indMin, indMil, indSup, tmp1, tmp2);
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
    int *tmp1 = malloc(8 * sizeof(int));
    int *tmp2 = malloc(8 * sizeof(int));
    printf("Le tableau avant le tri : \n");
    print_tab(tab, 8);
    printf("\n");
    tri_fusion(tab, 0, 7, tmp1, tmp2);
    printf("Le tableau apres le tri : \n");
    print_tab(tab, 8);
}

/**
 * Exo 1.b — Saisie d'un tableau au clavier puis tri par fusion.
 */
void exo1b() {
    int n;
    printf("Merci d'indiquer une taille pour votre tableau.\n");
    scanf("%d", &n);
    int *tab = malloc(n * sizeof(int));
    int *tmp1 = malloc(n * sizeof(int));
    int *tmp2 = malloc(n * sizeof(int));
    printf("Merci d'indiquer les valeurs de votre tableau à la suite\n");
    for (int i=0; i<n; i++) {
        scanf("%d",tab+i);
    }
    printf("Le tableau que vous avez entre : \n");
    print_tab(tab, n);
    printf("\n");
    tri_fusion(tab, 0, n-1, tmp1, tmp2);
    printf("Le tableau trie : \n");
    print_tab(tab, n);
}

/**
 * Exo 2.a — Génère un tableau aléatoire puis le trie.
 */
void exo2a() {
    int n = rand() % 100 + 100;
    int *tab = random_tab(n);
    int *tmp1 = malloc(n * sizeof(int));
    int *tmp2 = malloc(n * sizeof(int));
    printf("Le tableau genere aleatoirement : \n");
    print_tab(tab, n);
    printf("\n");
    tri_fusion(tab, 0, n-1, tmp1, tmp2);
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
    int *tmp1 = malloc(n * sizeof(int));
    int *tmp2 = malloc(n * sizeof(int));
    for (int i=0; i<n; i++) {
        fscanf(f, "%d", tab+i);
    }
    printf("Le tableau cree a partir du fichier : \n");
    print_tab(tab, n);
    printf("\n");
    tri_fusion(tab, 0, n-1, tmp1, tmp2);
    printf("Le tableau trie : \n");
    print_tab(tab, n);
    free(tab);
    tab=NULL;
}

/**
 * Exo 3 — Mesures expérimentales : trie 40 tableaux aléatoires de tailles
 * croissantes (pas de 10000), et écrit les couples (n, durée) dans
 * `data/resultFusion.txt` pour exploitation gnuplot.
 */
void exo3() {
    FILE *f = fopen("../data/resultFusion.txt", "w");
    int n=0;
    double t;
    int *tab, *tmp1, *tmp2;
    int i;
    for (i=0; i<40; i++) {
        n=n+10000;
        tab = random_tab(n);
        tmp1 = malloc(n * sizeof(int));
        tmp2 = malloc(n * sizeof(int));
        clock_t start = clock();
        tri_fusion(tab,0, n-1, tmp1, tmp2);
        clock_t end = clock();
        t = (double)(end - start) / CLOCKS_PER_SEC;
        fprintf(f, "%d %f\n", n, t);
        free(tab); tab=NULL;
    }
    fclose(f);
    printf("Tris realises avec succes, resultats dans data/resultFusion.txt");
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