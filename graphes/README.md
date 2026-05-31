# Graphes et optimisation combinatoire

Projet le plus complet du dépôt, regroupant l'implémentation **from scratch**
des principaux algorithmes de **théorie des graphes** étudiés en Licence 3.

## Sommaire des séances

| Dossier                                                       | Sujet                                                            |
| ------------------------------------------------------------- | ---------------------------------------------------------------- |
| [`01_representations/`](./01_representations)                 | Représentations : matrice d'adjacence, file de successeurs, liste d'adjacence, lecture depuis fichier |
| [`02_parcours/`](./02_parcours)                               | Parcours en profondeur (**DFS**) et en largeur (**BFS**)         |
| [`03_bipartisme_carre/`](./03_bipartisme_carre)               | Carré d'un graphe, marquage et test de bipartisme                |
| [`04_composantes_connexes/`](./04_composantes_connexes)       | Composantes connexes, composantes fortement connexes, fermeture transitive |
| [`05_tri_topologique/`](./05_tri_topologique)                 | Tri topologique d'un graphe acyclique                            |
| [`06_plus_courts_chemins/`](./06_plus_courts_chemins)         | Plus courts chemins : **Dijkstra**, **Bellman-Ford**, **Floyd-Warshall** |
| [`07_flots/`](./07_flots)                                     | Flot maximum : **Ford-Fulkerson**                                |
| [`08_arbres_couvrants/`](./08_arbres_couvrants)               | Arbres couvrants de poids minimal : **Prim** et **Kruskal**      |

## Organisation des sources

```
graphes/
├── CMakeLists.txt
├── main.c                       Point d'entrée
├── graphe.txt                   Exemple de graphe d'entrée
├── include/                     En-têtes (prototypes par séance + structures communes)
├── utils/                       Fonctions transverses (listes, affichage, structures)
└── 0x_<sujet>/                  Un dossier par thématique
```

## Algorithmes implémentés

- **Parcours** : DFS, BFS
- **Décomposition** : composantes connexes, composantes fortement connexes,
  fermeture transitive
- **Tri topologique** sur graphe acyclique
- **Plus courts chemins** :
  - Source unique avec poids positifs : *Dijkstra*
  - Source unique avec poids quelconques : *Bellman-Ford*
  - Toutes paires : *Floyd-Warshall*
- **Flot maximum** : algorithme de *Ford-Fulkerson*
- **Arbres couvrants de poids minimal** : *Prim* et *Kruskal*

## Compilation

```bash
cmake -S . -B build
cmake --build build
./build/graphes
```

Le fichier [`graphe.txt`](./graphe.txt) sert d'entrée par défaut pour les
algorithmes lus depuis fichier.