#include "../structure.h"

/**
 * Renvoie l'élément au sommet du tas (la racine).
 * @param t Tas non vide.
 * @return La valeur au sommet (le maximum dans un max-heap).
 */
int sommet_tas(Tas t) {
    return t.tab[0];
}

/**
 * Insère un élément dans un tas et restaure la propriété de tas en remontant.
 * Version itérative (« percolation » vers le haut).
 * @param elt Valeur à insérer.
 * @param t Tas destination.
 * @return Le tas avec l'élément inséré à sa place.
 */
Tas inser_tas(int elt, Tas t) {
    int n = taille(t);
    if (n == 0) {
        t.tab[n] = elt;
        t.taille++;
    }
    else {
        int dp = donnee_ap(pere_noeud_ap(n, t), t);
        while (n>0 && elt>dp) {
            t.tab[n] = dp;
            n = pere_noeud_ap(n, t);
            dp = donnee_ap(pere_noeud_ap(n, t), t);
        }
        t.tab[n] = elt;
        t.taille++;
    }
    return t;
}

/**
 * Insère un élément dans un tas (version récursive de la percolation haute).
 * @param elt Valeur à insérer.
 * @param n Indice de la place candidate à comparer avec son père.
 * @param t Tas destination.
 * @return Le tas avec l'élément inséré à sa place.
 */
Tas rec_inser_tas(int elt, int n, Tas t) {
    if (n == 0) {
        t.tab[n] = elt;
        t.taille++;
        return t;
    }
    int dp = donnee_ap(pere_noeud_ap(n, t), t);
    if (elt <= dp) {
        t.tab[n] = elt;
        t.taille++;
        return t;
    }
    t.tab[n] = dp;
    n = pere_noeud_ap(n, t);
    return rec_inser_tas(elt, n, t);
}

/**
 * Supprime la racine du tas et restaure la propriété en faisant descendre
 * la dernière valeur. Version itérative.
 * @param t Tas non vide.
 * @return Le tas après suppression de la racine.
 */
Tas supp_tas(Tas t) {
    int r = 0;
    t.taille--;
    t.tab[r] = donnee_ap(taille(t), t);
    int elt = donnee_ap(r, t);
    int fmax;
    if (!est_vide_ap(t)) {
        int fg = fils_gauche_ap(r, t), fd;
        int echange = 1;
        while (est_exist_noeud_ap(fg, t) && echange) {
            fd = fils_droit_ap(r, t);
            fmax = fg;
            if (est_exist_noeud_ap(fd, t) && donnee_ap(fd, t) > donnee_ap(fg, t)) {
                fmax = fd;
            }
            if (elt > donnee_ap(fmax, t)) {
                echange = 0;
            }
            else {
                t.tab[r] = donnee_ap(fmax, t);
                r = fmax;
                fg = fils_gauche_ap(r, t);
            }
        }
        t.tab[r] = elt;
    }
    return t;
}

/**
 * Étape récursive de la suppression : fait descendre `elt` à partir de `r`.
 * @param elt Valeur à placer.
 * @param r Indice courant de la descente.
 * @param fg Indice du fils gauche de r.
 * @param t Tas en cours de restauration.
 * @return Le tas après descente complète.
 */
Tas rec_supp_tas_bis(int elt, int r, int fg, Tas t) {
    if (!est_exist_noeud_ap(fg, t)) {
        t.tab[r] = elt;
        return t;
    }
    int fmax = fg;
    int fd = fils_droit_ap(r, t);
    if (est_exist_noeud_ap(fd, t) && donnee_ap(fd, t) > donnee_ap(fg, t)) {
        fmax = fd;
    }
    if (elt >= donnee_ap(fmax, t)) {
        t.tab[r] = elt;
        return t;
    }
    t.tab[r] = donnee_ap(fmax, t);
    r = fmax;
    fg = fils_gauche_ap(r, t);
    return rec_supp_tas_bis(elt, r, fg, t);
}

/**
 * Supprime la racine du tas (version récursive).
 * @param t Tas non vide.
 * @return Le tas après suppression de la racine.
 */
Tas rec_supp_tas(Tas t) {
    t.taille--;
    int r = 0;
    t.tab[r] = donnee_ap(taille(t), t);
    int elt = donnee_ap(taille(t), t);
    if (!est_vide_ap(t)) {
        int fg = fils_gauche_ap(r, t);
        return rec_supp_tas_bis(elt, r, fg, t);
    }
    return t;
}

/**
 * Renvoie le maximum de deux entiers.
 * @param a Premier entier.
 * @param b Second entier.
 * @return Le plus grand des deux.
 */
int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

