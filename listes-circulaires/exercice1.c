#include "structure.h"

/**
 * Compte le nombre d'occurrences d'une valeur dans une liste circulaire.
 * @param elt Valeur recherchée.
 * @param der Pointeur d'entrée sur la liste (typiquement la queue).
 * @return Le nombre d'occurrences de elt dans la liste.
 */
int nb_occ(int elt, ListeC der) {
    ListeC ll = der;
    int occ = 0;
    do {
        if (donnee(ll) == elt) {
            occ++;
        }
        ll = suivant(ll);
    } while (ll != der);
    return occ;
}

/**
 * Compte le nombre d'occurrences d'une valeur dans une ListeCTQ.
 * @param elt Valeur recherchée.
 * @param l Liste circulaire à tête/queue/taille.
 * @return Le nombre d'occurrences de elt dans la liste.
 */
int nb_occ_lctq(int elt, ListeCTQ l) {
    ListeC ll = tete(l);
    ListeC der = queue(l);
    int occ = 0;
    do {
        if (donnee(ll) == elt) {
            occ++;
        }
        ll = suivant(ll);
    } while (ll != der);
    return occ;
}