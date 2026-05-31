#ifndef STRUCT
#define STRUCT

typedef struct {
    int nbSom;
    int **mat;
    int **cout;
}MatAdjacence;

typedef struct {
    int nbSom;
    int nbArc;
    int **mat;
    int **cout;
}MatIncidence;

typedef enum {
    MAT_ADJACENCE,
    MAT_INCIDENCE,
    FILE_SUCCESSEUR,
    LISTE_ADJACENCE,
}TypeGraphe;

typedef struct{
    int nbSom;
    int nbArcs;
    int* FS;
    int* APS;
    int* cout;
}FileSuccesseur;

typedef struct cel{
    int donnee;
    struct cel* suivant;
    int cout;
}*Liste;

typedef Liste File;
typedef Liste Pile;

typedef struct{
    int nbSom;
    Liste *tabAdj;
}ListeAdjacence;

/**
 * La structure liste successeur et prédécesseur
 */
typedef struct celluleSucc{     // C'est vraiment juste des listes hein
    int somSucc;
    struct celluleSucc* suivSucc;
}*ListeSucc;

typedef struct cellulePred{
    int somPred;
    struct cellulePred* suivPred;
}*ListePred;

typedef struct{
    ListeSucc lSucc;
    ListePred lPred;
}ListeSuccPred;

typedef struct{
    int nbSom;
    ListeSuccPred *tabAdjSP;
}ListeAdjSuccPred;

typedef struct {
    int nbSom;
    int* alpha;
    int* beta;
    int* cout;
}MatriceIncidenceCC;

typedef struct {
    int somS;
    int somT;
    int cout;
}Arete;

typedef struct celArete{
    Arete arete;
    struct celArete* suivant;
}*ListeArete;

#endif