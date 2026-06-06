# Listes chaînées simples

Implémentation **from scratch** des listes chaînées simples en C, à travers deux
sous-projets indépendants.

## Contenu

- [`exercice1_2_3/`](./exercice1_2_3) — Décomposition en facteurs premiers à
  l'aide d'une liste chaînée associant chaque facteur à son nombre d'occurrences,
  puis calcul du **PGCD** par intersection de deux listes.
- [`exercice3/`](./exercice3) — Travail complémentaire sur les listes chaînées.

## Structures de données

```c
typedef struct cellule {
    FactPremier donnee;        // (facteur premier, nombre d'occurrences)
    struct cellule *suivant;
} *Liste;
```

## Compilation

```bash
cmake -S . -B build
cmake --build build
./build/PGCD
./build/exo3
```