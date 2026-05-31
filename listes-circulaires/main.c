#include "structure.h"

/**
 * Démonstration : construit deux listes circulaires (simple et tête/queue),
 * affiche leur contenu et le nombre d'occurrences d'une valeur cherchée.
 * @return 0 en cas de succès.
 */
int main(void) {
    printf("EXERCICE 1 (circulaire) \n");
    ListeC l = init_l();
    l = inser_vide_lc(6);
    l = inser_queue(5, l);
    l = inser_queue(8, l);
    l = inser_queue(1, l);
    l = inser_queue(5, l);
    print_liste(l);
    printf("\nNombre d occurrence : %d\n", nb_occ(5, l));

    printf("EXERCICE 1 (circulaire tete queue)\n");
    ListeCTQ l1 = init_lctq();
    inser_vide_lctq(9, &l1);
    inser_queue_lctq(3, &l1);
    inser_queue_lctq(9, &l1);
    inser_queue_lctq(9, &l1);
    inser_queue_lctq(9, &l1);
    print_liste_ctq(l1);
    printf("\nNombre d occurrence : %d\n", nb_occ_lctq(9, l1));
}