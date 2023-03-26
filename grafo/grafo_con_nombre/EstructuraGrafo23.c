// ------------------------ LIBRERÍAS (usadas por tipos y TADs)
// ------------------------

#include "EstructuraGrafo23.h"

#include <stdlib.h>

#include "../../errors/error.h"
#include "../../vector/vector.h"
#include "../grafo_simple/grafo_simple.h"

// ------------------------ TIPOS DE DATOS ------------------------

typedef unsigned int u32;

// ------------------------ ESTRUCTURAS DE DATOS ------------------------

/**
 * @brief Estructura de datos del grafo (incluye nombre de los nodos)
 */
struct GrafoSt {
  GrafoSimple g;
  Vector nombre_nodos;
};

// ------------------------ FUNCIONES AUXILIARES ------------------------

static int cmp(const void* a, const void* b) {
  u32 valA = *((int*)a), valB = *((int*)b);
  if (valA < valB)
    return -1;
  else if (valA > valB)
    return 1;
  return 0;
}

// ------------------------ FUNCIONES CONTRUCTIVAS ------------------------

struct GrafoSt* grafo_inicializar(u32 cnt_nodos, Vector nombre_nodos) {
  __ERROR_CONDICIONAL(nombre_nodos != NULL, "grafo_inicializar",
                      "Lista de nombres inválida (es NULL)");

  struct GrafoSt* g = malloc(sizeof(struct GrafoSt));
  __ERROR_CONDICIONAL(g != NULL, "grafo_inicializar", "Error con Malloc");

  g->g = grafo_simple_inicializar(cnt_nodos);

  g->nombre_nodos = nombre_nodos;
  vector_ordenar(g->nombre_nodos, cmp);

  __ERROR_CONDICIONAL(g != NULL, "grafo_inicializar", "Error interno");
  return g;
}

void grafo_anadir_arista(struct GrafoSt* g, u32 nombreNodoI, u32 nombreNodoJ) {
  __ERROR_CONDICIONAL(g != NULL, "grafo_anadir_arista", "Grafo es NULL");

  u32* nombreNodoIP = malloc(sizeof(u32));
  u32* nombreNodoJP = malloc(sizeof(u32));

  *nombreNodoIP = nombreNodoI;
  *nombreNodoJP = nombreNodoJ;

  u32 indiceNodoI =
      vector_busqueda_ordenada(g->nombre_nodos, nombreNodoIP, cmp);
  u32 indiceNodoJ =
      vector_busqueda_ordenada(g->nombre_nodos, nombreNodoJP, cmp);

  free(nombreNodoIP);
  free(nombreNodoJP);

  grafo_simple_anadir_arista(g->g, indiceNodoI, indiceNodoJ);
}

// ------------------------ FUNCIONES DESTRUCTIVAS ------------------------

void grafo_liberar(struct GrafoSt* g) {
  grafo_simple_liberar(g->g);
  vector_liberar(g->nombre_nodos);
  free(g);
  g = NULL;

  __ERROR_CONDICIONAL(g == NULL, "grafo_liberar", "Error interno");
}

// ------------------------ FUNCIONES INFORMATIVAS ------------------------

u32 grafo_cnt_nodos(struct GrafoSt* g) {
  __ERROR_CONDICIONAL(g != NULL, "grafo_cnt_nodos", "Grafo es NULL");

  return grafo_simple_cnt_nodos(g->g);
}

u32 grafo_cnt_aristas(struct GrafoSt* g) {
  __ERROR_CONDICIONAL(g != NULL, "grafo_cnt_aristas", "Grafo es NULL");

  return grafo_simple_cnt_aristas(g->g);
}

u32 grafo_Delta(struct GrafoSt* g) {
  __ERROR_CONDICIONAL(g != NULL, "grafo_Delta", "Grafo es NULL");

  return grafo_simple_Delta(g->g);
}

// ------------------------ FUNCIONES INFORMATIVAS (nodos)
// ------------------------

u32 grafo_nombre_nodo(struct GrafoSt* g, u32 indiceNodo) {
  __ERROR_CONDICIONAL(g != NULL, "grafo_nombre_nodo", "Grafo es NULL");
  __ERROR_CONDICIONAL(indiceNodo < grafo_cnt_nodos(g), "grafo_nombre_nodo",
                      "Índice fuera de rango");

  u32* nombre = (u32*)vector_elemento(g->nombre_nodos, indiceNodo);
  return *nombre;
}

u32 grafo_grado_nodo(struct GrafoSt* g, u32 indiceNodo) {
  __ERROR_CONDICIONAL(g != NULL, "grafo_grado_nodo", "Grafo es NULL");
  __ERROR_CONDICIONAL(indiceNodo < grafo_cnt_nodos(g), "grafo_grado_nodo",
                      "Índice fuera de rango");

  return grafo_simple_grado_nodo(g->g, indiceNodo);
}

u32 grafo_vecino_jesimo_nodo(struct GrafoSt* g, u32 indiceNodo, u32 j) {
  __ERROR_CONDICIONAL(g != NULL, "grafo_vecino_jesimo_nodo", "Grafo es NULL");
  __ERROR_CONDICIONAL(indiceNodo < grafo_cnt_nodos(g),
                      "grafo_vecino_jesimo_nodo", "Índice fuera de rango");
  __ERROR_CONDICIONAL(j < grafo_grado_nodo(g, indiceNodo),
                      "grafo_vecino_jesimo_nodo", "Índice fuera de rango");

  Vector v = grafo_simple_vecinos_nodo(g->g, indiceNodo);
  u32* indiceNodoVec = (u32*)vector_elemento(v, j);

  __ERROR_CONDICIONAL(*indiceNodoVec < grafo_cnt_nodos(g),
                      "grafo_vecino_jesimo_nodo", "Error interno");
  return *indiceNodoVec;
}