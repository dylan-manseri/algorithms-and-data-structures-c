# Arbres

Regroupe l'ensemble des TP autour des **arbres** en C.
Chaque sous-dossier est un projet CMake autonome.

| Sous-dossier                                              | Structure étudiée                       |
| --------------------------------------------------------- | --------------------------------------- |
| [`arbres-binaires/`](./arbres-binaires)                   | Arbres binaires (parcours, expression)  |
| [`arbres-parfaits-et-tas/`](./arbres-parfaits-et-tas)     | Arbres parfaits, tas, file de priorité  |

## Compilation

```bash
cd <sous-dossier>
cmake -S . -B build
cmake --build build
```