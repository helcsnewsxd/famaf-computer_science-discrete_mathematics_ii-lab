#ifndef ERROR_H_
#define ERROR_H_

#include <stdio.h>
#include <stdlib.h>

#define __ERROR_CONDICIONAL(cond, pl, s)         \
  if (!(cond)) {                                 \
    fprintf(stderr, "Error en %s: %s\n", pl, s); \
    exit(EXIT_FAILURE);                          \
  }

#define __ERROR_INPUT_GRAFO(cond, msg)                         \
  if (!(cond)) {                                               \
    fprintf(stderr, "Error en el STDIN del grafo: %s\n", msg); \
    vector_liberar(nombre_nodos_viejo);                        \
    vector_liberar(aristas);                                   \
    return NULL;                                               \
  }

#endif