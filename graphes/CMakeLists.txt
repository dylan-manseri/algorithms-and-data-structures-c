cmake_minimum_required(VERSION 3.20)

project(graphes C)

set(CMAKE_C_STANDARD 23)

add_executable(graphes
        main.c

        # En-têtes communs
        include/structure.h
        include/prototype_td3.h
        include/prototype_td4.h
        include/prototype_td5.h
        include/prototype_td6.h
        include/prototype_td7.h
        include/prototype_td8.h
        include/prototype_td9.h
        include/prototype_td12.h

        # Utilitaires
        utils/print.c
        utils/fonctions_liste.c
        utils/fonctions_struct.c

        # Représentations (matrice, file de successeurs, liste d'adjacence)
        01_representations/main_td1_2.c
        01_representations/partie_td/exo3.c
        01_representations/partie_td/exo4.c
        01_representations/partie_tp/alloc_lib.c
        01_representations/partie_tp/fichiers.c

        # Parcours en profondeur (DFS) et en largeur (BFS)
        02_parcours/main_td3.c
        02_parcours/exo4.c

        # Carré d'un graphe et test de bipartisme
        03_bipartisme_carre/main_td4.c
        03_bipartisme_carre/partie_tp.c

        # Composantes connexes, composantes fortement connexes, fermeture transitive
        04_composantes_connexes/main_td5.c
        04_composantes_connexes/partie_tp.c

        # Tri topologique
        05_tri_topologique/main_td6.c
        05_tri_topologique/partie_tp.c

        # Plus courts chemins — Dijkstra, Bellman-Ford, Floyd-Warshall
        06_plus_courts_chemins/main_td7.c
        06_plus_courts_chemins/partie_tp.c

        # Flot maximum — Ford-Fulkerson
        07_flots/partie_tp.c

        # Arbres couvrants de poids minimal — Prim et Kruskal
        08_arbres_couvrants/partie_tp.c
)