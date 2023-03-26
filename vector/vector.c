// ------------------------ LIBRERIAS ------------------------

#include "vector.h"

#include <stdlib.h>

#include "../errors/error.h"

// ------------------------ ESTRUCTURA DE DATOS ------------------------

struct VectorSt {
  size_t tamano, capacidad;
  void **lista;
};

// ------------------------ FUNCIONES CONSTRUCTIVAS ------------------------

Vector vector_inicializar(Vector v) {
  __ERROR_CONDICIONAL(v == NULL, "vector_inicializar", "Vector no es NULL");

  v = malloc(sizeof(struct VectorSt));
  __ERROR_CONDICIONAL(v != NULL, "vector_inicializar", "Error con Malloc");

  v->tamano = v->capacidad = 0;
  v->lista = NULL;

  __ERROR_CONDICIONAL(v != NULL, "vector_inicializar",
                      "Error al inicializar el vector");
  return v;
}

void vector_encolar(Vector v, void *el) {
  __ERROR_CONDICIONAL(v != NULL, "vector_encolar", "Vector es NULL");
  __ERROR_CONDICIONAL(el != NULL, "vector_encolar", "Elemento es NULL");

  if (!v->capacidad) {
    v->capacidad = 1;
    v->lista = malloc(sizeof(el));
  } else if (v->capacidad == v->tamano) {
    v->capacidad *= 2;
    v->lista = realloc(v->lista, v->capacidad * sizeof(el));
  }
  __ERROR_CONDICIONAL(v->lista != NULL, "vector_encolar", "Error con Malloc");
  v->lista[v->tamano] = el;
  v->tamano++;

  __ERROR_CONDICIONAL(vector_elemento(v, vector_tamano(v) - 1) == el,
                      "vector_encolar", "Error en encolado del vector");
}

// ------------------------ FUNCIONES DESTRUCTIVAS ------------------------

void vector_liberar(Vector v) {
  for (unsigned int i = 0; i < v->tamano; i++) {
    if (v->lista[i] != NULL) {
      free(v->lista[i]);
      v->lista[i] = NULL;
    }
  }
  free(v->lista);
  v->lista = NULL;
  free(v);
  v = NULL;

  __ERROR_CONDICIONAL(v == NULL, "vector_liberar",
                      "Error en liberación de memoria del vector");
}

// ------------------------ FUNCIONES INFORMATIVAS ------------------------

bool vector_esta_vacio(Vector v) {
  __ERROR_CONDICIONAL(v != NULL, "vector_esta_vacio", "Vector es NULL");

  return !v->tamano;
}

size_t vector_tamano(Vector v) {
  __ERROR_CONDICIONAL(v != NULL, "vector_tamano", "Vector es NULL");

  return v->tamano;
}

void *vector_elemento(Vector v, unsigned int indice) {
  __ERROR_CONDICIONAL(v != NULL, "vector_elemento", "Vector es NULL");
  __ERROR_CONDICIONAL(indice < v->tamano, "vector_elemento",
                      "Índice fuera de rango");

  return v->lista[indice];
}

unsigned int vector_busqueda(Vector v, void *el,
                             int (*cmp)(const void *a, const void *b)) {
  __ERROR_CONDICIONAL(v != NULL, "vector_busqueda", "Vector es NULL");
  __ERROR_CONDICIONAL(el != NULL, "vector_busqueda", "Elemento es NULL");

  unsigned int indice = v->tamano;
  for (unsigned int i = 0; i < v->tamano; i++) {
    if (!cmp(v->lista[i], el)) {
      indice = i;
      break;
    }
  }

  __ERROR_CONDICIONAL(indice == v->tamano || !cmp(v->lista[indice], el),
                      "vector_busqueda", "Error interno");
  return indice;
}

