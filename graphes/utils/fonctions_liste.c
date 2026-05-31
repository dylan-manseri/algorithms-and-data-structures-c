/**
 * Toutes les fonctions relatives aux listes utilisées dans le projet.
 * Trois familles cohabitent :
 *   - Liste classique : utilisée pour les listes d'adjacence.
 *   - ListeSucc : utilisée pour la partie successeur de ListeAdjSuccPred.
 *   - ListePred : utilisée pour la partie prédécesseur de ListeAdjSuccPred.
 *   - ListeArete : utilisée pour les listes d'arêtes (TD9 Kruskal).
 */
#include <stdlib.h>

#include "../include/prototype_td12.h"
#include "../include/structure.h"

/**
 * Initialise une liste d'arêtes vide.
 * @return Une liste vide (NULL).
 */
ListeArete init_l_arete() {
    return NULL;
}

/**
 * Renvoie le nombre de sommets d'une matrice d'adjacence.
 * @param m Matrice d'adjacence.
 * @return Le nombre de sommets.
 */
int nb_som(MatAdjacence m){
    return m.nbSom;
}

/**
 * Teste si une liste classique est vide.
 * @param l Liste à tester.
 * @return 1 si vide, 0 sinon.
 */
int est_vide(Liste l){
    return l == NULL;
}

/**
 * Teste si une liste de prédécesseurs est vide.
 * @param lp Liste à tester.
 * @return 1 si vide, 0 sinon.
 */
int est_vide_lp(ListePred lp) {
    return lp == NULL;
}

/**
 * Teste si une liste de successeurs est vide.
 * @param ls Liste à tester.
 * @return 1 si vide, 0 sinon.
 */
int est_vide_ls(ListeSucc ls) {
    return ls == NULL;
}

/**
 * Teste si une liste d'arêtes est vide.
 * @param la Liste à tester.
 * @return 1 si vide, 0 sinon.
 */
int est_vide_l_arete(ListeArete la) {
    return la == NULL;
}

/**
 * Renvoie la donnée portée par la tête d'une liste classique.
 * @param l Liste non vide.
 * @return La valeur entière en tête.
 */
int donnee(Liste l){
    return l->donnee;
}

/**
 * Renvoie le sommet prédécesseur d'une cellule de ListePred.
 * @param lp Cellule non NULL.
 * @return L'indice du sommet prédécesseur.
 */
int donnee_lp(ListePred lp){
    return lp->somPred;
}

/**
 * Renvoie le sommet successeur d'une cellule de ListeSucc.
 * @param ls Cellule non NULL.
 * @return L'indice du sommet successeur.
 */
int donnee_ls(ListeSucc ls){
    return ls->somSucc;
}

/**
 * Renvoie l'arête portée par la tête d'une ListeArete.
 * @param la Liste non vide.
 * @return L'arête en tête (struct Arete).
 */
Arete donnee_l_arete(ListeArete la) {
    return la->arete;
}

/**
 * Renvoie la cellule suivante d'une liste classique.
 * @param l Cellule courante.
 * @return Le successeur (NULL si fin).
 */
Liste suivant(Liste l){
    return l->suivant;
}

/**
 * Renvoie la cellule suivante dans une liste de prédécesseurs.
 * @param lp Cellule courante.
 * @return Le successeur (NULL si fin).
 */
ListePred suivant_lp(ListePred lp) {
    return lp->suivPred;
}

/**
 * Renvoie la cellule suivante dans une liste de successeurs.
 * @param ls Cellule courante.
 * @return Le successeur (NULL si fin).
 */
ListeSucc suivant_ls(ListeSucc ls) {
    return ls->suivSucc;
}

/**
 * Renvoie la cellule suivante dans une liste d'arêtes.
 * @param la Cellule courante.
 * @return Le successeur (NULL si fin).
 */
ListeArete suivant_l_arete(ListeArete la) {
    return la->suivant;
}

/**
 * Insère une donnée en tête d'une liste classique.
 * @param donnee Valeur à insérer.
 * @param l Liste destination.
 * @return La nouvelle tête de liste.
 */
Liste inser_tete(int donnee, Liste l){
    Liste cel = malloc(sizeof(struct cel));
    cel->donnee = donnee;
    cel->suivant = l;
    l = cel;
    return l;
}

/**
 * Insère une arête en tête d'une ListeArete.
 * @param donnee Arête à insérer.
 * @param la Liste destination.
 * @return La nouvelle tête de liste.
 */
