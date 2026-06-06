# Arbres binaires

Manipulation des **arbres binaires** en C, avec une application à l'évaluation
d'**arbres d'expression** arithmétique (opérateurs + opérandes) via une **pile**.

## Structures de données

Les nœuds peuvent contenir soit un opérateur, soit un opérande :

```c
typedef union {
    char   operateur;
    double operande;
} DNoeud;

typedef enum {
    OPERATEUR,
    OPERANDE
} NNoeud;
```

## Notions abordées

- Construction et parcours d'un arbre binaire
- Évaluation d'expressions arithmétiques sous forme arborescente
- Pile (LIFO) implémentée à partir de zéro
- Manipulation conjointe d'arbre et de pile

## Compilation

```bash
cmake -S . -B build
cmake --build build
./build/arbres_binaires
```