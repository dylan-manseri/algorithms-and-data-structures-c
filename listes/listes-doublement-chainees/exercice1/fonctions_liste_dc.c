#include "../structure.h"

/**
 * Renvoie le coefficient d'un monôme.
 * @param mon Monôme.
 * @return Coefficient (double).
 */
double coef(Monome mon) {
    return mon.coef;
}

/**
 * Renvoie le degré d'un monôme.
 * @param mon Monôme.
 * @return Degré entier.
 */
int degre(Monome mon) {
    return mon.degre;
}

/**
 * Accède au monôme stocké dans la cellule courante du polynôme.
 * @param p Cellule du polynôme (non vide).
 * @return Le monôme porté par la cellule.
 */
Monome monome(Polynome p) {
    return p->monome;
}

/**
 * Renvoie la cellule suivante dans la chaîne du polynôme.
 * @param p Cellule courante.
 * @return Le successeur de p (NULL si p est en queue).
 */
Polynome suivant(Polynome p) {
    return p->suivant;
}

/**
 * Renvoie la cellule précédente dans la chaîne du polynôme.
 * @param p Cellule courante.
 * @return Le prédécesseur de p (NULL si p est en tête).
 */
Polynome precedent(Polynome p) {
    return p->precedent;
}

/**
 * Initialise un polynôme vide.
 * @return Polynôme vide (NULL).
 */
Polynome initP() {
    return NULL;
}

/**
 * Teste si un polynôme est vide.
 * @param p Polynôme à tester.
 * @return 1 si vide, 0 sinon.
 */
int estVideP(Polynome p) {
    return p==NULL;
}

/**
 * Construit un nouveau monôme à partir d'un coefficient et d'un degré.
 * @param coef Coefficient du monôme.
 * @param degre Degré du monôme.
 * @return Le monôme construit (par valeur).
 */
Monome newMon(double coef, int degre) {
    Monome m;
    m.coef = coef;
    m.degre = degre;
    return m;
}

/**
 * Affiche un polynôme sous la forme "c1x^d1 + c2x^d2 + ...".
 * @param p Polynôme à afficher (peut être vide).
 */
void printPolynome(Polynome p) {
    while (!estVideP(p)) {
        printf("%fx^%d", coef(monome(p)), degre(monome(p)));
        if (!estVideP(suivant(p))) {
            printf(" + ");
        }
        p=p->suivant;
    }
    printf("\n");
}

/**
 * Alloue une cellule de polynôme et y stocke le monôme passé.
 * Termine le programme en cas d'échec d'allocation.
 * @param m Monôme à stocker.
 * @return Pointeur vers la cellule allouée (chaînage non initialisé).
 */
Polynome allocMemRemp(Monome m) {
    Polynome p = (Polynome) malloc(sizeof(struct cellule));
    if (p==NULL) {
        printf("Erreur d'allocation");
        exit(1);
    }
    p->monome = m;
    return p;
}