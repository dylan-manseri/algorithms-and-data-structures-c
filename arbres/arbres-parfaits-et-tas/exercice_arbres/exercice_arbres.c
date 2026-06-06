#include "../structure.h"

/**
 * Alloue dynamiquement le tableau sous-jacent d'un arbre parfait.
 * @param a Arbre parfait à initialiser.
 * @param tMax Capacité maximale souhaitée.
 * @return L'arbre avec son tableau alloué et tailleMax fixé.
 */
ArbreParfait alloc_mem_ap(ArbreParfait a, int tMax) {
    a.tailleMax = tMax;
    a.tab = malloc(tMax * sizeof(ArbreParfait));
    return a;
}

/**
 * Initialise un arbre parfait à vide (taille à 0).
 * @param a Arbre parfait dont la mémoire a déjà été allouée.
 * @return L'arbre marqué comme vide.
 */
ArbreParfait init_ap(ArbreParfait a) {
    a.taille = 0;
    return a;
}

/**
 * Teste si un arbre parfait est vide.
 * @param a Arbre parfait.
 * @return 1 si aucun nœud, 0 sinon.
 */
int est_vide_ap(ArbreParfait a) {
    return a.taille == 0;
}

/**
 * Teste si l'arbre a atteint sa capacité maximale.
 * @param a Arbre parfait.
 * @return 1 si plein, 0 sinon.
 */
int est_plein_ap(ArbreParfait a) {
    return a.taille == a.tailleMax;
}

/**
 * Teste l'existence d'un nœud à un indice donné.
 * @param nd Indice du nœud.
 * @param a Arbre parfait.
 * @return 1 si nd correspond à un nœud présent, 0 sinon.
 */
int est_exist_noeud_ap(int nd, ArbreParfait a) {
    return nd < a.taille;
}

/**
 * Renvoie la donnée stockée au nœud nd.
 * @param nd Indice du nœud.
 * @param a Arbre parfait.
 * @return La valeur entière au nœud nd.
 */
int donnee_ap(int nd, ArbreParfait a) {
    return a.tab[nd];
}

/**
 * Calcule l'indice du père d'un nœud (arithmétique : (nd-1)/2).
 * @param nd Indice du nœud.
 * @param a Arbre parfait (non utilisé, présent pour signature uniforme).
 * @return L'indice du père.
 */
int pere_noeud_ap(int nd, ArbreParfait a) {
    return (nd-1)/2;
}

/**
 * Calcule l'indice du fils gauche d'un nœud (arithmétique : 2*nd+1).
 * @param nd Indice du nœud.
 * @param a Arbre parfait (non utilisé, présent pour signature uniforme).
 * @return L'indice du fils gauche.
 */
int fils_gauche_ap(int nd, ArbreParfait a) {
    return 2*nd+1;
}

/**
 * Calcule l'indice du fils droit d'un nœud (arithmétique : 2*nd+2).
 * @param nd Indice du nœud.
 * @param a Arbre parfait (non utilisé, présent pour signature uniforme).
 * @return L'indice du fils droit.
 */
int fils_droit_ap(int nd, ArbreParfait a) {
    return 2*nd+2;
}

/**
 * Teste si un nœud est une feuille (sans fils gauche ni fils droit).
 * @param nd Indice du nœud.
 * @param a Arbre parfait.
 * @return 1 si feuille, 0 sinon.
 */
int est_feuille(int nd, ArbreParfait a) {
    return (est_exist_noeud_ap(fils_droit_ap(nd, a), a) && est_exist_noeud_ap(fils_gauche_ap(nd, a), a));
}

/**
 * Parcours infixe (gauche, racine, droite) d'un arbre parfait.
 * @param racine Indice du nœud racine du sous-arbre.
 * @param a Arbre parfait.
 */
void parcours_infixe_ap(int racine, ArbreParfait a) {
    if (est_exist_noeud_ap(racine, a)) {
        parcours_infixe_ap(fils_gauche_ap(racine, a), a);
        // traiter
        parcours_infixe_ap(fils_droit_ap(racine, a), a);
    }
}

/**
 * Parcours préfixe (racine, gauche, droite) d'un arbre parfait.
 * @param racine Indice du nœud racine du sous-arbre.
 * @param a Arbre parfait.
 */
