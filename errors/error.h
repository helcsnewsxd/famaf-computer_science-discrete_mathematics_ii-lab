#ifndef ERROR_H_
#define ERROR_H_

#include <stdio.h>
#include <stdlib.h>

#define __ERROR_CONDICIONAL(cond, pl, s)         \
  if (!(cond)) {                                 \
    fprintf(stderr, "Error en %s: %s\n", pl, s); \
    exit(EXIT_FAILURE);                          \
  }

#endif
