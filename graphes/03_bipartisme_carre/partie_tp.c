#include <stdio.h>
#include <stdlib.h>

#include "../include/prototype_td4.h"
#include "../include/prototype_td3.h"

/**
 * (s, t) appartient à G² ssi, il existe un u tq (s, u) appartient à G et (u, t) appartient à G
 * @param g La matrice adjacence
 * @return g² la matrice adjacence du carré du graphe
 */
MatAdjacence get_carre_ma(MatAdjacence g) {
    int n = g.nbSom;
    MatAdjacence g2 = alloc_sma_f(n);
    int u;
    for (int s=0; s<n; s++) {
        for (int t=0; t<n; t++) {
            u = 0;
            while (u<n && g.mat[s][u]*g.mat[u][t] != 1) {
                u++;
            }
            if (u<n) {
                g2.mat[s][t] = 1;
            }
            else {
                g2.mat[s][t] = 0;
            }
        }
    }
    return g2;
}

/**
 * La même chose, mais avec la liste d'adjacence
 * @param g La liste d'adjacence initial
 * @return La liste d'adjacence du graphe au carré
 */
ListeAdjacence get_carre_la(ListeAdjacence g) {
    ListeAdjacence g2;
    g2.tabAdj = malloc(g.nbSom*sizeof(struct cel));
    g2.nbSom = g.nbSom;
    Liste lu;
    Liste ls;
    int u;
    int t;
    for (int s=0; s<g.nbSom; s++) {
        Liste l2 = init_l();
        ls = g.tabAdj[s];
        while (!est_vide(ls)) {
            u = donnee(ls);
            ls = suivant(ls);
            lu = g.tabAdj[u];
            while (!est_vide(lu)) {
                t = donnee(lu);
                l2 = inser_trie(t, l2);
                lu  = suivant(lu);
            }
        }
        g2.tabAdj[s] = l2;
    }
    return g2;
}

/**
 * On veut verifier si un graphe est Biparti.
 * On marque les successeurs d'un sommet d'un niveau+1 que le sien.
 * On les marque via un parcours en largeur.
 * À la fin les sommets marqué pair et impair forment deux groupes.
 * @param g Le graphe
 * @param type Le type du graphe
 * @return Le tableau de marquage
 */
int* marquage_pl(void* g, TypeGraphe type) {
    int n = nb_som_gen(g, type);
    int* visite = alloc_tab(n);
    for (int i=0; i<n; i++) {
        visite[i] = 0;
    }
    int* marquage = alloc_tab(n);
    int nbSomVisite = 0;
    int s = 0;
    marquage[s] = 0;
    int u;
    // Parcours en largeur à partir du sommet
    File f = init_l();
    f = inser_queue(s, f);
    while (!est_vide(f) && nbSomVisite < n) {
        u = donnee(f);
        f = supp_tete(f);
        if (!visite[u]) {
            nbSomVisite++;
            visite[u] = 1;
            int* succ = get_succ_by_type(u, type, g);
            for (int i=1; i<succ[0]+1; i++) {
                if (!visite[i]) {
                    f = inser_queue(succ[i], f);
                    marquage[succ[i]] = marquage[u]+1;
                }
            }
        }
    }
    while (!est_vide(f)) {
        f = supp_tete(f);
    }
    visite = lib_tab_f(visite);
    free(visite);
    return marquage;
}

/**
 * On a notre tableau de marquage.
 * On regarde pour chaque sommet, quel est son groupe.
 * Pair → groupe 1
 * Impair → groupe 2
 * @param n Le nombre de sommet
 * @param marquage Le tableau des marquages indicé par le sommet
 * @param s1 Liste des sommets du groupe 1
 * @param s2 Liste des sommets du groupe 2
 */
void partition(int n, int* marquage, Liste* s1, Liste* s2) {
    *s1 = init_l();
    *s2 = init_l();
    for (int i=0; i<n; i++) {
        if (marquage[i]%2 == 0) {   // C'est pair
            *s1 = inser_tete(i, *s1);
        }
        else {
            *s2 = inser_tete(i, *s2);  // C'est impair
        }
    }
}

/**
 * On a nos deux groupes de sommets.
 * On veut vérifier qu'ils n'ont des relations qu'en dehors de leur groupe
 * @param group La liste de sommet
 * @param type Le type du graphe
 * @param g Le graphe
 * @return Un booléen, soit il y a un lien soit il n'y en a pas.
 */
int est_liaison(Liste group, TypeGraphe type, void* g) {
    int estLien = 0;
    int* succ;
    while (!est_vide(group) && !estLien) {
        succ = get_succ_by_type(donnee(group), type, g);
        int i = 1;
        while (!estLien && i<succ[0]+1) {
            if (contain(succ[i], group)) {
                estLien = 1;
            }
            i++;
        }
        group = suivant(group);
    }
    return estLien;
}

/**
 * Fonction final regroupant le déroulement des autres.
 * Etape 1 : On marque les sommets via un parcours en largeur.
 * Etape 2 : On sépare nos deux groupes de sommets pair et impair.
 * Etape 3 : On vérifie qu'il n'y ai pas de lien entre un groupe et lui-même.
 * @param g Le graphe
 * @param type Le type du graphe
 * @return Un booléen, soit il est biparti, soit il ne l'est pas.
 */
int est_biparti(void* g, TypeGraphe type) {
    int n = nb_som_gen(g, type);
    int* marquage = marquage_pl(g, type);
    Liste s1, s2;
    partition(n, marquage, &s1, &s2);
    int est_biparti = !est_liaison(s1, type, g) && !est_liaison(s2, type, g);
    return est_biparti;
}