//
// Created by dylanm on 10/02/2026.
//

#ifndef PROTOTYPETD12_H
#define PROTOTYPETD12_H

#include "structure.h"

int nb_som_gen(void* g, TypeGraphe type);
int nb_som_ma(MatAdjacence mat);

int est_vide(Liste l);
int est_vide_ls(ListeSucc ls);
int est_vide_lp(ListePred lp);
int donnee(Liste l);
int donnee_lp(ListePred lp);
int donnee_ls(ListeSucc ls);
Liste suivant(Liste l);
ListePred suivant_lp(ListePred lp);
ListeSucc suivant_ls(ListeSucc ls);
Liste inser_tete(int donnee, Liste l);
ListePred inser_tete_lp(int somPred, ListePred lp);
ListeSucc inser_tete_ls(int somSucc, ListeSucc ls);
Liste adr_dernier(Liste l);
ListePred adr_dernier_lp(ListePred lp);
ListeSucc adr_dernier_ls(ListeSucc ls);
Liste adr_insert(int cout, int* tabCout, Liste M);
Liste inser_triee_cout(int t, Liste M, int* D);
Liste supp_elt_cout(int t, Liste M);
Liste inser_queue(int donnee, Liste l);
ListePred inser_queue_lp(int somPred, ListePred lp);
ListeSucc inser_queue_ls(int somSucc, ListeSucc ls);
Liste inser_trie(int donnee, Liste l);
Liste init_l();
ListeSucc init_ls();
ListePred init_lp();
Liste supp_tete(Liste l);
int contain(int s, Liste l);
ListeArete init_l_arete();
int est_vide_l_arete(ListeArete la);
Arete donnee_l_arete(ListeArete la);
ListeArete suivant_l_arete(ListeArete la);
ListeArete inser_tete_l_arete(Arete donnee, ListeArete la);
ListeArete adr_insert_l_arete(int cout, ListeArete la);
ListeArete inser_triee_l_arete(Arete donnee, ListeArete la);

ListeAdjacence init_la(int nbSom);

MatAdjacence alloc_sma_f(int n);
void alloc_sma_p(int n, MatAdjacence *ma);
void *lib_tab_f(int *tab);
void lib_tab_p(int **tab);
void *lib_mat_f(int **mat, int nbLig);
void lib_mat_p(int ***mat, int nbLig);
MatAdjacence lib_mat_adj_f(MatAdjacence mat);
int* alloc_tab(int nMax);
void alloc_tab_p(int nMax, int **tab);
int** alloc_mem_mat_f(int nbLig, int nbCol);
void alloc_mem_mat_p(int nbLig, int nbCol, int*** mat);
void full_zero(int** mat, int n);
void lib_mat_adj_p(MatAdjacence *mat);
void alloc_la(int n, ListeAdjacence* la);
void alloc_fs(int n, int nbArcs, FileSuccesseur* fs);
void alloc_lsp(int n, ListeAdjSuccPred* lsp);
MatIncidence alloc_smi_f(int nbSom, int nbArcs);
MatriceIncidenceCC alloc_smicc(int n);
ListeArete supp_tete_l_arete(ListeArete la);

MatAdjacence loading(char* nom);

int* get_succ_by_type(int s, TypeGraphe type, void* g);
int* get_pred_by_type(int s, TypeGraphe type, void* g);
int get_nb_pred(int t, void* g, TypeGraphe type);
int get_nb_pred_ma(int t, MatAdjacence ma);
int get_nb_pred_fs(int t, FileSuccesseur fs);
int get_nb_pred_la(int t, ListeAdjacence la);
int* get_succ_mat_adj(int s, MatAdjacence g);
int* get_pred_mat_adj(int s, MatAdjacence g);
int* get_succ_fs(int s, FileSuccesseur fs);
int* get_pred_fs(int s, FileSuccesseur fs);
int* get_succ_l(int s, ListeAdjacence la);
int* get_pred_l(int s, ListeAdjacence la);

void print_tab(int n, int* tab);
void print_liste(Liste l);
void print_la(ListeAdjacence la);
void print_fs(FileSuccesseur fs);
void print_ls(ListeSucc ls);
void print_lp(ListePred lp);
void print_lsp(ListeAdjSuccPred lsp);
void print_mat(void* mat, TypeGraphe type);

int est_boucle_ma(MatAdjacence ma);
int est_boucle_fs(FileSuccesseur fs);
int est_boucle_la(ListeAdjacence la);

int max_succ_ma(MatAdjacence ma);
int max_succ_fs(FileSuccesseur fs);
int max_succ_la(ListeAdjacence la);

ListeAdjacence convert_ma_to_la(MatAdjacence ma);
int count_arc(MatAdjacence ma);
int count_arc_la(ListeAdjacence la);
FileSuccesseur convert_ma_to_fs(MatAdjacence ma);
ListeAdjSuccPred convert_ma_to_lsp(MatAdjacence ma);
ListeAdjacence convert_fs_to_la(FileSuccesseur fs);
FileSuccesseur convert_la_to_fs(ListeAdjacence la);
MatIncidence convert_ma_to_mi(MatAdjacence ma);
MatAdjacence convert_mi_to_ma(MatIncidence mi);
MatAdjacence convert_mi_to_ma_no(MatIncidence mi);

int cout_ma(int s, int t, MatAdjacence ma);
int cout_mi(int s, int t, MatIncidence mi);
int cout_fs(int s, int t, FileSuccesseur fs);
int cout_la(int s, int t, ListeAdjacence la);
int cout(int s, int t, void* g, TypeGraphe type);

int exist_ma(int s, int t, MatAdjacence ma);
int exist_mi(int s, int t, MatIncidence mi);
int exist_fs(int s, int t, FileSuccesseur fs);
int exist_la(int s, int t, ListeAdjacence la);
int exist(int s, int t, void* g, TypeGraphe type);

int main_td1_2(void);

#endif //TD1_2_PROTOTYPETD12_H