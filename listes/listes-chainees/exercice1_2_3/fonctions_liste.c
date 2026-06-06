#include "structure.h"

/**
 * Renvoie le facteur premier d'une donnée FactPremier.
 * @param f Couple (facteur, nombre d'occurrences).
 * @return La valeur du facteur premier.
 */
int fact(FactPremier f) {
    return f.fact;
}

/**
 * Renvoie le nombre d'occurrences associé à un facteur premier.
 * @param f Couple (facteur, nombre d'occurrences).
 * @return La multiplicité du facteur.
 */
int nb_occ(FactPremier f) {
    return f.nbOcc;
}

/**
 * Renvoie la donnée stockée dans une cellule de liste.
 * @param l Cellule de liste.
 * @return La donnée FactPremier portée par la cellule.
 */
FactPremier donnee(Liste l) {
    return l->donnee;
}

/**
 * Renvoie le pointeur sur la cellule suivante d'une liste.
 * @param l Cellule courante.
 * @return Le successeur (NULL si fin de liste).
 */
Liste suivant(Liste l) {
    return l->suivant;
}

/**
 * Initialise une liste vide.
 * @return Une liste vide (NULL).
 */
Liste create_liste(void) {
    return NULL;
}

/**
 * Renvoie le nombre associé à une entrée de TabLDFP.
 * @param cel Cellule TabLDFP (nombre + sa décomposition).
 * @return Le nombre original.
 */
int nombre(TabLDFP cel) {
    return cel.nbr;
}

/**
 * Renvoie la liste de facteurs premiers d'une entrée de TabLDFP.
 * @param cel Cellule TabLDFP.
 * @return La liste de facteurs premiers correspondante.
 */
Liste liste(TabLDFP cel) {
    return cel.ldfp;
}

/**
 * Construit une donnée FactPremier à partir d'un facteur et d'une multiplicité.
 * @param fact Le facteur premier.
 * @param nbOcc Le nombre d'occurrences.
 * @return La structure FactPremier prête à insérer.
 */
FactPremier create_fact_premier(int fact, int nbOcc) {
    FactPremier fp;
    fp.fact = fact;
    fp.nbOcc = nbOcc;
    return fp;
}

/**
 * Teste si une liste chaînée est vide.
 * @param l Liste à tester.
 * @return 1 si la liste est vide, 0 sinon.
 */
int est_vide(Liste l) {
    if (l == NULL) {
        return 1;
    }
    return 0;
}

/**
 * Renvoie l'adresse de la dernière cellule d'une liste non vide.
 * @param l Liste non vide.
 * @return Le pointeur sur la dernière cellule.
 */
Liste adr_dernier(Liste l) {
    while (!est_vide(suivant(l))) {
        l = suivant(l);
    }
    return l;
}

/**
 * Insère une donnée en tête de liste et renvoie la nouvelle tête.
 * @param fp Donnée à insérer.
 * @param l Liste destination.
 * @return La liste avec fp en tête.
 */
Liste inser_tete(FactPremier fp, Liste l) {
    Liste cel = malloc(sizeof(struct cellule));
    cel->donnee = fp;
    cel->suivant = l;
    return l = cel;
}

/**
 * Insère une donnée en queue de liste (gère le cas de la liste vide).
 * @param fp Donnée à insérer.
 * @param l Liste destination.
 * @return La liste avec fp en queue.
 */
Liste inser_queue(FactPremier fp, Liste l) {
    if (est_vide(l)) {
        return inser_tete(fp, l);
    }
    Liste der = adr_dernier(l);
    der->suivant = inser_tete(fp, suivant(der));
    return l;
}

/**
 * Construit une entrée TabLDFP associant un nombre à sa décomposition.
 * @param nbr Nombre d'origine.
 * @param l Liste de ses facteurs premiers.
 * @return La structure TabLDFP prête à utiliser.
 */
TabLDFP create_tab_ldfp(int nbr, Liste l) {
    TabLDFP cel;
    cel.nbr = nbr;
    cel.ldfp = l;
    return cel;
}

/**
 * Affiche une donnée FactPremier sous la forme `facteur^occurrences`.
 * @param fp Donnée à afficher.
 */
void print_fact_premier(FactPremier fp) {
    printf("%d^%d", fact(fp), nb_occ(fp));
}

/**
 * Affiche une liste chaînée de facteurs premiers entre barres verticales.
 * @param l Liste à afficher.
 */
void print_liste(Liste l) {
    if (est_vide(l)) {
        printf("Liste vide");
    }
    else {
        printf("| ");
        while (!est_vide(l)) {
            print_fact_premier(donnee(l));
            printf(" | ");
            l = suivant(l);
        }
    }
    printf("\n");
}

/**
 * Affiche un tableau de TabLDFP : pour chaque entrée, le nombre puis sa
 * décomposition en facteurs premiers.
 * @param tab Tableau de TabLDFP.
 * @param taille Nombre d'entrées dans le tableau.
 */
void print_tab_ldfp(TabLDFP* tab, int taille) {
    int nbr;
    for (int i=0; i<taille; i++) {
        nbr = nombre(*(tab+i));
        printf("%d -> ", nbr);
        Liste l = liste(*(tab+i));
        print_liste(l);
    }
}