#include "structure.h"

/**
 * Démonstration : construit l'arbre d'expression « (23.5+22.6) » et affiche
 * le résultat de son évaluation.
 * @return 0 en cas de succès.
 */
int main(void) {
    char* exp = "(23.5+22.6)";
    ArbreExp ae = cons_a(exp);
    double d = eval_a_exp(ae);
    printf("%f", d);
}