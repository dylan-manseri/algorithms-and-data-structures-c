#include "structure.h"

/**
 * Renvoie la cellule suivante d'une pile.
 * @param p Cellule courante.
 * @return Le successeur (NULL si fond de pile).
 */
Pile suivant(Pile p) {
    return p->suivant;
}

/**
 * Initialise une pile vide.
 * @return Une pile vide (NULL).
 */
Pile init_p(void) {
    return NULL;
}

/**
 * Teste si une pile est vide.
 * @param p Pile à tester.
 * @return 1 si vide, 0 sinon.
 */
int est_vide_p(Pile p) {
    return p == NULL;
}

/**
 * Alloue dynamiquement une cellule de pile non initialisée.
 * @return Pointeur sur la cellule allouée.
 */
Pile alloc_mem_pile(void) {
    Pile p = malloc(sizeof(struct cel));
    return p;
}

/**
 * Renvoie la donnée au sommet de la pile (sans dépiler).
 * @param p Pile non vide.
 * @return Le pointeur générique stocké au sommet.
 */
void* sommet_p(Pile p) {
    return p->donnee;
}

/**
 * Empile une nouvelle donnée au sommet de la pile.
 * @param donnee Donnée générique à empiler.
 * @param p Pile destination.
 * @return Le nouveau sommet (la cellule fraîchement allouée).
 */
Pile empiler(void* donnee, Pile p) {
    Pile cel = alloc_mem_pile();
    cel->donnee = donnee;
    cel->suivant = p;
    p = cel;
    return p;
}

/**
 * Retire l'élément au sommet de la pile et libère la cellule correspondante.
 * Sans effet sur pile vide.
 * @param p Pile à modifier.
 * @return Le nouveau sommet après dépilage.
 */
Pile depiler(Pile p) {
    if (est_vide_p(p)) {
        return p;
    }
    Pile tmp = p;
    p = suivant(p);
    free(tmp);
    return p;
}