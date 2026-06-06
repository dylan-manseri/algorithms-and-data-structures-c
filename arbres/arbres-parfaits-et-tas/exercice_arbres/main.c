#include "../structure.h"

/**
 * Démonstration : construit interactivement un arbre parfait puis l'affiche
 * niveau par niveau (deux variantes : générique, et version optimisée pour
 * arbre plein).
 * @return 0 en cas de succès.
 */
int main(void) {
    ArbreParfait a = const_ap();
    parcours_largeur_par_niveau(a, taille(a));
    parcours_arbre_parfait_niveau_plein(a);
}