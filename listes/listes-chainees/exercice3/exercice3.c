#include "structure_exo3.h"

/**
 * Recherche l'adresse d'une cellule contenant la valeur elt dans une liste.
 * Une cellule étant déjà une adresse, on renvoie directement le pointeur.
 * @param l Liste à parcourir.
 * @param elt Valeur recherchée.
 * @return Le pointeur sur la cellule trouvée, NULL si absent.
 */
Liste search_elt(Liste l, int elt) {
    int trouve = 0;
    Liste res = NULL;
    while (!est_vide(l) && !trouve) {
        if (donnee(l) == elt) {
            trouve = 1;
            res = l;
        }
    }
    return res;
}

/**
 * Renvoie l'adresse d'insertion d'un nouvel élément dans une liste triée
 * (première cellule dont la donnée est >= elt).
 * @param l Liste triée.
 * @param elt Valeur à insérer.
 * @return L'adresse de la cellule de référence pour l'insertion.
 */
Liste adr_insert(Liste l, int elt) {
    while (!est_vide(l) && donnee(l) < elt) {
        l = suivant(l);
    }
    return l;
}

/**
 * Insère un élément en conservant l'ordre croissant de la liste triée.
 * @param l Liste triée.
 * @param elt Valeur à insérer.
 * @return La liste avec l'élément inséré au bon endroit.
 */
Liste inser_triee(Liste l, int elt) {
    if (est_vide(l)) {
        return inser_tete(l, elt);
    }
    Liste adr = adr_insert(l, elt);
    adr = inser_tete(adr, elt);
    return l;
}