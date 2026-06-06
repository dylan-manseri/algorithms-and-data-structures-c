#include "../structure.h"

/**
 * Insère un monôme en tête du polynôme.
 * @param m Monôme à insérer.
 * @param p Polynôme courant.
 * @return Le polynôme avec sa nouvelle tête.
 */
Polynome inserTete(Monome m, Polynome p) {
    Polynome cel = allocMemRemp(m);
    cel->suivant = p;
    cel->precedent = initP();
    p=cel;
    return p;
}

/**
 * Supprime la cellule de tête du polynôme et libère sa mémoire.
 * Aucune action si le polynôme est vide.
 * @param p Polynôme courant.
 * @return Le polynôme privé de sa tête.
 */
Polynome suppTete(Polynome p) {
    if (estVideP(p)) {
        return p;
    }
    Polynome as=p;
    p=p->suivant;
    free(as);
    return p;
}

/**
 * Recherche, dans un polynôme trié par degré croissant, l'adresse
 * de la cellule juste avant celle où le monôme m doit être inséré.
 * @param m Monôme à insérer.
 * @param p Cellule de départ (non vide).
 * @return La cellule après laquelle l'insertion doit avoir lieu.
 */
Polynome adresseInsertion(Monome m, Polynome p) {
    while (!estVideP(suivant(p)) && degre(monome(suivant(p))) < degre(m) ) {
        p=p->suivant;
    }
    return p;
}

/**
 * Teste si un double est numériquement nul (comparaison à epsilon).
 * @param d Valeur à tester.
 * @return 1 si |d| < 1e-9, 0 sinon.
 */
int zero(double d) {
    double epsilon = 1e-9;
    if (fabs(d) < epsilon) {
        return 1;
    }
    return 0;
}

/**
 * Insère un monôme en queue du polynôme.
 * @param m Monôme à insérer.
 * @param der Adresse de la dernière cellule du polynôme.
 * @param p Polynôme courant.
 * @return Le polynôme inchangé en tête (la queue a été étendue).
 */
Polynome inserQueue(Monome m, Polynome der, Polynome p) {
    Polynome cel = allocMemRemp(m);
    cel->suivant = NULL;
    cel->precedent = der;
    der->suivant = cel;
    return p;
}

/**
 * Insère un monôme juste après une cellule donnée (cas général).
 * @param m Monôme à insérer.
 * @param ai Adresse de la cellule précédant l'insertion.
 * @param p Polynôme courant.
 * @return Le polynôme avec le monôme inséré.
 */
Polynome inserApres(Monome m, Polynome ai,Polynome p) {
    Polynome cel = allocMemRemp(m);
    Polynome sai = suivant(ai);
    cel->suivant = sai;
    sai->precedent = cel;
    ai->suivant = cel;
    cel->precedent = ai;
    return p;
}

/**
 * Supprime la cellule de queue.
 * @param as Adresse de la cellule à supprimer (queue actuelle).
 * @param p Polynôme courant.
 * @return Le polynôme avec sa queue libérée.
 */
Polynome suppQueue(Polynome as, Polynome p) {
    (as->precedent)->suivant = NULL;
    free(as);
    return p;
}

/**
 * Supprime une cellule située ailleurs qu'aux extrémités.
 * @param as Adresse de la cellule à supprimer.
 * @param p Polynôme courant.
 * @return Le polynôme privé de la cellule.
 */
Polynome suppAilleurs(Polynome as, Polynome p) {
    (as->precedent)->suivant = suivant(as);
    (as->suivant)->precedent = precedent(as);
    free(as);
    return p;
}

/**
 * Insère un monôme dans un polynôme trié par degré croissant en
 * fusionnant les coefficients lorsque les degrés coïncident.
 * @param m Monôme à insérer.
 * @param p Polynôme courant.
 * @return Le polynôme mis à jour.
 */
Polynome inserMonPoly(Monome m, Polynome p) {
    if (estVideP(p)) {
        return inserTete(m,p);
    }
    double dm = degre(m);
    double dmp = degre(monome(p));
    if (dm < dmp) {                         //On fait les tests pour le premier monome
        return inserTete(m,p);
    }
    if (dm == dmp) {
        double sc = coef(m) + coef(monome(p));
        if (zero(sc)) {
            return suppTete(p);
        }
        p->monome.coef = sc;
    }
    Polynome ai = adresseInsertion(m,p);    //L'insertion ne se faisant pas au debut, on cherche l'adresse d'insertion
    Polynome sai = suivant(ai);
    if (estVideP(sai)) {                    //On fait les mêmes tests pour ce polynome
        return inserQueue(m,ai,p);
    }
    int dmsai = degre(monome(sai));
    if (dm<dmsai) {
        return inserApres(m, ai, p);
    }
    double sc  = coef(monome(sai))+coef(m);
    if (zero(sc)) {
        if (estVideP(suivant(sai))) {
            return suppQueue(sai,p);
        }
        return suppAilleurs(sai,p);
    }
    (sai->monome).coef = sc;
    return p;
}

