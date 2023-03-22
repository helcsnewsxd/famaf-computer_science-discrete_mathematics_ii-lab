#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

// ------------------------ TEST 1 ------------------------

int cmp_test1(const void *a, const void *b) {
  int A = *(int *)a, B = *(int *)b;
  if (A < B)
    return -1;
  else if (A == B)
    return 0;
  return 1;
}

void print_vector_test1(Vector v, int b) {
  printf("Size -> %lu\nIsEmpty -> %u\nElements:\n   {", vector_size(v),
         vector_is_empty(v));
  for (unsigned int i = 0; i < vector_size(v); i++) {
    if (i != 0) printf(", ");
    int *x = (int *)vector_element(v, i);
    printf("%d", (*x));
    free(x);
  }
  printf("}\n-----------------------------------------------------\n");
  if (b == 0)
    printf("Simple search\n{");
  else
    printf("Ordered search\n{");
  for (unsigned int i = 0; i < vector_size(v); i++) {
    if (i != 0) printf(", ");
    int *x = (int *)vector_element(v, i);
    if (b == 0)
      printf("%u", vector_search(v, x, cmp_test1));
    else
      printf("%u", vector_sorted_search(v, x, cmp_test1));
    free(x);
  }
  printf(
      "}\n=================================================================="
      "\n");
}

void test1() {
  Vector v = NULL;
  v = vector_initialize(v);

  int arr0[10] = {-1, 5, 3, 7, -1435, 134364745, 0, 0, 1, 3};
  for (unsigned int i = 0; i < 10; i++) {
    int *x = malloc(sizeof(int));
    *x = arr0[i];
    vector_push_back(v, (void *)x);
    free(x);
  }
  print_vector_test1(v, 0);

  int *y = malloc(sizeof(int));
  *y = 1500000;
  vector_assign(v, y, 0);
  free(y);
  print_vector_test1(v, 0);

  vector_pop_back(v);
  print_vector_test1(v, 0);

  vector_erase(v, 2);
  print_vector_test1(v, 0);

  vector_erase(v, 0);
  print_vector_test1(v, 0);

  vector_erase(v, vector_size(v) - 1);
  print_vector_test1(v, 0);

  for (unsigned int i = 0; i < 10; i++) {
    int *x = malloc(sizeof(int));
    *x = arr0[i];
    vector_push_back(v, (void *)x);
    free(x);
  }
  print_vector_test1(v, 0);

  while (vector_size(v) > 3) vector_pop_back(v);
  print_vector_test1(v, 0);

  vector_merge_sort(v, cmp_test1);
  print_vector_test1(v, 1);

  vector_free(v);
}

// ------------------------ TEST 2 ------------------------

typedef struct PairSt {
  int x, y;
} pair;

int cmp_test2(const void *a, const void *b) {
  pair *A = (pair *)a, *B = (pair *)b;
  int *Ax = malloc(sizeof(int));
  *Ax = (*A).x;
  int *Ay = malloc(sizeof(int));
  *Ay = (*A).y;
  int *Bx = malloc(sizeof(int));
  *Bx = (*B).x;
  int *By = malloc(sizeof(int));
  *By = (*B).y;

  int cmp1 = cmp_test1((void *)Ax, (void *)Bx),
      cmp2 = cmp_test1((void *)Ay, (void *)By);

  free(Ax);
  free(Ay);
  free(Bx);
  free(By);

  if (cmp1 == 0)
    return cmp2;
  else
    return cmp1;
}

void print_vector_test2(Vector v, int b) {
  printf("Size -> %lu\nIsEmpty -> %u\nElements:\n   {", vector_size(v),
         vector_is_empty(v));
  for (unsigned int i = 0; i < vector_size(v); i++) {
    if (i != 0) printf(", ");
    pair *x = (pair *)vector_element(v, i);
    printf("{%d, %d}", (*x).x, (*x).y);
    free(x);
  }
  printf("}\n-----------------------------------------------------\n");
  if (b == 0)
    printf("Simple search\n{");
  else
    printf("Ordered search\n{");
  for (unsigned int i = 0; i < vector_size(v); i++) {
    if (i != 0) printf(", ");
    pair *x = (pair *)vector_element(v, i);
    if (b == 0)
      printf("%u", vector_search(v, x, cmp_test2));
    else
      printf("%u", vector_sorted_search(v, x, cmp_test2));
    free(x);
  }
  printf(
      "}\n=================================================================="
      "\n");
}

void test2() {
  Vector v = NULL;
  v = vector_initialize(v);

  pair arr0[10] = {{-1, 0},        {-1435, 1}, {3, 2}, {7, -99999}, {-1435, 4},
                   {134364745, 5}, {0, 6},     {0, 7}, {1, 8},      {3, 9}};
  for (unsigned int i = 0; i < 10; i++) {
    pair *x = malloc(sizeof(pair));
    *x = arr0[i];
    vector_push_back(v, (void *)x);
    free(x);
  }
  print_vector_test2(v, 0);

  pair *y = malloc(sizeof(pair));
  (*y).x = 1500000;
  (*y).y = -123;
  vector_assign(v, y, 0);
  free(y);
  print_vector_test2(v, 0);

  vector_pop_back(v);
  print_vector_test2(v, 0);

  vector_erase(v, 2);
  print_vector_test2(v, 0);

  vector_erase(v, 0);
  print_vector_test2(v, 0);

  vector_erase(v, vector_size(v) - 1);
  print_vector_test2(v, 0);

  for (unsigned int i = 0; i < 10; i++) {
    pair *x = malloc(sizeof(pair));
    *x = arr0[i];
    vector_push_back(v, (void *)x);
    free(x);
  }
  print_vector_test2(v, 0);

  while (vector_size(v) > 3) vector_pop_back(v);
  print_vector_test2(v, 0);

  vector_merge_sort(v, cmp_test1);
  print_vector_test2(v, 1);

  vector_free(v);
}

int main() {
  test1();
  test2();
}