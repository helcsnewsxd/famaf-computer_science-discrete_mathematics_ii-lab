#ifndef ERROR_H_
#define ERROR_H_

#include <stdio.h>
#include <stdlib.h>

#define __CONDITION_ERROR(cond, pl, s)             \
  if (!cond) {                                     \
    fprintf(stderr, "Error into %s: %s\n", pl, s); \
    exit(EXIT_FAILURE);                            \
  }

#endif