/**
 * Recherche un monôme dans le polynôme (par degré et coefficient).
 * @param m Monôme recherché.
 * @param p Polynôme dans lequel chercher.
 * @return La cellule contenant le monôme, ou NULL si absent.
 */
Polynome rechMonPoly(Monome m, Polynome p) {    // Pas compris "renvoyer l'adresse du monome" alors que Monome
    int dm = degre(m);                          // n'est pas une structure pointée, donc j'ai renvoyé le polynome
    double cm = coef(m);
    int dmp = degre(monome(p));
    double cmp = coef(monome(p));
    while (!estVideP(p) && dm!=dmp && cm!=cmp) {
        p=p->suivant;
        dmp = degre(monome(p));
        cmp = coef(monome(p));
    }
    return p;
}

/**
 * Supprime un monôme du polynôme en choisissant la primitive adaptée
 * (tête, queue ou milieu) selon la position de la cellule trouvée.
 * @param m Monôme à supprimer.
 * @param p Polynôme courant.
 * @return Le polynôme mis à jour.
 */
Polynome suppMonPoly(Monome m, Polynome p) {
    Polynome as = rechMonPoly(m, p);
    if (estVideP(precedent(as))) {
        return suppTete(as);
    }
    if (estVideP(suivant(as))) {
        return suppQueue(as, p);
    }
    return suppAilleurs(as,p);
}

/**
 * Libère toutes les cellules du polynôme.
 * @param p Polynôme à détruire.
 * @return Un polynôme vide (NULL).
 */
Polynome delPolynome(Polynome p) {
    while (!estVideP(p)) {
        p=suppTete(p);
    }
    return p;
}

/**
 * Calcule le coefficient maximum d'un polynôme non vide.
 * @param p Polynôme non vide.
 * @return La plus grande valeur de coefficient présente.
 */
double maxCoef(Polynome p) {
    double cp = coef(monome(p));
    double cmax = cp;
    p=suivant(p);
    while (!estVideP(p)) {
        cp = coef(monome(p));
        if (cp>cmax) {
            cmax=cp;
        }
        p=suivant(p);
    }
    return cmax;
}

/**
 * Calcule la somme de tous les coefficients du polynôme.
 * @param p Polynôme (peut être vide).
 * @return La somme des coefficients (0 si vide).
 */
double somCoef(Polynome p) {
    double som = 0;
    while (!estVideP(p)) {
        som+=coef(monome(p));
        p=suivant(p);
    }
    return som;
}

/**
 * Construit un polynôme à partir d'un tableau de coefficients.
 * L'indice du tableau sert de degré ; les coefficients nuls sont ignorés.
 * @param n Taille du tableau.
 * @param tab Tableau de coefficients (indexé par le degré).
 * @return Le polynôme construit.
 */
Polynome generPoly(int n, int *tab) {
    Polynome p = initP();
    Monome m;
    double coef;
    for (int i=0; i<n; i++) {
        coef=tab[i];
        if (coef!=0) {
            m = newMon(coef, i);
            p=inserMonPoly(m,p);
        }
    }
    return p;
}

/**
 * Calcule la dérivée formelle d'un polynôme.
 * @param p Polynôme à dériver.
 * @return Un nouveau polynôme représentant p'.
 */
Polynome derivPoly(Polynome p) {
    Polynome pderiv = initP();
    Monome m;
    int deg;
    double coeff;
    while (!estVideP(p)) {
        m = monome(p);
        if (degre(m) != 0) {
            deg = degre(m)-1;
            coeff = coef(m)*degre(m);
            m = newMon(coeff, deg);
            pderiv = inserMonPoly(m, pderiv);
        }
        p=suivant(p);
    }
    return pderiv;
}

/**
 * Calcule la somme de deux polynômes triés par degré croissant.
 * @param p1 Premier polynôme.
 * @param p2 Second polynôme.
 * @return Un nouveau polynôme p1 + p2.
 */
Polynome somPoly(Polynome p1, Polynome p2) {
    Polynome sp = initP();
    int dp1, dp2;
    double cp1, cp2;
    Monome m;
    while (!estVideP(p1) && !estVideP(p2)) {
        dp1 = degre(monome(p1));
        dp2 = degre(monome(p2));
        if (dp1<dp2) {
            sp = inserMonPoly(monome(p1), sp);
            p1=suivant(p1);
        }
        else if (dp1>dp2) {
            sp = inserMonPoly(monome(p2), sp);
            p2=suivant(p2);
        }
        else {
            cp1 = coef(monome(p1));
            cp2 = coef(monome(p2));
            if (cp1+cp2 != 0) {
                m = newMon(cp1+cp2, dp1);
                sp = inserMonPoly(m,sp);
            }
            p1=suivant(p1);
            p2=suivant(p2);
        }
    }
    while (!estVideP(p1)) {
        sp = inserMonPoly(monome(p1), sp);
        p1=suivant(p1);
    }
    while (!estVideP(p2)) {
        sp = inserMonPoly(monome(p2), sp);
        p2=suivant(p2);
    }
    return sp;
}