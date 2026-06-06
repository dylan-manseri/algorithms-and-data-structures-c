#include "structure.h"

/**
 * Renvoie la cellule de tête d'une ListeCTQ.
 * @param l Liste circulaire à tête/queue/taille.
 * @return Le pointeur sur la tête.
 */
ListeC tete(ListeCTQ l) {
    return l.tete;
}

/**
 * Renvoie la cellule de queue d'une ListeCTQ.
 * @param l Liste circulaire à tête/queue/taille.
 * @return Le pointeur sur la queue.
 */
ListeC queue(ListeCTQ l) {
    return l.queue;
}

/**
 * Initialise une ListeCTQ vide (tête et queue à NULL, taille 0).
 * @return La structure initialisée.
 */
ListeCTQ init_lctq(void) {
    ListeCTQ l;
    l.tete = NULL;
    l.queue = NULL;
    l.taille = 0;
    return l;
}

/**
 * Insère un premier élément dans une ListeCTQ vide.
 * @param elt Valeur à insérer.
 * @param l Pointeur sur la ListeCTQ vide à initialiser à un élément.
 */
void inser_vide_lctq(int elt, ListeCTQ *l) {
    ListeC cel = alloc_mem(elt);
    cel->suivant = cel;
    (*l).tete = cel;
    (*l).queue = cel;
    (*l).taille = 1;
}

/**
 * Insère un élément en tête d'une ListeCTQ (la queue reste inchangée).
 * @param elt Valeur à insérer.
 * @param l Pointeur sur la liste à modifier.
 */
void inser_tete_lctq(int elt, ListeCTQ *l) {
    ListeC cel = alloc_mem(elt);
    cel->suivant = tete(*l);
    (l->queue)->suivant = cel;
    (*l).tete = cel;
    (*l).taille++;
}

/**
 * Insère un élément en queue d'une ListeCTQ et met à jour le pointeur de queue.
 * @param elt Valeur à insérer.
 * @param l Pointeur sur la liste à modifier.
 */
void inser_queue_lctq(int elt, ListeCTQ *l) {
    ListeC cel = alloc_mem(elt);
    cel->suivant = tete(*l);
    (l->queue)->suivant = cel;
    (*l).queue = cel;
    (*l).taille++;
}

/**
 * Affiche le contenu d'une ListeCTQ (délègue à print_liste depuis la tête).
 * @param l Liste à afficher.
 */
void print_liste_ctq(ListeCTQ l) {
    print_liste(tete(l));
}