#include "../structure.h"

/**
 * Démonstration : insère plusieurs entiers dans un tas, supprime la racine,
 * construit un AP non-tas pour tester `rec_est_tas_ver2`, convertit
 * un tableau en tas, puis effectue un tri par tas sur un tableau.
 * @return 0 en cas de succès.
 */
int main(void) {
    Tas t;
    t = alloc_mem_ap(t, 100);
    t = init_ap(t);
    t = rec_inser_tas(8, taille(t), t);
    t = rec_inser_tas(5, taille(t), t);
    t = rec_inser_tas(10, taille(t), t);
    t = rec_inser_tas(9, taille(t), t);
    t = rec_inser_tas(16, taille(t), t);
    t = rec_inser_tas(13, taille(t), t);
    t = rec_inser_tas(2, taille(t), t);

    parcours_largeur_par_niveau(t, taille(t));  // Avant suppression
    t = rec_supp_tas(t);
    parcours_largeur_par_niveau(t, taille(t));  // Après suppression

    ArbreParfait a;     // Construction d'un AP qui n'est pas un tas pour tester
    a = alloc_mem_ap(a, 100);
    a = init_ap(a);
    a = inser_elt_ap(4, a);
    a = inser_elt_ap(8, a);
    a = inser_elt_ap(7, a);
    a = inser_elt_ap(5, a);
    a = inser_elt_ap(3, a);
    a = inser_elt_ap(18, a);
    if (rec_est_tas_ver2(taille(a), 0, a)) {
        printf("c'est un tas\n");
    }
    else {
        printf("ce n'est pas un tas\n");
    }
    parcours_largeur_par_niveau(a, taille(a));
    ArbreParfait tas;
    tas = alloc_mem_ap(tas, taille(a));
    tas = init_ap(tas);
    a = rec_convert_tab_to_tas(taille(a), tas, a.tab);
    parcours_largeur_par_niveau(a, taille(a));
    int tab[7] = {2,5,6,7,6,4,7};
    tri_par_tas(7, tab);
    for (int i=0; i<7; i++) {
        printf("%d", tab[i]);
    }
}