ListeArete inser_tete_l_arete(Arete donnee, ListeArete la) {
    ListeArete cel = malloc(sizeof(struct celArete));
    cel->arete = donnee;
    cel->suivant = la;
    return cel;
}

/**
 * Cherche l'adresse d'insertion dans une ListeArete triée par coût décroissant.
 * @param cout Coût de l'arête à placer.
 * @param la Liste triée.
 * @return La cellule de référence pour l'insertion.
 */
ListeArete adr_insert_l_arete(int cout, ListeArete la) {
    while (!est_vide_l_arete(suivant_l_arete(la)) && cout < la->arete.cout) {
        la = suivant_l_arete(la);
    }
    return la;
}

/**
 * Insère une arête à sa place dans une ListeArete triée par coût.
 * @param donnee Arête à insérer.
 * @param la Liste triée.
 * @return La liste avec l'arête insérée.
 */
ListeArete inser_triee_l_arete(Arete donnee, ListeArete la) {
    if (est_vide_l_arete(la)) {
        return inser_tete_l_arete(donnee, la);
    }
    ListeArete ai = adr_insert_l_arete(la->arete.cout, la);
    ai->suivant = inser_tete_l_arete(donnee, ai->suivant);
    return la;
}

/**
 * Supprime et libère la tête d'une ListeArete.
 * @param la Liste non vide.
 * @return La liste sans son ancien premier élément.
 */
ListeArete supp_tete_l_arete(ListeArete la) {
    ListeArete as = la;
    la = suivant_l_arete(la);
    free(as);
    return la;
}

/**
 * Cherche l'adresse d'insertion dans une liste M triée selon `tabCout`.
 * @param cout Coût de l'élément à insérer.
 * @param tabCout Tableau associant un coût à chaque sommet.
 * @param M Liste triée selon tabCout.
 * @return La cellule de référence pour l'insertion.
 */
Liste adr_insert(int cout, int* tabCout, Liste M) {
    while (!est_vide(suivant(M)) && tabCout[donnee(suivant(M))] < cout) {
        M = suivant(M);
    }
    return M;
}

/**
 * Insère un sommet t dans une liste M triée selon les coûts D.
 * Utilisé dans Dijkstra (file de priorité naïve).
 * @param t Sommet à insérer.
 * @param M Liste triée.
 * @param D Tableau des distances.
 * @return La liste avec t inséré à sa place.
 */
Liste inser_triee_cout(int t, Liste M, int* D) {
    if (est_vide(M) || D[t] < D[donnee(M)]) {
        return inser_tete(t, M);
    }
    Liste ai = adr_insert(D[t], D, M);
    Liste new = malloc(sizeof(struct cel));
    new->donnee = t;
    new->suivant = suivant(ai);
    ai->suivant = new;
    return M;
}

/**
 * Supprime récursivement la cellule contenant t d'une liste triée.
 * @param t Valeur à retirer.
 * @param M Liste source (modifiée).
 * @return La liste sans l'élément t.
 */
Liste supp_elt_cout(int t, Liste M) {
    if (donnee(M) == t) {
        return supp_tete(M);
    }
    return M->suivant = supp_elt_cout(t, suivant(M));
}

/**
 * Insère un sommet prédécesseur en tête d'une ListePred.
 * @param somPred Indice du sommet prédécesseur.
 * @param lp Liste destination.
 * @return La nouvelle tête de liste.
 */
ListePred inser_tete_lp(int somPred, ListePred lp) {
    ListePred cellulePred = malloc(sizeof(struct cellulePred));
    cellulePred->somPred = somPred;
    cellulePred->suivPred = lp;
    lp = cellulePred;
    return lp;
}

/**
 * Insère un sommet successeur en tête d'une ListeSucc.
 * @param somSucc Indice du sommet successeur.
 * @param ls Liste destination.
 * @return La nouvelle tête de liste.
 */
ListeSucc inser_tete_ls(int somSucc, ListeSucc ls) {
    ListeSucc celluleSucc = malloc(sizeof(struct celluleSucc));
    celluleSucc->somSucc = somSucc;
    celluleSucc->suivSucc = ls;
    ls = celluleSucc;
    return ls;
}

/**
 * Renvoie l'adresse de la dernière cellule d'une liste classique.
 * @param l Liste à parcourir.
 * @return La dernière cellule (NULL si liste vide).
 */
Liste adr_dernier(Liste l){
    if(est_vide(l)){
        return l;
    }
    while(!est_vide(suivant(l))){
        l = suivant(l);
    }
    return l;
}

