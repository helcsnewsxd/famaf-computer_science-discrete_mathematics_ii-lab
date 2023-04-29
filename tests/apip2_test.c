#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../coloreo/APIParte2.h"

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

  free(Orden);

  printf("RESPUESTA --------> %d\n", cnt_col[0]);

  // PARTE ORDEN IMPAR PAR

  Orden = calloc(n, sizeof(u32));
  for (u32 i = 0; i < n; i++) Orden[i] = i;

  clock_t inicio, fin;

  char resultado = OrdenImparPar(n, Orden, Color);
  if (resultado != 0) {
    exit(EXIT_FAILURE);
  }

  inicio = clock();
  u32 cant_colores = Greedy(G, Orden, Color);
  fin = clock();
  double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
  printf("GREEDY CON ORDEN IMPAR PAR TARDA --> %f\n", tiempo);
  printf("RESPUESTA --------> %d\n", cant_colores);

  DestruirGrafo(G);
  free(Orden), free(Color);
  Orden = Color = NULL;

  // PARTE TEST CASERO APARTE

  printf("\nTEST CASERO PARA COMPROBAR ORDEN DE IMPAR PAR:\n");

  n = 11;
  Color = (u32 *)malloc(11 * sizeof(u32));
  Color[0] = 2;
  Color[1] = 3;
  Color[2] = 5;
  Color[3] = 1;
  Color[4] = 4;
  Color[5] = 6;
  Color[6] = 7;
  Color[7] = 9;
  Color[8] = 8;
  Color[9] = 0;
  Color[10] = 10;
  Orden = (u32 *)malloc(11 * sizeof(u32));
  resultado = OrdenImparPar(n, Orden, Color);

  if (resultado == 0) {
    printf("Indices ordenados: ");
    for (u32 i = 0; i < n; i++) {
      printf("%u ", Orden[i]);
    }
  } else {
    printf("Ocurrió un error al ordenar los índices.");
  }
  printf("\n");

  free(Color);
  free(Orden);
  Color = NULL;
  Orden = NULL;

  return 0;
}

/**
p edge 5 4
e 1 2
e 2 3
e 3 4
e 4 5
*/