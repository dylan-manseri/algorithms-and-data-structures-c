/**
 *Fonction principale, décommenter pour tester chaque fonctions
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/prototype_td12.h"

int main_td1_2(void) {
    // STRUCTURE MATRICE ADJACENCE

    MatAdjacence mat = loading("graphe.txt");
    //print_mat(mat);

    //trait_succ_mat_adj(3, mat);
    //trait_pred_mat_adj(3, mat);

    /*if(est_boucle_ma(mat)){
        printf("C'est une boucle !\n");
    }
    else{
        printf("Ce n'est pas une boucle...\n");
    }*/

   //printf("%d\n", max_succ_ma(mat));

    /*ListeAdjacence lAdj = convert_ma_to_la(mat);
    print_la(lAdj);*/

    /*FileSuccesseur fsu = convert_ma_to_fs(mat);
    print_fs(fsu);*/

    /*ListeAdjSuccPred lsp = convert_ma_to_lsp(mat);
    print_lsp(lsp);*/

    /*MatIncidence mi = convert_ma_to_mi(mat);
    printf("Matrice adjacence :\n");
    print_mat(&mat, MAT_ADJACENCE);
    printf("Matrice d'incidence :\n");
    print_mat(&mi, MAT_INCIDENCE);*/

    // STRUCTURE FILE DE SUCCESSEUR

    FileSuccesseur fs;
    fs.nbSom = 4;
    fs.nbArcs = 5;
    fs.FS = malloc(fs.nbArcs * sizeof(int));
    fs.APS = malloc(fs.nbSom * sizeof(int));
    fs.FS[0]=2; fs.FS[1]=3; fs.FS[2]=3; fs.FS[3]=1; fs.FS[4]=2; fs.FS[5]=0;
    fs.APS[0]=0; fs.APS[1]=2; fs.APS[2]=3; fs.APS[3]=4; fs.APS[4]=5;

    /*int* succ = get_succ_fs(3, fs);
    print_tab(3, succ);*/

    /*int* pred = get_pred_fs(3, fs);
    print_tab(2, pred);*/

    /*if(est_boucle_fs(fs)){
        printf("C'est une boucle !\n");
    }

    else{
        printf("Ce n'est pas une boucle...\n");
    }*/

   //printf("%d\n", max_succ_fs(fs));

    /*ListeAdjacence listeAdj = convert_fs_to_la(fs);
    print_la(listeAdj);*/

    // STRUCTURE LISTE ADJACENCE

    ListeAdjacence la;
    alloc_la(4, &la);
    la.tabAdj[0] = inser_queue(1, la.tabAdj[0]);
    la.tabAdj[1] = inser_queue(2, la.tabAdj[1]);
    la.tabAdj[2] = inser_queue(0, la.tabAdj[2]);
    la.tabAdj[2] = inser_queue(1, la.tabAdj[2]);
    la.tabAdj[3] = inser_queue(3, la.tabAdj[3]);

    /*int* succ = get_succ_l(3, la);
    print_tab(4, succ);*/

    /*int* pred = get_pred_l(1, la);
    print_tab(4, pred);*/

    /*if(est_boucle_la(la)){
        printf("C'est une boucle !\n");
    }
    else{
        printf("Ce n'est pas une boucle...\n");
    }/*

   //printf("%d\n", max_succ_la(la)+1);

    /*FileSuccesseur f = convert_la_to_fs(la);
    print_fs(f);*/

    return 0;
}