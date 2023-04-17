#include "APIP2.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __ERROR_CONDICIONAL(cond, pl, s)         \
  if (!(cond)) {                                 \
    fprintf(stderr, "Error en %s: %s\n", pl, s); \
    return ERROR;                                \
  }

static void SetearArray(u32* array, u32 n, u32 val) {
  for (u32 i = 0; i < n; i++) array[i] = val;
}

static bool EsColoreoPropio(Grafo G, u32* Orden, u32* Color) {
  const u32 n = NumeroDeVertices(G);

  for (u32 indice = 0; indice < n; indice++) {
    const u32 nodo = Orden[indice], grado = Grado(nodo, G),
              colorNodo = Color[nodo];
    for (u32 indiceVec = 0; indiceVec < grado; indiceVec++) {
      const u32 vec = IndiceVecino(indiceVec, nodo, G), colorVec = Color[vec];
      if (colorNodo == colorVec) return 0;
    }
  }
  return 1;
}

// Se asume SZ(Orden) = SZ(Color) = NumeroDeVertices(G) = n
// Por enunciado, NO se verifica
u32 Greedy(Grafo G, u32* Orden, u32* Color) {
  const u32 ERROR = (1LL << 32) - 1, n = NumeroDeVertices(G), d = Delta(G);
  SetearArray(Color, n, ERROR);

  u32 cnt_colores = 0;

  for (u32 indice = 0; indice < n; indice++) {
    const u32 nodo = Orden[indice], grado = Grado(nodo, G);
    bool* color_usado = calloc(d + 1, sizeof(bool));
    __ERROR_CONDICIONAL((color_usado != NULL), "Greedy", "Error interno");

    for (u32 indiceVec = 0; indiceVec < grado; indiceVec++) {
      const u32 vec = IndiceVecino(indiceVec, nodo, G), color = Color[vec];
      if (color != ERROR) color_usado[color] = 1;
    }

    Color[nodo] = 0;
    for (u32 color = 0; color < d + 1; color++)
      if (!color_usado[color]) {
        Color[nodo] = color;
        break;
      }

    if (cnt_colores < Color[nodo] + 1) cnt_colores = Color[nodo] + 1;

    free(color_usado);
    color_usado = NULL;
  }

  __ERROR_CONDICIONAL((EsColoreoPropio(G, Orden, Color)), "Greedy",
                      "El coloreo NO es propio");
  return cnt_colores;
}