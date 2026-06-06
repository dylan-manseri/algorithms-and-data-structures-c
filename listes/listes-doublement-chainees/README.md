# Listes doublement chaînées — Polynômes

Manipulation de **polynômes** représentés par des **listes doublement chaînées**.
Chaque cellule stocke un monôme (coefficient + degré) et possède un lien vers
le suivant et vers le précédent, ce qui permet d'insérer ou de supprimer en
n'importe quel point en O(1) une fois l'adresse connue.

## Représentations

- **`Polynome`** — liste doublement chaînée « classique » : on accède au
  polynôme par sa tête, chaque cellule connaît ses deux voisins.
- **`PolynomeTQ`** — variante avec accès direct à la **tête** et à la **queue**,
  pour insérer en queue en O(1).

```c
typedef struct {
    double coef;
    int    degre;
} Monome;

typedef struct cellule {
    Monome          monome;
    struct cellule *suivant;
    struct cellule *precedent;
} *Polynome;

typedef struct {
    Polynome tete;
    Polynome queue;
} PolynomeTQ;
```

## Exercices

| Sous-dossier  | Sujet                                                                       |
| ------------- | --------------------------------------------------------------------------- |
| `exercice1/`  | Primitives LDC + opérations algébriques (insertion triée, dérivée, somme)   |
| `exercice2/`  | Variante LDCTQ (tête / queue) — *en cours*                                  |

Les polynômes restent triés par **degré croissant**. Lors d'une insertion, si
un monôme du même degré existe déjà les coefficients sont fusionnés et le
résultat éventuellement nul est supprimé.

## Compilation

```bash
cmake -S . -B build
cmake --build build
./build/listes_doublement_chainees_exo1
./build/listes_doublement_chainees_exo2
```