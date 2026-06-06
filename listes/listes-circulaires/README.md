# Listes chaînées circulaires

Étude de deux représentations distinctes des **listes circulaires** en C.

## Représentations

- **`ListeC`** — liste circulaire simple : on accède à la liste par un pointeur
  unique, le dernier élément pointe sur le premier.
- **`ListeCTQ`** — liste circulaire avec accès direct à la **tête** et à la
  **queue**, ainsi qu'à la **taille** courante, pour un accès O(1) aux deux
  extrémités.

```c
typedef struct cel {
    int elt;
    struct cel *suivant;
} *ListeC;

typedef struct {
    int     taille;
    ListeC  tete;
    ListeC  queue;
} ListeCTQ;
```

## Compilation

```bash
cmake -S . -B build
cmake --build build
./build/listes_circulaires
```