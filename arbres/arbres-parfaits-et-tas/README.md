# Arbres parfaits et tas

Implémentation des **arbres parfaits** et des **tas (heaps)** en C, avec une
représentation par **tableau** pour exploiter la régularité de la structure.

## Sous-projets

- [`exercice_arbres/`](./exercice_arbres) — Primitives d'arbre parfait : accès au
  père, aux fils, vérification de feuille, parcours préfixe / infixe /
  postfixe / largeur / par niveau.
- [`exercice_tas/`](./exercice_tas) — Implémentation d'une **file de priorité**
  reposant sur un tas, opérations d'insertion et d'extraction.

## Structure de données

L'arbre parfait est stocké en tableau (l'indice du père et des fils se calcule
arithmétiquement) :

```c
typedef struct {
    int  taille;
    int  tailleMax;
    int *tab;
} ArbreParfait;
```

## Compilation

```bash
cmake -S . -B build
cmake --build build
./build/arbres_parfaits   # arbres parfaits
./build/tas               # tas / file de priorité
```