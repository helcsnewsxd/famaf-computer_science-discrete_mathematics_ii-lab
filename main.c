#include <stdbool.h>
#include <stdio.h>

#include "coloreo/APIParte2.h"

#define __ERROR_MAIN(cond, pl, s)                \
  if (!(cond)) {                                 \
    fprintf(stderr, "Error en %s: %s\n", pl, s); \
    exit(EXIT_FAILURE);                          \
  }

typedef struct Coloreo_s {
  u32* Orden;
  u32* Color;
} Coloreo;

Coloreo* CrearColoreo(u32 n) {
  Coloreo* ret = malloc(sizeof(Coloreo));
  __ERROR_MAIN(ret != NULL, "CrearColoreo", "Error con malloc");
  ret->Orden = calloc(n, sizeof(u32));
  ret->Color = calloc(n, sizeof(u32));
  __ERROR_MAIN(ret->Color != NULL && ret->Orden != NULL, "CrearColoreo",
               "Error con malloc");

  for (u32 i = 0; i < n; i++) ret->Orden[i] = i;

  return ret;
}

void LiberarColoreo(Coloreo* c) {
  free(c->Color);
  free(c->Orden);
  free(c);
  c = NULL;
}

u32 min(const u32 a, const u32 b) { return a < b ? a : b; }

int main(void) {
  Grafo G = NULL;
  G = ConstruirGrafo();
  u32 n = NumeroDeVertices(G);

  u32 aproxChi = (1LL << 32) - 1, greedyCol;
  const u32 ERROR = (1LL << 32) - 1;

  // Inicialización de los Coloreos con el orden natural
  Coloreo** cols = calloc(2, sizeof(Coloreo*));
  for (u32 i = 0; i < 2; i++) {
    cols[i] = CrearColoreo(n);
    greedyCol = Greedy(G, cols[i]->Orden, cols[i]->Color);
    __ERROR_MAIN(greedyCol != ERROR, "main", "Error con greedy");
    aproxChi = min(aproxChi, greedyCol);
  }

  // Algoritmo pedido
  bool estrategia = 0;
  char retorno;
  for (u32 i = 0; i < 500; i++) {
    // Se swapean los arrays de coloreo y orden según corresponda
    if (i != 0 && i % 16 == 0) estrategia ^= 1;

    // Estrategia 1
    retorno =
        OrdenImparPar(n, cols[estrategia]->Orden, cols[estrategia]->Color);
    __ERROR_MAIN(retorno == 0, "main", "Error con Orden Impar Par");

    greedyCol = Greedy(G, cols[estrategia]->Orden, cols[estrategia]->Color);
    __ERROR_MAIN(greedyCol != ERROR, "main", "Error con greedy");
    aproxChi = min(aproxChi, greedyCol);

    // Estrategia 2
    retorno = OrdenJedi(G, cols[!estrategia]->Orden, cols[!estrategia]->Color);
    __ERROR_MAIN(retorno == 0, "main", "Error con Orden Jedi");

    greedyCol = Greedy(G, cols[!estrategia]->Orden, cols[!estrategia]->Color);
    __ERROR_MAIN(greedyCol != ERROR, "main", "Error con greedy");
    aproxChi = min(aproxChi, greedyCol);
  }

  // Se imprime el chi aproximado obtenido
  printf("%u\n", aproxChi);

  for (u32 i = 0; i < 2; i++) LiberarColoreo(cols[i]);
  free(cols);
  cols = NULL;

  DestruirGrafo(G);

  return 0;
}