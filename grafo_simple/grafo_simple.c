#include "grafo_simple.h"

#include <stdio.h>

#include "../errors/error.h"
#include "../vector/vector.h"

// --------------------- ESTRUCTURAS DE DATOS ---------------------

struct NodoSimpleSt {
  unsigned int grado;
  Vector vecinos;
};
typedef struct NodoSimpleSt* NodoSimple;

struct GrafoSimpleSt {
  unsigned int n, m, Delta;
  Vector nodos;
};

// --------------------- FUNCIONES CONSTRUCTORAS ---------------------

GrafoSimple grafo_simple_inicializar(unsigned int cnt_vertices) {
  GrafoSimple gs = malloc(sizeof(struct GrafoSimpleSt));
  __ERROR_CONDICIONAL(gs != NULL, "grafo_simple_inicializar",
                      "Error con Malloc");
  gs->n = cnt_vertices;
  gs->m = gs->Delta = 0;

  gs->nodos = NULL;
  gs->nodos = vector_inicializar(gs->nodos);
  for (unsigned int i = 0; i < cnt_vertices; i++) {
    NodoSimple x = malloc(sizeof(struct NodoSimpleSt));
    __ERROR_CONDICIONAL(x != NULL, "grafo_simple_inicializar",
                        "Error con Malloc");
    x->grado = 0;
    x->vecinos = NULL;
    x->vecinos = vector_inicializar(x->vecinos);

    vector_encolar(gs->nodos, x);
  }

  __ERROR_CONDICIONAL(gs != NULL, "grafo_simple_inicializar", "Error interno");
  return gs;
}

// --------------------- FUNCIONES DESTRUCTORAS ---------------------

void grafo_simple_liberar(GrafoSimple gs) {
  for (unsigned int i = 0; i < gs->n; i++) {
    NodoSimple x = vector_elemento(gs->nodos, i);
    vector_liberar(x->vecinos);
  }
  vector_liberar(gs->nodos);
  free(gs);
  gs = NULL;

  __ERROR_CONDICIONAL(gs == NULL, "grafo_simple_liberar", "Error interno");
}

// --------------------- FUNCIONES INFORMATIVAS ---------------------

unsigned int grafo_simple_cnt_nodos(GrafoSimple gs) {
  __ERROR_CONDICIONAL(gs != NULL, "grafo_simple_cnt_nodos", "Grafo es NULL");

  return gs->n;
}

unsigned int grafo_simple_cnt_aristas(GrafoSimple gs) {
  __ERROR_CONDICIONAL(gs != NULL, "grafo_simple_cnt_aristas", "Grafo es NULL");

  return gs->m;
}

unsigned int grafo_simple_Delta(GrafoSimple gs) {
  __ERROR_CONDICIONAL(gs != NULL, "grafo_simple_Delta", "Grafo es NULL");

  return gs->Delta;
}

// --------------------- FUNCIONES INFORMATIVAS (DE NODOS) ---------------------

Vector grafo_simple_vecinos_nodo(GrafoSimple gs, unsigned int indice) {
  __ERROR_CONDICIONAL(gs != NULL, "grafo_simple_vecinos_nodo", "Grafo es NULL");
  __ERROR_CONDICIONAL(indice < gs->n, "grafo_simple_vecinos_nodo",
                      "Índice fuera de rango");

  NodoSimple x = vector_elemento(gs->nodos, indice);
  Vector v = x->vecinos;

  __ERROR_CONDICIONAL(v != NULL, "grafo_simple_vecinos_nodo", "Error interno");
  return v;
}

unsigned int grafo_simple_grado_nodo(GrafoSimple gs, unsigned int indice) {
  __ERROR_CONDICIONAL(gs != NULL, "grafo_simple_grado_nodo", "Grafo es NULL");
  __ERROR_CONDICIONAL(indice < gs->n, "grafo_simple_grado_nodo",
                      "Índice fuera de rango");

  NodoSimple x = vector_elemento(gs->nodos, indice);
  return x->grado;
}

// --------------------- FUNCIONES MODIFICATIVAS ---------------------

void grafo_simple_anadir_arista(GrafoSimple gs, unsigned int i,
                                unsigned int j) {
  __ERROR_CONDICIONAL(gs != NULL, "grafo_simple_anadir_arista",
                      "Grafo es NULL");
  __ERROR_CONDICIONAL(i < gs->n && j < gs->n, "grafo_simple_anadir_arista",
                      "Índice fuera de rango");

  NodoSimple xi = vector_elemento(gs->nodos, i),
             xj = vector_elemento(gs->nodos, j);

  unsigned int *vecI = malloc(sizeof(unsigned int)),
               *vecJ = malloc(sizeof(unsigned int));
  *vecI = j;
  *vecJ = i;
  vector_encolar(xi->vecinos, vecI);
  vector_encolar(xj->vecinos, vecJ);

  xi->grado++;
  xj->grado++;

  if (gs->Delta < xi->grado) gs->Delta = xi->grado;
  if (gs->Delta < xj->grado) gs->Delta = xj->grado;

  gs->m++;

  __ERROR_CONDICIONAL(gs->m >= 1, "grafo_simple_anadir_arista",
                      "Error interno");
}