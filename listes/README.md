# Listes chaînées

Regroupe l'ensemble des TP autour des **listes chaînées** en C.
Chaque sous-dossier est un projet CMake autonome.

| Sous-dossier                                                | Représentation                  |
| ----------------------------------------------------------- | ------------------------------- |
| [`listes-chainees/`](./listes-chainees)                     | Liste simplement chaînée         |
| [`listes-circulaires/`](./listes-circulaires)               | Liste circulaire (LC, LCTQ)      |
| [`listes-doublement-chainees/`](./listes-doublement-chainees) | Liste doublement chaînée (polynômes) |

## Compilation

```bash
cd <sous-dossier>
cmake -S . -B build
cmake --build build
```