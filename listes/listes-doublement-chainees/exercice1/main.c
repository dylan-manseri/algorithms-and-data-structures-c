#include "../structure.h"

/**
 * Démonstration : construit un polynôme par insertions successives,
 * effectue une recherche puis une suppression de monôme, calcule le
 * coefficient maximum et la somme des coefficients, génère un polynôme
 * depuis un tableau, le dérive et ajoute les deux polynômes.
 * @return 0 en cas de succès.
 */
int main(void) {
    Polynome p = initP();
    p = inserMonPoly(newMon(13,0), p);
    p = inserMonPoly(newMon(-7,13), p);
    p = inserMonPoly(newMon(1,5), p);
    p = inserMonPoly(newMon(2,8), p);
    p = inserMonPoly(newMon(-2.5,2), p);
    printf("Polynome inital : ");
    printPolynome(p);

    printf("Recherche d un monome : ");
    printPolynome(rechMonPoly(newMon(1,5), p));

    p = suppMonPoly(newMon(-7,13), p);
    printf("Polynome apres suppression : ");
    printPolynome(p);

    //p = delPolynome(p);       Ca marche, mais j'ai encore besoin de mon polynome apres mdr
    //printPolynome(p);

    double cmax = maxCoef(p);
    printf("\nCoef max : %f", cmax);
    double som = somCoef(p);
    printf("\nSomme des coefs : %f\n", som);

    int tab[6] = {2,8,6,0,4,0};
    Polynome pg = generPoly(6, tab);
    printf("Polynome genere par tableau : ");
    printPolynome(pg);

    Polynome pderiv = derivPoly(pg);
    printf("Polynome derive : ");
    printPolynome(pderiv);

    Polynome sp = somPoly(p, pg);
    printf("Somme de polynomes : ");
    printPolynome(sp);

}