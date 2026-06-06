#include "structure_exo3.h"

/**
 * Renvoie la donnée portée par une cellule.
 * @param l Cellule de liste.
 * @return L'entier stocké dans la cellule.
 */
int donnee(Liste l) {
    return l->donnee;
}

/**
 * Renvoie la cellule suivante.
 * @param l Cellule courante.
 * @return Le successeur (NULL si fin de liste).
 */
Liste suivant(Liste l) {
    return l->suivant;
}

/**
 * Teste si une liste est vide.
 * @param l Liste à tester.
 * @return 1 si vide, 0 sinon.
 */
int est_vide(Liste l) {
    return l == NULL;
}

/**
 * Initialise une liste vide.
 * @return Une liste vide (NULL).
 */
Liste init_l(void) {
    return NULL;
}

/**
 * Alloue une cellule de liste non initialisée.
 * @return Pointeur sur la cellule allouée.
 */
Liste alloc_mem(void) {
    return malloc(sizeof(struct cellule));
}

/**
 * Insère un élément en tête de liste et renvoie la nouvelle tête.
 * @param l Liste destination.
 * @param elt Valeur à insérer.
 * @return La nouvelle tête de liste.
 */
Liste inser_tete(Liste l, int elt) {
    Liste cel = alloc_mem();
    cel->donnee = elt;
    cel->suivant = l;
    l = cel;
    return l;
}