unsigned int vector_busqueda_ordenada(Vector v, void *el,
                                      int (*cmp)(const void *a,
                                                 const void *b)) {
  __ERROR_CONDICIONAL(v != NULL, "vector_busqueda_ordenada", "Vector es NULL");
  __ERROR_CONDICIONAL(el != NULL, "vector_busqueda_ordenada",
                      "Elemento es NULL");

  unsigned int indice = v->tamano;
  unsigned int izq = 0, der = v->tamano;
  while (izq + 1 < der) {
    unsigned int med = (izq + der) / 2;
    int cmp_resultado = cmp(v->lista[med], el);
    if (!cmp_resultado) {
      indice = med;
      break;
    } else if (cmp_resultado < 0)
      izq = med;
    else
      der = med;
  }
  if (!cmp(v->lista[izq], el)) indice = izq;

  __ERROR_CONDICIONAL(indice == v->tamano || !cmp(v->lista[indice], el),
                      "vector_busqueda_ordenada", "Error interno");
  return indice;
}

// ------------------------ FUNCIONES MODIFICATIVAS ------------------------

void vector_asignar(Vector v, void *el, unsigned int indice) {
  __ERROR_CONDICIONAL(v != NULL, "vector_asignar", "Vector es NULL");
  __ERROR_CONDICIONAL(el != NULL, "vector_asignar", "Elemento es NULL");
  __ERROR_CONDICIONAL(indice < v->tamano, "vector_asignar",
                      "Índice fuera de rango");

  free(v->lista[indice]);
  v->lista[indice] = el;

  __ERROR_CONDICIONAL(v->lista[indice] == el, "vector_asignar",
                      "Error interno");
}

static void merge_sort(Vector v, int (*cmp)(const void *a, const void *b),
                       unsigned int izq, unsigned int der) {
  if (izq < der) {
    unsigned int med = (izq + der) / 2;
    merge_sort(v, cmp, izq, med);
    merge_sort(v, cmp, med + 1, der);

    Vector aux = NULL;
    aux = vector_inicializar(aux);
    unsigned int i = izq, j = med + 1;
    while (i <= med && j <= der) {
      if (cmp(v->lista[i], v->lista[j]) <= 0)
        vector_encolar(aux, v->lista[i++]);
      else
        vector_encolar(aux, v->lista[j++]);
    }
    while (i <= med) vector_encolar(aux, v->lista[i++]);
    while (j <= der) vector_encolar(aux, v->lista[j++]);

    __ERROR_CONDICIONAL(
        i == med + 1 && j == der + 1 && aux->tamano == der - izq + 1,
        "vector_ordenar", "Error interno");

    for (unsigned int w = 0; w < aux->tamano; w++)
      v->lista[w + izq] = aux->lista[w];

    free(aux->lista);
    free(aux);
    aux = NULL;
  }
}

void vector_ordenar(Vector v, int (*cmp)(const void *a, const void *b)) {
  __ERROR_CONDICIONAL(v != NULL, "vector_ordenar", "Vector es NULL");

  merge_sort(v, cmp, 0, v->tamano - 1);
}

// ------------------------ FUNCIONES DE ELIMINACIÓN ------------------------

void vector_eliminar_ultimo(Vector v) {
  __ERROR_CONDICIONAL(v != NULL, "vector_eliminar_ultimo", "Vector es NULL");
  __ERROR_CONDICIONAL(v->tamano != 0, "vector_eliminar_ultimo",
                      "Vector está vacío");

  free(v->lista[v->tamano - 1]);
  v->lista[v->tamano - 1] = NULL;
  v->tamano--;
}

void vector_eliminar(Vector v, unsigned int indice) {
  __ERROR_CONDICIONAL(v != NULL, "vector_eliminar", "Vector es NULL");
  __ERROR_CONDICIONAL(v->tamano != 0, "vector_eliminar", "Vector está vacío");
  __ERROR_CONDICIONAL(indice < v->tamano, "vector_eliminar",
                      "Índice fuera de rango");

  free(v->lista[indice]);
  for (unsigned int i = indice; i < v->tamano - 1; i++) {
    v->lista[i] = v->lista[i + 1];
  }
  v->lista[v->tamano - 1] = NULL;

  v->tamano--;
}