void parcours_prefixe_ap(int racine, ArbreParfait a) {
    if (est_exist_noeud_ap(racine, a)) {
        // traiter
        parcours_prefixe_ap(fils_gauche_ap(racine, a), a);
        parcours_prefixe_ap(fils_droit_ap(racine, a), a);
    }
}

/**
 * Parcours postfixe (gauche, droite, racine) d'un arbre parfait.
 * @param racine Indice du nœud racine du sous-arbre.
 * @param a Arbre parfait.
 */
void parcours_postfixe_ap(int racine, ArbreParfait a) {
    if (est_exist_noeud_ap(racine, a)) {
        parcours_postfixe_ap(fils_gauche_ap(racine, a), a);
        parcours_postfixe_ap(fils_droit_ap(racine, a), a);
        // traiter
    }
}

/**
 * Parcours en largeur (BFS) trivial grâce à la représentation tabulaire :
 * l'ordre des indices est l'ordre de parcours en largeur.
 * @param racine Indice de départ (généralement 0).
 * @param a Arbre parfait.
 */
void parcours_largeur_ap(int racine, ArbreParfait a) {
    int nbNoeuds = taille(a);
    for (int i=0; i<nbNoeuds; i++) {
        // traiter
    }
}

/**
 * Affiche un arbre parfait niveau par niveau (un saut de ligne par niveau).
 * Le nombre de nœuds par niveau double à chaque étape.
 * @param a Arbre parfait à afficher.
 * @param n Nombre total de nœuds (non utilisé, conservé pour compatibilité).
 */
void parcours_largeur_par_niveau(ArbreParfait a, int n) {
    int noeud = 0;
    int nbNoeudNiv = 1;
    int compteur;
    while (est_exist_noeud_ap(noeud, a)) {
        compteur = 0;
        while (est_exist_noeud_ap(noeud, a) && (compteur < nbNoeudNiv)) {
            printf("%d ", donnee_ap(noeud, a));
            noeud++;
            compteur++;
        }
        printf("\n");
        nbNoeudNiv *= 2;
    }
}

/**
 * Affiche un arbre parfait PLEIN niveau par niveau.
 * Hypothèse : n = 2^h - 1 (arbre complet sans trou).
 * @param a Arbre parfait plein.
 */
void parcours_arbre_parfait_niveau_plein(ArbreParfait a) {
    int n = taille(a);
    int h = (int) round(log(n+1)/log(2));  // h = log2(n+1)
    int hM = h-1;                          // on s'arrête à l'avant-dernier niveau
    int nbNiveau = 1;                      // la racine occupe le premier niveau
    int noeud = 0;
    for (int i=0; i<hM; i++) {
        for (int k=0; k<nbNiveau; k++) {
            printf("%d ", donnee_ap(noeud, a));
            noeud++;
        }
        nbNiveau *= 2;
        printf("\n");
    }
    for (; noeud<n; noeud++) {
        printf("%d ", donnee_ap(noeud, a));
    }
    printf("\n");
}

/**
 * Insère un élément à la fin de l'arbre (premier indice libre) si non plein.
 * @param elt Valeur à insérer.
 * @param a Arbre parfait destination.
 * @return L'arbre avec l'élément ajouté (inchangé si plein).
 */
ArbreParfait inser_elt_ap(int elt, ArbreParfait a) {
    if (!est_plein_ap(a)) {
        a.tab[taille(a)] = elt;
        a.taille++;
    }
    return a;
}

/**
 * Construit interactivement un arbre parfait à partir des saisies utilisateur.
 * Demande la taille puis chaque valeur sur l'entrée standard.
 * @return L'arbre parfait construit.
 */
ArbreParfait const_ap(void) {
    ArbreParfait a;
    int tMax = 100, t;
    printf("Bienvenue dans l'algorithme de creation d'arbre parfait.\n");
    printf("Pour commencer, indiquez la taille de l'arbre.\n");
    scanf("%d", &t);
    a = alloc_mem_ap(a, tMax);
    a = init_ap(a);
    printf("Ecoute en cours, indiquez à la suite les elements de l'arbre.\n");
    int donnee;
    for (int i=0; i<t; i++) {
        scanf("%d", &donnee);
        a = inser_elt_ap(donnee, a);
    }
    return a;
}