/**
 * Teste si un arbre parfait est un tas (version itérative bas → haut).
 * @param n Taille de l'arbre.
 * @param a Arbre parfait.
 * @return 1 si c'est un tas, 0 sinon.
 */
int est_tas_ver1(int n, ArbreParfait a) {
    if (n <= 1) {
        return 1;
    }
    n--;
    int r = 0;
    while (n > r && a.tab[n] < a.tab[pere_noeud_ap(n, a)]) {
        n--;
    }
    return n == r;
}

/**
 * Teste si un arbre parfait est un tas (version récursive bas → haut).
 * @param n Taille de l'arbre.
 * @param a Arbre parfait.
 * @return 1 si c'est un tas, 0 sinon.
 */
int rec_est_tas_ver1(int n, ArbreParfait a) {
    if (n <= 1) {
        return 1;
    }
    int nd = n-1;
    int p = pere_noeud_ap(nd, a);
    if (donnee_ap(nd, a) > donnee_ap(p, a)) {
        return 0;
    }
    return rec_est_tas_ver1(nd, a);
}

/**
 * Teste si un arbre parfait est un tas (version itérative haut → bas).
 * @param n Taille de l'arbre.
 * @param a Arbre parfait.
 * @return 1 si c'est un tas, 0 sinon.
 */
int est_tas_ver2(int n, ArbreParfait a) {
    if (n <= 1) {
        return 1;
    }
    int r = 0;
    int fg = fils_gauche_ap(r, a);
    int fd = fils_droit_ap(r, a);
    while (est_exist_noeud_ap(fg, a) && est_exist_noeud_ap(fd, a) && donnee_ap(r, a) > max(donnee_ap(fg, a), donnee_ap(fd, a))) {
        r++;
        fg = fils_gauche_ap(r, a);
        fd = fils_droit_ap(r, a);
    }
    if (est_exist_noeud_ap(fg, a) && est_exist_noeud_ap(fd, a)) {
        return 0;
    }
    if (est_exist_noeud_ap(fg, a)) {
        return a.tab[fg] <= donnee_ap(r, a);
    }
    return 1;
}

/**
 * Teste si un arbre parfait est un tas (version récursive haut → bas).
 * @param n Taille de l'arbre (non utilisé directement, propagé).
 * @param r Indice du nœud courant.
 * @param a Arbre parfait.
 * @return 1 si c'est un tas à partir de r, 0 sinon.
 */
int rec_est_tas_ver2(int n, int r, ArbreParfait a) {
    int fg = fils_gauche_ap(r, a);
    if (!est_exist_noeud_ap(r, a) || !est_exist_noeud_ap(fg, a)) {
        return 1;
    }
    int fd = fils_droit_ap(r, a);
    if (est_exist_noeud_ap(fd, a)) {
        return donnee_ap(r, a) >= max(donnee_ap(fg, a), donnee_ap(fd, a))
            && rec_est_tas_ver2(n, fg, a) && rec_est_tas_ver2(n, fd, a);
    }
    return donnee_ap(r, a) >= donnee_ap(fg, a);
}

/**
 * Construit un tas à partir d'un tableau d'entiers (insertions successives).
 * @param n Taille du tableau.
 * @param tab Tableau source.
 * @return Le tas obtenu.
 */
Tas convert_tab_to_tas(int n, int *tab) {
    ArbreParfait tas;
    tas = alloc_mem_ap(tas, n);
    tas = init_ap(tas);
    for (int i=0; i<n; i++) {
        tas = inser_tas(tab[i], tas);
    }
    return tas;
}

/**
 * Construit un tas à partir d'un tableau (version récursive).
 * @param n Indice du prochain élément à insérer (compte à rebours).
 * @param tas Tas en cours de construction.
 * @param tab Tableau source.
 * @return Le tas final.
 */
Tas rec_convert_tab_to_tas(int n, ArbreParfait tas, int *tab) {
    if (n == 0) {
        return tas;
    }
    tas = rec_inser_tas(tab[n-1], taille(tas), tas);
    return rec_convert_tab_to_tas(n-1, tas, tab);
}

/**
 * Trie un tableau par la méthode du tri par tas (heapsort) :
 * construction du tas puis extractions successives du maximum.
 * Complexité : O(n log n) en moyenne et pire cas.
 * @param n Taille du tableau.
 * @param tab Tableau à trier en place.
 */
void tri_par_tas(int n, int *tab) {
    Tas tas;
    tas = alloc_mem_ap(tas, n);
    tas = init_ap(tas);
    for (int i=0; i<n; i++) {
        tas = inser_tas(tab[i], tas);
    }
    int e;
    for (int j=n-1; j>-1; j--) {
        e = sommet_tas(tas);
        tas = supp_tas(tas);
        tab[j] = e;
    }
    free(tas.tab);
}