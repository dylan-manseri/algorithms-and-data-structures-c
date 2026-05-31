#include "structure.h"

/**
 * Renvoie la cellule suivante d'une liste circulaire.
 * @param l Cellule courante.
 * @return Le successeur de l (la liste étant circulaire, jamais NULL).
 */
ListeC suivant(ListeC l) {
    return l->suivant;
}

/**
 * Renvoie la donnée stockée dans une cellule.
 * @param der Cellule.
 * @return La valeur entière portée par la cellule.
 */
int donnee(ListeC der) {
    return der->elt;
}

/**
 * Initialise une liste circulaire vide.
 * @return Une liste vide (NULL).
 */
ListeC init_l(void) {
    return NULL;
}

/**
 * Alloue dynamiquement une cellule et y stocke la valeur passée.
 * Termine le programme en cas d'échec d'allocation.
 * @param elt Valeur à stocker dans la cellule.
 * @return Pointeur vers la cellule nouvellement allouée.
 */
ListeC alloc_mem(int elt) {
    ListeC cel = malloc(sizeof(struct cel));
    if (cel == NULL) {
        printf("erreur d'allocation");
        exit(1);
    }
    cel->elt = elt;
    return cel;
}

/**
 * Crée une liste circulaire à un seul élément (cellule pointant sur elle-même).
 * @param elt Valeur à insérer.
 * @return La liste circulaire à une cellule.
 */
ListeC inser_vide_lc(int elt) {
    ListeC cel = alloc_mem(elt);
    cel->suivant = cel;
    return cel;
}

/**
 * Insère un élément en tête de liste, juste après le pointeur de fin (der).
 * @param elt Valeur à insérer.
 * @param der Pointeur sur la dernière cellule (entrée de la liste).
 * @return Le même pointeur de fin (la tête a changé, pas la queue).
 */
ListeC inser_tete(int elt, ListeC der) {
    ListeC cel = alloc_mem(elt);
    cel->suivant = suivant(der);
    der->suivant = cel;
    return der;
}

/**
 * Insère un élément en queue de liste et met à jour le pointeur de fin.
 * @param elt Valeur à insérer.
 * @param der Pointeur sur la dernière cellule.
 * @return Le nouveau pointeur de fin (la cellule fraîchement insérée).
 */
ListeC inser_queue(int elt, ListeC der) {
    ListeC cel = alloc_mem(elt);
    cel->suivant = suivant(der);
    der->suivant = cel;
    der = cel;
    return der;
}

/**
 * Affiche les valeurs d'une liste circulaire entre barres verticales.
 * @param l Pointeur d'entrée (typiquement la queue) sur la liste à afficher.
 */
void print_liste(ListeC l) {
    ListeC ll = l;
    do {
        printf("| %d ", donnee(ll));
        ll = suivant(ll);
    } while (ll != l);
    printf("|");
}