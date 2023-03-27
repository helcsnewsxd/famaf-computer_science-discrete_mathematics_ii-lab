#include <stdio.h>
#include <stdlib.h>

#include "../grafo/APIG23.h"

void grafo_print(Grafo g) {
  u32 n = NumeroDeVertices(g);

  printf("Cantidad de nodos: %u\nCantidad de aristas: %u\nDelta: %u\nNodos:\n",
         n, NumeroDeLados(g), Delta(g));

  for (u32 i = 0; i < n; i++) {
    printf("    Nombre: %u\n", Nombre(i, g));

    u32 sz = Grado(i, g);
    printf("    Grado: %u\nVecinos: ", sz);

    for (u32 j = 0; j < sz; j++) {
      u32 x = IndiceVecino(j, i, g);
      u32 y = Nombre(x, g);
      printf("(%u, %u) ", x, y);
    }
    printf("\n================\n");
  }
}

int main(void) {
  Grafo g = NULL;
  g = ConstruirGrafo();
  grafo_print(g);
  DestruirGrafo(g);

  return 0;
}
