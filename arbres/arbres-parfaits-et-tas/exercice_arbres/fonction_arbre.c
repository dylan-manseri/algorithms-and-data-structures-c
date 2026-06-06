#include "../structure.h"

/**
 * Renvoie la taille (nombre de nœuds présents) d'un arbre parfait.
 * @param a Arbre parfait.
 * @return Le nombre de nœuds actuellement insérés.
 */
int taille(ArbreParfait a) {
    return a.taille;
}

/**
 * Renvoie la capacité maximale d'un arbre parfait.
 * @param a Arbre parfait.
 * @return La taille maximale allouée pour le tableau sous-jacent.
 */
int taille_max(ArbreParfait a) {
    return a.tailleMax;
}