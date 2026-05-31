#include "structure.h"

/**
 * Teste si un caractère est une parenthèse ouvrante.
 * @param c Caractère.
 * @return 1 si c == '(', 0 sinon.
 */
int est_po(char c) {
    return c == '(';
}

/**
 * Teste si un caractère est une parenthèse fermante.
 * @param c Caractère.
 * @return 1 si c == ')', 0 sinon.
 */
int est_pf(char c) {
    return c == ')';
}

/**
 * Teste si un caractère est un espace.
 * @param c Caractère.
 * @return 1 si c == ' ', 0 sinon.
 */
int est_sep(char c) {
    return c == ' ';
}

/**
 * Teste si un caractère est un point décimal.
 * @param c Caractère.
 * @return 1 si c == '.', 0 sinon.
 */
int est_point(char c) {
    return c == '.';
}

/**
 * Teste si un caractère est un chiffre décimal.
 * @param c Caractère.
 * @return 1 si c appartient à '0'..'9', 0 sinon.
 */
int est_chiffre(char c) {
    return c == '0' || c == '1' || c == '2' ||  c == '3' || c == '4' || c == '5' ||
        c == '6' || c == '7' || c == '8' || c == '9';
}

/**
 * Teste si un caractère est un opérateur arithmétique reconnu.
 * @param c Caractère.
 * @return 1 si c est dans { '+', '-', '*', '/' }, 0 sinon.
 */
int est_operateur(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

/**
 * Renvoie le code ASCII (entier) d'un caractère.
 * @param chr Caractère.
 * @return La valeur entière du code ASCII.
 */
int code_ascii(char chr) {
    return (int)chr;
}

/**
 * Lit dans une expression un nombre réel à partir de la position *i,
 * en avançant l'indice jusqu'au premier caractère non numérique.
 * @param i Pointeur sur l'indice courant dans la chaîne (modifié).
 * @param exp Chaîne contenant l'expression.
 * @return La valeur réelle extraite.
 */
double extraire_nb_reel(int *i, char* exp) {
    char chr = exp[*i];
    double n;
    double nbr = 0;
    if (est_chiffre(chr)) {
        do {
            n = code_ascii(chr) - code_ascii('0');
            nbr = nbr*10 + n;
            (*i)++;
            chr = exp[*i];
        } while (est_chiffre(chr));
    }
    if (est_point(chr)) {
        (*i)++;
        chr = exp[*i];
        double dec = 0.1;
        do {
            n = code_ascii(chr) - code_ascii('0');
            nbr = nbr + n*dec;
            dec /= 10;
            (*i)++;
            chr = exp[*i];
        } while (est_chiffre(chr));
    }
    return nbr;
}

/**
 * Construit l'arbre d'expression à partir d'une chaîne parenthésée.
 * Utilise deux piles auxiliaires (opérateurs et sous-arbres) pour gérer
 * la grammaire et la priorité induite par les parenthèses.
 * @param exp Chaîne représentant l'expression arithmétique parenthésée.
 * @return Le pointeur sur la racine de l'arbre d'expression construit.
 */
ArbreExp cons_a(char* exp) {
    Pile pOperateur = init_p();
    Pile pArbre = init_p();
    int i = 0;
    int lg = strlen(exp);
    int erreur = 0;
    while (i < lg && !erreur) {
        char chr = exp[i];
        if (est_po(chr) || est_sep(chr)) {
            i++;
        }
        else {
            if (est_chiffre(chr) || est_point(chr)) {
                double nM = extraire_nb_reel(&i, exp);
                TElementA a;
                a.nNoeud = OPERANDE;
                a.dNoeud.operande = nM;
                ArbreExp f = create_feuille(a);
                pArbre = empiler(f, pArbre);
            }
            else {
                if (est_operateur(chr)) {
                    char *copie = malloc(sizeof(char));
                    memcpy(copie, &chr, sizeof(char));
                    pOperateur = empiler(copie, pOperateur);
                    i++;
                }
                else {
                    if (est_pf(chr)) {
                        ArbreExp opD = sommet_p(pArbre);
                        pArbre = depiler(pArbre);
                        ArbreExp opG = sommet_p(pArbre);
                        pArbre = depiler(pArbre);
                        char *opA = sommet_p(pOperateur);
                        pOperateur = depiler(pOperateur);
                        TElementA elt;
                        elt.nNoeud = OPERATEUR;
                        DNoeud dnoeud; dnoeud.operateur = *opA;
                        elt.dNoeud = dnoeud;
                        ArbreExp nd = create_noeud(elt, opG, opD);
                        pArbre = empiler(nd, pArbre);
                        i++;
                    }
                    else {
                        erreur = 1;
                        printf("y'a un blem");
                    }
                }
            }
        }
    }
    ArbreExp aExp = sommet_p(pArbre);
    pArbre = depiler(pArbre);
    return aExp;
}

/**
 * Applique un opérateur binaire à deux opérandes réelles.
 * @param oper Opérateur ('+', '-', '*' ou '/').
 * @param vd Opérande de droite.
 * @param vg Opérande de gauche.
 * @return Le résultat du calcul vd <oper> vg.
 */
double eval_oper(char oper, double vd, double vg) {
    switch (oper) {
        case '+': return vd+vg;
        case '-': return vd-vg;
        case '*': return vd*vg;
        case '/': return vd/vg;
    }
}

/**
 * Évalue récursivement un arbre d'expression et renvoie la valeur calculée.
 * @param aExp Racine de l'arbre d'expression.
 * @return La valeur réelle de l'expression.
 */
double eval_a_exp(ArbreExp aExp) {
    if (est_feuille(aExp)) {
        return operande(d_noeud(donnee_a(aExp)));
    }
    double vg = eval_a_exp(aExp->filsGauche);
    double vd = eval_a_exp(aExp->filsDroit);
    char oper = operateur(d_noeud(donnee_a(aExp)));
    return eval_oper(oper, vd, vg);
}