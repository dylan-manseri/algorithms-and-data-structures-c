#include "structure.h"

/**
 * Extrait le caractère opérateur d'un DNoeud.
 * @param dnoeud Union DNoeud (tagué OPERATEUR par convention).
 * @return Le caractère opérateur.
 */
char operateur(DNoeud dnoeud) {
    return dnoeud.operateur;
}

/**
 * Extrait la valeur opérande d'un DNoeud.
 * @param dnoeud Union DNoeud (tagué OPERANDE par convention).
 * @return La valeur réelle de l'opérande.
 */
double operande(DNoeud dnoeud) {
    return dnoeud.operande;
}

/**
 * Renvoie le DNoeud d'un élément d'arbre.
 * @param elt Élément complet (tag + valeur).
 * @return La partie « valeur » de l'élément.
 */
DNoeud d_noeud(TElementA elt) {
    return elt.dNoeud;
}

/**
 * Renvoie le fils gauche d'un nœud d'arbre d'expression.
 * @param a Nœud courant.
 * @return Le pointeur sur le fils gauche (NULL si absent).
 */
ArbreExp fils_gauche(ArbreExp a) {
    return a->filsGauche;
}

/**
 * Renvoie le fils droit d'un nœud d'arbre d'expression.
 * @param a Nœud courant.
 * @return Le pointeur sur le fils droit (NULL si absent).
 */
ArbreExp fils_droit(ArbreExp a) {
    return a->filsDroit;
}

/**
 * Renvoie la donnée portée par un nœud.
 * @param a Nœud.
 * @return L'élément (tag + valeur) du nœud.
 */
TElementA donnee_a(ArbreExp a) {
    return a->donnee;
}

/**
 * Teste si un arbre d'expression est vide.
 * @param ae Arbre à tester.
 * @return 1 si vide, 0 sinon.
 */
int est_vide_a(ArbreExp ae) {
    return ae == NULL;
}

/**
 * Teste si un nœud est une feuille (sans fils).
 * @param ae Nœud à tester.
 * @return 1 si feuille, 0 sinon.
 */
int est_feuille(ArbreExp ae) {
    return est_vide_a(fils_droit(ae)) && est_vide_a(fils_gauche(ae));
}

/**
 * Crée un nœud feuille portant la valeur donnée.
 * @param a Élément (généralement une opérande).
 * @return Le pointeur sur la feuille allouée.
 */
ArbreExp create_feuille(TElementA a) {
    ArbreExp ae = malloc(sizeof(struct noeud));
    ae->donnee = a;
    ae->filsDroit = NULL;
    ae->filsGauche = NULL;
    return ae;
}

/**
 * Crée un nœud interne d'arbre d'expression (opérateur + deux sous-arbres).
 * @param elt Élément du nœud (généralement un opérateur).
 * @param fg Sous-arbre gauche.
 * @param fd Sous-arbre droit.
 * @return Le pointeur sur le nœud alloué.
 */
ArbreExp create_noeud(TElementA elt, ArbreExp fg, ArbreExp fd) {
    ArbreExp ae = malloc(sizeof(struct noeud));
    ae->donnee = elt;
    ae->filsGauche = fg;
    ae->filsDroit = fd;
    return ae;
}