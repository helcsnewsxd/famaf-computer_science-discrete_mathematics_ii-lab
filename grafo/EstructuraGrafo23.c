#include "EstructuraGrafo23.h"

#include <stdio.h>

#include "../errors/error.h"
#include "../vector/vector.h"

// --------------------- ESTRUCTURAS DE DATOS ---------------------

struct NodoSt {
  u32 grado;
  Vector vecinos;
};
typedef struct NodoSt* Nodo;

struct GrafoStAux {
  u32 n, m, Delta;
  Vector nodos, nombre_nodos;
};

// --------------------- FUNCIONES CONSTRUCTORAS ---------------------

GrafoSt* grafo_inicializar(u32 cnt_vertices, Vector nombre_nodos) {
  GrafoSt* g = malloc(sizeof(struct GrafoStAux));
  __ERROR_CONDICIONAL(g != NULL, "grafo_inicializar", "Error con Malloc");
  g->n = cnt_vertices;
  g->m = g->Delta = 0;

  g->nodos = NULL;
  g->nodos = vector_inicializar(g->nodos);
  for (u32 i = 0; i < cnt_vertices; i++) {
    Nodo x = malloc(sizeof(struct NodoSt));
    __ERROR_CONDICIONAL(x != NULL, "grafo_inicializar", "Error con Malloc");
    x->grado = 0;
    x->vecinos = NULL;
    x->vecinos = vector_inicializar(x->vecinos);

    vector_encolar(g->nodos, x);
  }

  g->nombre_nodos = nombre_nodos;

  __ERROR_CONDICIONAL(g != NULL, "grafo_inicializar", "Error interno");
  return g;
}

void grafo_anadir_arista(GrafoSt* g, u32 i, u32 j) {
  __ERROR_CONDICIONAL(g != NULL, "grafo_anadir_arista", "Grafo es NULL");
  __ERROR_CONDICIONAL(i < g->n && j < g->n, "grafo_anadir_arista",
                      "Índice fuera de rango");

  Nodo xi = vector_elemento(g->nodos, i), xj = vector_elemento(g->nodos, j);

  u32 *vecI = malloc(sizeof(u32)), *vecJ = malloc(sizeof(u32));
  *vecI = j;
  *vecJ = i;
  vector_encolar(xi->vecinos, vecI);
  vector_encolar(xj->vecinos, vecJ);

  xi->grado++;
  xj->grado++;

  if (g->Delta < xi->grado) g->Delta = xi->grado;
  if (g->Delta < xj->grado) g->Delta = xj->grado;

  g->m++;

  __ERROR_CONDICIONAL(g->m >= 1, "grafo_anadir_arista", "Error interno");
}

// --------------------- FUNCIONES DESTRUCTORAS ---------------------

void grafo_liberar(GrafoSt* g) {
  for (u32 i = 0; i < g->n; i++) {
    Nodo x = vector_elemento(g->nodos, i);
    vector_liberar(x->vecinos);
  }
  vector_liberar(g->nodos);
  vector_liberar(g->nombre_nodos);
  free(g);
  g = NULL;

  __ERROR_CONDICIONAL(g == NULL, "grafo_liberar", "Error interno");
}

// --------------------- FUNCIONES INFORMATIVAS ---------------------

u32 grafo_cnt_nodos(GrafoSt* g) {
  __ERROR_CONDICIONAL(g != NULL, "grafo_cnt_nodos", "Grafo es NULL");

  return g->n;
}

u32 grafo_cnt_aristas(GrafoSt* g) {
  __ERROR_CONDICIONAL(g != NULL, "grafo_cnt_aristas", "Grafo es NULL");

  return g->m;
}

u32 grafo_Delta(GrafoSt* g) {
  __ERROR_CONDICIONAL(g != NULL, "grafo_Delta", "Grafo es NULL");

  return g->Delta;
}

// --------------------- FUNCIONES INFORMATIVAS (DE NODOS) ---------------------

u32 grafo_nombre_nodo(GrafoSt* g, u32 indiceNodo) {
  __ERROR_CONDICIONAL(g != NULL, "grafo_nombre_nodo", "Grafo es NULL");
  __ERROR_CONDICIONAL(indiceNodo < grafo_cnt_nodos(g), "grafo_nombre_nodo",
                      "Índice fuera de rango");

  u32* nombre = (u32*)vector_elemento(g->nombre_nodos, indiceNodo);
  return *nombre;
}

u32 grafo_grado_nodo(GrafoSt* g, u32 indice) {
  __ERROR_CONDICIONAL(g != NULL, "grafo_grado_nodo", "Grafo es NULL");
  __ERROR_CONDICIONAL(indice < g->n, "grafo_grado_nodo",
                      "Índice fuera de rango");

  Nodo x = vector_elemento(g->nodos, indice);
  return x->grado;
}

u32 grafo_vecino_jesimo_nodo(GrafoSt* g, u32 indiceNodo, u32 j) {
  __ERROR_CONDICIONAL(g != NULL, "grafo_vecino_jesimo_nodo", "Grafo es NULL");
  __ERROR_CONDICIONAL(indiceNodo < grafo_cnt_nodos(g),
                      "grafo_vecino_jesimo_nodo", "Índice fuera de rango");
  __ERROR_CONDICIONAL(j < grafo_grado_nodo(g, indiceNodo),
                      "grafo_vecino_jesimo_nodo", "Índice fuera de rango");

  Nodo v = (Nodo)vector_elemento(g->nodos, indiceNodo);
  u32* indiceNodoVec = (u32*)vector_elemento(v->vecinos, j);

  __ERROR_CONDICIONAL(*indiceNodoVec < grafo_cnt_nodos(g),
                      "grafo_vecino_jesimo_nodo", "Error interno");
  return *indiceNodoVec;
}