/**
 * Renvoie l'adresse de la dernière cellule d'une ListePred.
 * @param lp Liste à parcourir.
 * @return La dernière cellule (NULL si liste vide).
 */
ListePred adr_dernier_lp(ListePred lp) {
    if (est_vide_lp(lp)) {
        return lp;
    }
    while (!est_vide_lp(suivant_lp(lp))){
        lp = suivant_lp(lp);
    }
    return lp;
}

/**
 * Renvoie l'adresse de la dernière cellule d'une ListeSucc.
 * @param ls Liste à parcourir.
 * @return La dernière cellule (NULL si liste vide).
 */
ListeSucc adr_dernier_ls(ListeSucc ls) {
    if (est_vide_ls(ls)) {
        return ls;
    }
    while (!est_vide_ls(suivant_ls(ls))) {
        ls = suivant_ls(ls);
    }
    return ls;
}

/**
 * Cherche l'adresse d'insertion d'un entier d dans une liste triée croissante.
 * @param d Valeur à insérer.
 * @param l Liste triée.
 * @return La cellule de référence pour l'insertion.
 */
Liste adr_insertion(int d, Liste l) {
    while (!est_vide(suivant(l)) && d > donnee(suivant(l))){
        l = suivant(l);
    }
    return l;
}

/**
 * Insère une donnée en queue d'une liste classique.
 * Gère le cas de la liste vide en délégant à inser_tete.
 * @param donnee Valeur à insérer.
 * @param l Liste destination.
 * @return La liste avec la donnée en queue.
 */
Liste inser_queue(int donnee, Liste l){
    if(est_vide(l)){
        return inser_tete(donnee, l);
    }
    Liste der = adr_dernier(l);
    der->suivant = inser_tete(donnee, suivant(der));
    return l;
}

/**
 * Insère un sommet prédécesseur en queue d'une ListePred.
 * @param somPred Indice du sommet prédécesseur.
 * @param lp Liste destination.
 * @return La liste avec le sommet en queue.
 */
ListePred inser_queue_lp(int somPred, ListePred lp) {
    if (est_vide_lp(lp)) {
        return inser_tete_lp(somPred, lp);
    }
    ListePred der = adr_dernier_lp(lp);
    der->suivPred = inser_tete_lp(somPred, suivant_lp(lp));
    return lp;
}

/**
 * Insère un sommet successeur en queue d'une ListeSucc.
 * @param somSucc Indice du sommet successeur.
 * @param ls Liste destination.
 * @return La liste avec le sommet en queue.
 */
ListeSucc inser_queue_ls(int somSucc, ListeSucc ls) {
    if (est_vide_ls(ls)) {
        return inser_tete_ls(somSucc, ls);
    }
    ListeSucc der = adr_dernier_ls(ls);
    der->suivSucc = inser_tete_ls(somSucc, suivant_ls(ls));
    return ls;
}

/**
 * Insère une donnée à sa place dans une liste triée croissante.
 * @param donnee Valeur à insérer.
 * @param l Liste triée.
 * @return La liste avec la donnée insérée.
 */
Liste inser_trie(int donnee, Liste l) {
    if(est_vide(l)) {
        return inser_tete(donnee, l);
    }
    Liste ai = adr_insertion(donnee, l);
    if (ai != NULL) {
        ai->suivant = inser_tete(donnee, suivant(ai));
    }
    return l;
}

/**
 * Initialise une liste classique vide.
 * @return Une liste vide (NULL).
 */
Liste init_l(){
    return NULL;
}

/**
 * Initialise une liste de successeurs vide.
 * @return Une liste vide (NULL).
 */
ListeSucc init_ls() {
    return NULL;
}

/**
 * Initialise une liste de prédécesseurs vide.
 * @return Une liste vide (NULL).
 */
ListePred init_lp() {
    return NULL;
}

/**
 * Supprime et libère la tête d'une liste classique.
 * @param l Liste non vide.
 * @return La liste sans son ancien premier élément.
 */
Liste supp_tete(Liste l) {
    Liste tmp = l;
    l = suivant(l);
    free(tmp);
    return l;
}

/**
 * Teste l'appartenance d'un entier à une liste classique.
 * @param d Valeur recherchée.
 * @param l Liste à parcourir.
 * @return 1 si d apparaît dans la liste, 0 sinon.
 */
int contain(int d, Liste l) {
    int trouve = 0;
    while (!est_vide(l) && !trouve) {
        if (donnee(l) == d) {
            trouve = 1;
        }
        l = suivant(l);
    }
    return trouve;
}
