#include "structure_exo3.h"

/**
 * Affiche une liste sous la forme `| v1 | v2 | ... |`.
 * @param l Liste à afficher.
 */
static void print_liste(Liste l) {
    printf("| ");
    while (!est_vide(l)) {
        printf("%d | ", donnee(l));
        l = suivant(l);
    }
    printf("\n");
}

/**
 * Démonstration : crée une liste vide et insère des valeurs dans l'ordre
 * croissant via inser_triee, puis affiche le résultat.
 * @return 0 en cas de succès.
 */
int main(void) {
    printf("EXERCICE 3 — Insertion triée\n");
    Liste l = init_l();
    l = inser_triee(l, 4);
    l = inser_triee(l, 1);
    l = inser_triee(l, 7);
    l = inser_triee(l, 3);
    print_liste(l);
}