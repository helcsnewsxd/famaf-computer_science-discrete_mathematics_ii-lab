#include "EstructuraGrafo23.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../vector/vector.h"

typedef struct GrafoSt* Grafo;

void grafo_print(Grafo g) {
  u32 n = grafo_cnt_nodos(g);

  printf("Cantidad de nodos: %u\nCantidad de aristas: %u\nDelta: %u\nNodos:\n",
         n, grafo_cnt_aristas(g), grafo_Delta(g));

  for (u32 i = 0; i < n; i++) {
    printf("    Nombre: %u\n", grafo_nombre_nodo(g, i));

    u32 sz = grafo_grado_nodo(g, i);
    printf("    Grado: %u\nVecinos: ", sz);

    for (u32 j = 0; j < sz; j++) {
      u32 x = grafo_vecino_jesimo_nodo(g, i, j);
      u32 y = grafo_nombre_nodo(g, x);
      printf("(%u, %u) ", x, y);
    }
    printf("\n================\n");
  }
}

int main() {
  u32 n, m;
  scanf("%u %u", &n, &m);

  Vector nombre_nodos = NULL;
  nombre_nodos = vector_inicializar(nombre_nodos);

  for (u32 i = 0; i < n; i++) {
    u32* nombre = malloc(sizeof(u32));
    scanf("%u", &(*nombre));
    vector_encolar(nombre_nodos, nombre);
  }

  Grafo g = grafo_inicializar(n, nombre_nodos);

  for (u32 i = 0; i < m; i++) {
    u32 a, b;
    scanf("%u %u", &a, &b);

    grafo_anadir_arista(g, a, b);
  }

  grafo_print(g);

  grafo_liberar(g);

  return 0;
}

/**
  5 6
  100 200 1 2 999
  100 1
  200 2
  200 1
  1 2
  999 2
  999 1
*/