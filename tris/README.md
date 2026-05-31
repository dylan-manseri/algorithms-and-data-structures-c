# Algorithmes de tri

Implémentation et **comparaison empirique** des principaux algorithmes de tri en C.

## Algorithmes implémentés

| Fichier             | Algorithme    | Complexité moyenne | Complexité pire cas |
| ------------------- | ------------- | ------------------ | ------------------- |
| `tri_selection.c`   | Tri sélection | O(n²)              | O(n²)               |
| `tri_insertion.c`   | Tri insertion | O(n²)              | O(n²)               |
| `tri_fusion.c`      | Tri fusion    | O(n log n)         | O(n log n)          |
| `tri_rapide.c`      | Tri rapide    | O(n log n)         | O(n²)               |

## Mesures expérimentales

Les exécutables produisent des fichiers de mesures dans [`data/`](./data),
exploitables avec **gnuplot** pour générer les courbes situées dans
[`img/`](./img) :

- `triSelGnuplot.png`
- `triInserGnuplot.png`
- `triFusionGnuplot.png`

## Compilation

```bash
cmake -S . -B build
cmake --build build
./build/out/tri_selection
./build/out/tri_insertion
./build/out/tri_fusion
./build/out/tri_rapide
```