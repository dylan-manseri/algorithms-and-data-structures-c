#include "../../include/prototype_td12.h"

/**
 * Crée une Liste d'adjacence à partir d'une matrice d'adjacence
 * @param ma Une matrice d'adjacence
 * @return La liste d'adjacence résultante
 */
ListeAdjacence convert_ma_to_la(MatAdjacence ma) {
    ListeAdjacence la;
    int n = ma.nbSom;
    int** mat = ma.mat;
    alloc_la(n, &la);
    for (int s=0; s<n; s++) {
        for (int t=0; t<n; t++) {
            if (mat[s][t] == 1) {
                la.tabAdj[s] = inser_queue(t ,la.tabAdj[s]);
            }
        }
    }
    return la;
}

/**
 * Compte le nombre d'arcs d'un graphe à partir d'unee matrice d'adjacence
 * @param ma
 * @return
 */
int count_arc(MatAdjacence ma) {
    int** mat = ma.mat;
    int n = ma.nbSom;
    int nb=0;
    for (int s=0; s<n; s++) {
        for (int t=0; t<n; t++) {
            if (mat[s][t] == 1) {
                nb++;
            }
        }
    }
    return nb;
}

/**
 * Construit une file de successeur à partir d'une matrice d'adjacence
 * @param ma
 * @return
 */
FileSuccesseur convert_ma_to_fs(MatAdjacence ma) {
    int nbArcs = count_arc(ma);  // Pour pouvoir allouer il nous faut le nombre d'élmt de FS, soit on le compte soit on définit une valeur max n*2
    FileSuccesseur fs;
    int n = ma.nbSom;
    int** mat = ma.mat;
    alloc_fs(n, nbArcs, &fs);
    int iaps = 0;
    int s;
    for (s=0; s<n; s++) {
        fs.APS[s] = iaps;
        for (int t=0; t<n; t++) {
            if (mat[s][t] == 1) {
                fs.FS[iaps] = t;
                iaps++;
            }
        }
    }
    fs.FS[iaps] = 0;
    fs.APS[s] = 0;
    return fs;
}

/**
 * Construit une Liste successeur prédécesseur à partir d'une matrice d'adjacence
 * @param ma
 * @return
 */
ListeAdjSuccPred convert_ma_to_lsp(MatAdjacence ma) {
    ListeAdjSuccPred lsp;
    int n = ma.nbSom;
    int** mat = ma.mat;
    alloc_lsp(n, &lsp);
    for (int s=0; s<n; s++) {
        for (int t=0; t<n; t++) {
            if (mat[s][t] == 1) {
                lsp.tabAdjSP[s].lSucc = inser_queue_ls(t, lsp.tabAdjSP[s].lSucc);
                lsp.tabAdjSP[t].lPred = inser_queue_lp(s, lsp.tabAdjSP[t].lPred);
            }
        }
    }
    return lsp;
}

/**
 * Construit une liste d'adjacence en fonction d'une file de successeur
 * @param fs la fille de successeur initial
 * @return la liste d'adjacence crée
 */
ListeAdjacence convert_fs_to_la(FileSuccesseur fs) {
    int n = fs.nbSom;
    ListeAdjacence la;
    alloc_la(fs.nbSom, &la);
    int iaps, nbr;
    for (int s=0; s<n; s++) {
        iaps = fs.APS[s];
        nbr = fs.APS[s+1] - fs.APS[s];
        for (int j=iaps; j<iaps+nbr; j++) {
            la.tabAdj[s] = inser_queue(fs.FS[j], la.tabAdj[s]);
        }
    }
    return la;
}

/**
 * Compte le nombre d'arcs dans une liste d'adjacence.
 * @param la Liste d'adjacence.
 * @return Le nombre total d'arcs.
 */
int count_arc_la(ListeAdjacence la) {
    int arc=0;
    for (int s=0; s<la.nbSom; s++) {
        Liste l = la.tabAdj[s];
        while (!est_vide(l)) {
            arc++;
            l = suivant(l);
        }
    }
    return arc;
}

/**
 * Construit une File de successeur à partir d'une liste d'adjacence
 * @param la La liste d'adjacence initiale
 * @return La File de successeur resultante
 */
FileSuccesseur convert_la_to_fs(ListeAdjacence la) {
    int n = la.nbSom;
    FileSuccesseur fs;
    int arcs = count_arc_la(la);
    alloc_fs(n, arcs, &fs);
    int iaps=0;
    Liste tmp;
    int s;
    for (s=0; s<n; s++) {
        fs.APS[s] = iaps;
        tmp = la.tabAdj[s];
        while (!est_vide(tmp)) {
            fs.FS[iaps] = donnee(tmp);
            iaps++;
            tmp = suivant(tmp);
        }
    }
    fs.APS[s] = iaps;       // Sommets virtuels
    fs.FS[iaps] = 0;
    return fs;
}

/**
 * Convertit une matrice d'incidence à partir d'une matrice d'adjacence
 * @param ma la matrice d'adjacence initial
 * @return la matrice d'incidence résultante
 */
MatIncidence convert_ma_to_mi(MatAdjacence ma) {
    int nbSom = ma.nbSom;
    int nbArcs = count_arc(ma);
    MatIncidence matI = alloc_smi_f(nbSom, nbArcs);
    int currentArc = 0;
    for (int s=0; s<nbSom; s++) {
        for (int t=0; t<nbSom; t++) {
            if (ma.mat[s][t] == 1) {
                matI.mat[s][currentArc] = +1;
                matI.mat[t][currentArc] = -1;
                currentArc++;
            }
        }
    }
    return matI;
}

/**
 * Conversion d'une matrice d'incidence vers une matrice d'adjacence
 * Pour un graphe ORIENTE
 * @param mi
 * @return
 */
MatAdjacence convert_mi_to_ma(MatIncidence mi) {
    int nbArc = mi.nbArc;
    int nbSom = mi.nbSom;
    int s, t;
    MatAdjacence ma = alloc_sma_f(mi.nbSom);
    for (int a = 0; a<nbArc; a++) {
        for (int i=0; i<nbSom; i++) {
            if (mi.mat[i][a] == 1) {
                s = i;
            }
            else if (mi.mat[i][a] == -1) {
                t = i;
            }
        }
        ma.mat[s][t] = 1;
    }
    return ma;
}

/**
 * Conversion d'une matrice incidence vers une matrice d'adjacence
 * Pour un grpahe NON ORIENTE
 * @param mi
 * @return
 */
MatAdjacence convert_mi_to_ma_no(MatIncidence mi) {
    int nbArc = mi.nbArc;
    int nbSom = mi.nbSom;
    int s, t;
    int first = 1;      // Variable pour préciser si c'est le 1er sommet rencontré
    MatAdjacence ma = alloc_sma_f(mi.nbSom);
    for (int a = 0; a<nbArc; a++) {
        first = 1;
        for (int i=0; i<nbSom; i++) {
            if (mi.mat[i][a] == 1 && first) {
                s = i;
                first = 0;      // Le prochain ne sera pas le premier
            }
            else if (mi.mat[i][a] == 1 && !first) {
                t = i;
            }
        }
        ma.mat[s][t] = 1;
        ma.mat[t][s] = 1;
    }
    return ma;
}