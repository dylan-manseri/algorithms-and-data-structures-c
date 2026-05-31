# Algorithmique et structures de données — Travaux pratiques

![Langage](https://img.shields.io/badge/langage-C-blue.svg)
![Build](https://img.shields.io/badge/build-CMake-brightgreen.svg)
![Niveau](https://img.shields.io/badge/niveau-Licence%203-orange.svg)

Ce dépôt regroupe l'ensemble des travaux pratiques réalisés en **Licence Informatique**
autour de l'algorithmique, des structures de données fondamentales et des graphes.
Chaque dossier correspond à un thème distinct et contient son propre `CMakeLists.txt`
afin d'être compilé de manière autonome.

---

## Sommaire

| Dossier                                                    | Thème                       | Notions clés                                 |
| ---------------------------------------------------------- | --------------------------- | -------------------------------------------- |
| [`listes-chainees/`](./listes-chainees)                    | Listes chaînées simples     | Cellules, primitives, manipulation par tête  |
| [`listes-circulaires/`](./listes-circulaires)              | Listes chaînées circulaires | Représentations LC et LCTQ (tête/queue)      |
| [`tris/`](./tris)                                          | Algorithmes de tri          | Sélection, insertion, fusion, rapide         |
| [`arbres-binaires/`](./arbres-binaires)                    | Arbres binaires             | Parcours, arbres d'expression, pile          |
| [`arbres-parfaits-et-tas/`](./arbres-parfaits-et-tas)      | Arbres parfaits & tas       | File de priorité, structure tableau          |
| [`graphes/`](./graphes)                                    | Graphes & optimisation      | Parcours, plus court chemin, flots, ACM      |

---

## Notions abordées

- **Structures de données** : listes chaînées (simples, circulaires), piles, arbres binaires, arbres parfaits, tas, graphes (matrice d'adjacence, liste d'adjacence)
- **Algorithmes de tri** : tri par sélection, par insertion, fusion, rapide
- **Parcours d'arbres** : préfixe, infixe, postfixe, en largeur
- **Algorithmes sur graphes** :
  - Parcours en largeur (BFS) et en profondeur (DFS)
  - Plus courts chemins : **Dijkstra**, **Bellman-Ford**, **Floyd-Warshall**
  - Problèmes de flots : **Ford-Fulkerson**
  - Arbres couvrants de poids minimal : **Prim**, **Kruskal**
- **Récursivité** et **fonctions de haut niveau**

---

## Compilation et exécution

Chaque TP est un projet CMake indépendant. Pour compiler l'un d'entre eux :

```bash
cd <nom-du-dossier>
cmake -S . -B build
cmake --build build
./build/<nom-de-l-executable>
```

**Exemple** — compiler et exécuter le TP sur les graphes :

```bash
cd graphes
cmake -S . -B build
cmake --build build
./build/graphes
```

---

## Organisation type d'un TP

```
<theme>/
├── CMakeLists.txt        Configuration de build
├── README.md             Description du TP
├── include/              En-têtes (.h)
├── utils/                Fonctions transverses
└── TDx/                  Sous-dossiers par séance
```

---

## Objectif pédagogique

Renforcer la compréhension des mécanismes algorithmiques et développer
une logique de résolution structurée à travers une implémentation **from scratch**
des structures de données et algorithmes classiques en langage C.

---

## Auteur

**Dylan Manseri** — Licence Informatique