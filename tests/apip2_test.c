#include "../coloreo/APIP2.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  u32 t0, t1;

  t0 = clock();
  Grafo G = NULL;
  G = ConstruirGrafo();
  t1 = clock();
  printf("CONSTRUCCION DEL GRAFO TARDA --> %f\n",
         (double)(t1 - t0) / CLOCKS_PER_SEC);

  u32 n = NumeroDeVertices(G);
  u32 *Orden = calloc(n, sizeof(u32)), *Color = calloc(n, sizeof(u32));
  for (u32 i = 0; i < n; i++) Orden[i] = i;
  u32 cnt_col[2] = {n, 0};
  u32 cnt_jedi = 1;
  t0 = clock();
  for (u32 i = 0; i < cnt_jedi; i++) {
    cnt_col[1] = Greedy(G, Orden, Color);
    assert(cnt_col[0] >= cnt_col[1]);
    cnt_col[0] = cnt_col[1];
    OrdenJedi(G, Orden, Color);
  }
  t1 = clock();
  printf("GREEDY CON %d ORDEN JEDI TARDA --> %f\n", cnt_jedi,
         (double)(t1 - t0) / CLOCKS_PER_SEC);

  free(Orden), free(Color);
  Orden = Color = NULL;
  DestruirGrafo(G);

  printf("RESPUESTA --------> %d\n", cnt_col[0]);

  return 0;
}

/**
p edge 5 4
e 1 2
e 2 3
e 3 4
e 4 5
*/