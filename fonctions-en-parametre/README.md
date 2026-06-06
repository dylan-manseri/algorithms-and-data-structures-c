# Fonctions en paramètre

Mise en pratique du **passage de fonctions en paramètre** via pointeurs de
fonction en C. On illustre le mécanisme en paramétrant des algorithmes
classiques (recherche, tri fusion) par un **prédicat d'ordre** choisi à
l'exécution.

## Idée

```c
typedef int (*Fcomp)(int, int);

int recherche(int n, int *tab, int elt, Fcomp comp);
void triFusion(int *tab, int indMin, int indSup,
               int *tmp1, int *tmp2, Fcomp fcomp);
```

Le même algorithme produit un tri croissant ou décroissant selon que l'on
passe `estInferieur` ou `estSuperieur`. Les comparaisons sur les
**complexes** se font via le module ; les variantes `estInferieurComp` /
`estSuperieurComp` exposent la même interface mais pour des `Complexe`.

## Compilation

```bash
cmake -S . -B build
cmake --build build
./build/fonctions_en_parametre
```

## Notes

- La sentinelle utilisée par le tri fusion est stockée dans la variable
  globale `VMAX` ; elle doit être réglée plus grande (resp. plus petite)
  que tous les éléments à trier suivant le prédicat utilisé.