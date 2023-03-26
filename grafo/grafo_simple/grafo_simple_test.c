#include "grafo_simple.h"

#include <stdio.h>

void grafo_simple_print(GrafoSimple gs) {
  unsigned int n = grafo_simple_cnt_nodos(gs);

  printf("Cantidad de nodos: %u\nCantidad de aristas: %u\nDelta: %u\nNodos:\n",
         n, grafo_simple_cnt_aristas(gs), grafo_simple_Delta(gs));

  for (unsigned int i = 0; i < n; i++) {
    unsigned int sz = grafo_simple_grado_nodo(gs, i);
    printf("    Grado: %u\nVecinos: ", sz);

    Vector vec = grafo_simple_vecinos_nodo(gs, i);
    for (unsigned int j = 0; j < sz; j++) {
      unsigned int *x = vector_elemento(vec, j);
      printf("%u ", *x);
    }
    printf("\n================\n");
  }
}

int main() {
  unsigned int n, m;
  scanf("%u %u", &n, &m);

  GrafoSimple gs = grafo_simple_inicializar(n);

  for (unsigned int i = 0; i < m; i++) {
    unsigned int a, b;
    scanf("%u %u", &a, &b);

    grafo_simple_anadir_arista(gs, a, b);
  }

  grafo_simple_print(gs);

  grafo_simple_liberar(gs);

  return 0;
}