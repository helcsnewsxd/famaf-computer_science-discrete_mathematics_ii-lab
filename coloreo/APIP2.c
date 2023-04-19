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
  bool *color_usado = calloc(d + 1, sizeof(bool)),
       *vis = calloc(n, sizeof(bool));
  __ERROR_CONDICIONAL((color_usado != NULL), "Greedy", "Error interno");
  __ERROR_CONDICIONAL((vis != NULL), "Greedy", "Error interno");

  u32 cnt_colores = 1;
  Color[Orden[0]] = 0, vis[Orden[0]] = 1;

  for (u32 indice = 1; indice < n; indice++) {
    const u32 nodo = Orden[indice], grado = Grado(nodo, G);
    vis[nodo] = 1;

    u32 cnt_color_usado = 0;
    memset(color_usado, false, cnt_colores * sizeof(bool));

    for (u32 indiceVec = 0; indiceVec < grado; indiceVec++) {
      const u32 vec = IndiceVecino(indiceVec, nodo, G);
      if (!vis[vec]) continue;

      const u32 color = Color[vec];
      if (!color_usado[color]) cnt_color_usado++, color_usado[color] = 1;
    }

    if (cnt_color_usado == cnt_colores)
      Color[nodo] = cnt_colores++;
    else {
      for (u32 color = 0; color < cnt_colores; color++)
        if (!color_usado[color]) {
          Color[nodo] = color;
          break;
        }
    }
  }

  free(color_usado), free(vis);
  color_usado = vis = NULL;
  __ERROR_CONDICIONAL((cnt_colores <= d + 1), "Greedy", "Error interno");
  __ERROR_CONDICIONAL((EsColoreoPropio(G, Orden, Color)), "Greedy",
                      "El coloreo NO es propio");
  return cnt_colores;
}