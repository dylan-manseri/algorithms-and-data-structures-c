cmake_minimum_required(VERSION 3.20)
project(tris C)

# Tous les exécutables dans cmake-build-xxx/out
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

add_executable(tri_selection tri_selection.c)
add_executable(tri_insertion tri_insertion.c)
add_executable(tri_fusion    tri_fusion.c)
add_executable(tri_rapide    tri_rapide.c)