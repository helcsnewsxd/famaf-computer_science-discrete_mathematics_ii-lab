#include "../vector/vector.h"

#include <stdio.h>
#include <stdlib.h>

// ------------------------ TEST 1 ------------------------

bool test1_ordenado = false;

int cmp_test1(const void *a, const void *b) {
  int ret = *((int *)a) - *((int *)b);
  if (ret < 0)
    return -1;
  else if (ret > 0)
    return 1;
  else
    return 0;
}

void vector_print_test1(Vector v) {
  size_t sz = vector_tamano(v);
  printf("Tamaño -> %ld\nEstá vacío? -> %d\nElementos:\n{ ", sz,
         vector_esta_vacio(v));
  for (unsigned int i = 0; i < sz; i++) {
    if (i) printf(", ");

    int *x = vector_elemento(v, i);
    printf("%d", *x);
  }
  if (test1_ordenado)
    printf(" }\nOrdenado:\n{ ");
  else
    printf(" }\nLineal:\n{ ");
  for (unsigned int i = 0; i < sz; i++) {
    if (i) printf(", ");

    int *x = vector_elemento(v, i);
    if (test1_ordenado)
      printf("%u", vector_busqueda_ordenada(v, x, cmp_test1));
    else
      printf("%u", vector_busqueda(v, x, cmp_test1));
  }
  printf(" }\n------------------------- \n");
}

void test1() {
  printf(" ======================= TEST1 ======================= \n");
  Vector v = NULL;
  v = vector_inicializar(v);

  int lista_test1[10] = {9, 8, 7, 1, 2, 3, 5, 6, 4, 0};
  for (unsigned int i = 0; i < 10; i++) {
    int *x = malloc(sizeof(int));
    *x = lista_test1[i];
    vector_encolar(v, x);
  }
  vector_print_test1(v);

  int *x0 = malloc(sizeof(int));
  *x0 = -100;
  vector_asignar(v, x0, 0);
  vector_print_test1(v);

  vector_eliminar(v, 2);
  vector_print_test1(v);

  vector_eliminar_ultimo(v);
  vector_print_test1(v);

  vector_ordenar(v, cmp_test1);
  test1_ordenado = true;
  vector_print_test1(v);

  vector_liberar(v);
}

// ------------------------ TEST 2 ------------------------

bool test2_ordenado = false;

struct NodoSt {
  int x, y;
  Vector lista;
};
typedef struct NodoSt *Nodo;

int cmp_test2(const void *a, const void *b) {
  int ret = (*((Nodo)a)).y - (*((Nodo)b)).y;
  if (ret < 0)
    return -1;
  else if (ret > 0)
    return 1;
  else
    return 0;
}

void vector_print_test2(Vector v) {
  size_t sz = vector_tamano(v);
  printf("Tamaño -> %ld\nEstá vacío? -> %d\nElementos:\n{ ", sz,
         vector_esta_vacio(v));
  for (unsigned int i = 0; i < sz; i++) {
    if (i) printf(", ");

    Nodo x = vector_elemento(v, i);
    printf("{ %d, %d, \n[\n", x->x, x->y);

    vector_print_test1(x->lista);
    printf(" ]\n");
  }
  printf(" }\n------------------------- \n\n\n");
}

void test2() {
  printf(" ======================= TEST2 ======================= \n");
  Vector v = NULL;
  v = vector_inicializar(v);

  struct NodoSt lista_test1[10] = {
      {1002, 9, NULL}, {-1, 8, NULL}, {-1, 7, NULL}, {-1, 1, NULL},
      {-1, 2, NULL},   {-1, 3, NULL}, {-1, 5, NULL}, {-1, 6, NULL},
      {0, 4, NULL},    {0, 0, NULL}};
  for (unsigned int i = 0; i < 10; i++) {
    Nodo x = malloc(sizeof(struct NodoSt));
    *x = lista_test1[i];
    x->lista = NULL;
    x->lista = vector_inicializar(x->lista);
    vector_encolar(v, x);
  }
  vector_print_test2(v);

  Nodo x0 = malloc(sizeof(struct NodoSt));
  x0->x = 12445435;
  x0->y = -14335;
  x0->lista = NULL;
  x0->lista = vector_inicializar(x0->lista);
  for (unsigned int i = 0; i < 10; i += 2) {
    int *x = malloc(sizeof(int));
    *x = i;
    vector_encolar(x0->lista, x);
  }
  Nodo x1 = vector_elemento(v, 0);
  vector_liberar(x1->lista);
  vector_asignar(v, x0, 0);
  vector_print_test2(v);

  x1 = vector_elemento(v, 2);
  vector_liberar(x1->lista);
  vector_eliminar(v, 2);
  vector_print_test2(v);

  x1 = vector_elemento(v, vector_tamano(v) - 1);
  vector_liberar(x1->lista);
  vector_eliminar_ultimo(v);
  vector_print_test2(v);

  vector_ordenar(v, cmp_test2);
  vector_print_test2(v);

  for (unsigned int i = 0; i < vector_tamano(v); i++) {
    Nodo x = vector_elemento(v, i);
    vector_liberar(x->lista);
  }
  vector_liberar(v);
}

int main() {
  test1();
  test1_ordenado = false;
  test2();
}