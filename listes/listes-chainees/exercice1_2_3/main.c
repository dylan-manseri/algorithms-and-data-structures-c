#include "structure.h"

/**
 * Démonstration : décomposition d'entiers en facteurs premiers, conversion
 * d'un tableau d'entiers en TabLDFP, intersection de décompositions et
 * calcul du PGCD d'un tableau d'entiers.
 * @return 0 en cas de succès.
 */
int main(void) {
    printf("QUESTION 2)\n");
    Liste l = create_liste();
    l = decomposition(210, l);
    print_liste(l);

    printf("\nQUESTION 3)\n");
    int tab[4] = {40, 15, 13, 210};
    TabLDFP *l2 = convert_tab_to_liste(tab, 4);
    print_tab_ldfp(l2, 4);

    printf("\nQUESTION 5)\n");
    Liste l3 = create_liste(); Liste l4 = create_liste();
    l3 = decomposition(6, l3);
    l4 = decomposition(30, l4);
    Liste l5 = intersection(l3, l4);
    print_liste(l5);

    printf("\nQUESTION 6)\n");
    int tab1[3] = {12, 18, 30};
    int pgcdV = pgcd(tab1, 3);
    printf("%d", pgcdV);
}