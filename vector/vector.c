#include "vector.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>  // memcpy

#include "../errors/error.h"

// ------------------------ AUXILIAR FUNCTIONS ------------------------

static void *create_element(void *el) {
  __CONDITION_ERROR((el != NULL), "create_element", "Element is NULL");

  void *nw_el = NULL;
  nw_el = malloc(sizeof(void *));
  __CONDITION_ERROR((nw_el != NULL),
                    "create_element (static function to copy *el)",
                    "Malloc error");

  nw_el = memcpy(nw_el, el, sizeof(void *));
  return nw_el;
}

// ------------------------ STRUCTURE ------------------------

struct VectorSt {
  size_t size, capacity;
  void **array;
};

// ------------------------ CONSTRUCTIVE FUNCTIONS ------------------------

Vector vector_initialize(Vector v) {
  __CONDITION_ERROR((v == NULL), "vector_initialize", "Vector doesn't NULL");

  v = (Vector)malloc(sizeof(struct VectorSt));
  __CONDITION_ERROR((v != NULL), "vector_initialize", "Malloc error");

  v->size = v->capacity = 0;
  v->array = NULL;

  __CONDITION_ERROR((v != NULL), "vector_initialize", "Vector is NULL");
  return v;
}

Vector vector_initialize_with_elements(Vector v, unsigned int n, void *el) {
  __CONDITION_ERROR((v == NULL), "vector_initialize", "Vector doesn't NULL");

  v = vector_initialize(v);
  for (unsigned int i = 0; i < n; i++) {
    vector_push_back(v, el);
  }

  __CONDITION_ERROR((v != NULL), "vector_initialize", "Vector is NULL");
  __CONDITION_ERROR((vector_size(v) == n), "vector_initialize",
                    "Bad initialization of vector");
  return v;
}

void vector_push_back(Vector v, void *el) {
  __CONDITION_ERROR((v != NULL), "vector_push_back", "Vector is NULL");
  __CONDITION_ERROR((el != NULL), "vector_push_back", "Element is NULL");

  if (v->capacity == 0) {
    v->capacity = 1;

    v->array = malloc(sizeof(void *));
    __CONDITION_ERROR((v->array != NULL), "vector_push_back", "Malloc error");

  } else if (v->capacity == v->size) {
    v->capacity *= 2;
    v->array = realloc(v->array, sizeof(void *) * v->capacity);
  }

  v->array[v->size] = create_element(el);
  v->size++;
}

// ------------------------ DESTRUCTIVE FUNCTIONS ------------------------

void vector_free(Vector v) {
  if ((v != NULL)) {
    for (unsigned int i = 0; i < v->size; i++) {
      free(v->array[i]);
      v->array[i] = NULL;
    }
    free(v->array);
    v->array = NULL;
    free(v);
    v = NULL;
  }

  __CONDITION_ERROR((v == NULL), "vector_free", "Bad free of vector");
}

// ------------------------ INFORMATIVE FUNCTIONS ------------------------

bool vector_is_empty(Vector v) {
  __CONDITION_ERROR((v != NULL), "vector_is_empty", "Vector is NULL");

  return v->size == 0;
}

size_t vector_size(Vector v) {
  __CONDITION_ERROR((v != NULL), "vector_size", "Vector is NULL");

  return v->size;
}

void *vector_element(Vector v, unsigned int idx) {
  __CONDITION_ERROR((v != NULL), "vector_element", "Vector is NULL");
  __CONDITION_ERROR((idx < vector_size(v)), "vector_element",
                    "Overflow of index");

  void *el = create_element(v->array[idx]);

  __CONDITION_ERROR((el != NULL), "vector_element", "Bad indexed search");
  return el;
}

unsigned int vector_search(Vector v, void *el,
                           int (*cmp)(const void *a, const void *b)) {
  __CONDITION_ERROR((v != NULL), "vector_search", "Vector is NULL");
  __CONDITION_ERROR((el != NULL), "vector_search", "Element is NULL");

  unsigned int idx = v->size;
  for (unsigned int i = 0; i < v->size; i++) {
    if (cmp(v->array[i], el) == 0) {
      idx = i;
      break;
    }
  }

  __CONDITION_ERROR((idx == vector_size(v) || cmp(v->array[idx], el) == 0),
                    "vector_search", "Bad search");
  return idx;
}

unsigned int vector_sorted_search(Vector v, void *el,
                                  int (*cmp)(const void *a, const void *b)) {
  __CONDITION_ERROR((v != NULL), "vector_sorted_search", "Vector is NULL");
  __CONDITION_ERROR((el != NULL), "vector_sorted_search", "Element is NULL");

  unsigned int idx = v->size;
  unsigned int left = 0, right = v->size;
  while (left + 1 < right) {
    unsigned int middle = (left + right) / 2;
    int cmp_result = cmp(v->array[middle], el);
    if (cmp_result == 0) {
      idx = middle;
      break;

    } else if (cmp_result < 0) {
      left = middle;

    } else {
      right = middle;
    }
  }
  if (cmp(v->array[left], el) == 0) {
    idx = left;
  }

  __CONDITION_ERROR((idx == vector_size(v) || cmp(v->array[idx], el) == 0),
                    "vector_sorted_search", "Bad search");
  return idx;
}

// ------------------------ MODIFICATIVE FUNCTIONS ------------------------

void vector_assign(Vector v, void *el, unsigned int idx) {
  __CONDITION_ERROR((v != NULL), "vector_assign", "Vector is NULL");
  __CONDITION_ERROR((el != NULL), "vector_assing", "Element is NULL");
  __CONDITION_ERROR((idx < vector_size(v)), "vector_assign",
                    "Overflow of index");

  void *nw_el = create_element(el);
  free(v->array[idx]);
  v->array[idx] = NULL;
  v->array[idx] = nw_el;
}

// ------------------------ ERASE FUNCTIONS ------------------------

void vector_pop_back(Vector v) {
  __CONDITION_ERROR((v != NULL), "vector_pop_back", "Vector is NULL");
  __CONDITION_ERROR((!vector_is_empty(v)), "vector_pop_back",
                    "Vector is empty");

  free(v->array[v->size - 1]);
  v->array[v->size - 1] = NULL;
  v->size--;
}

void vector_erase(Vector v, unsigned int idx) {
  __CONDITION_ERROR((v != NULL), "vector_erase", "Vector is NULL");
  __CONDITION_ERROR((!vector_is_empty(v)), "vector_erase", "Vector is empty");
  __CONDITION_ERROR((idx < vector_size(v)), "vector_erase",
                    "Overflow of index");

  free(v->array[idx]);
  v->array[idx] = NULL;
  for (unsigned int i = idx; i < v->size - 1; i++) {
    v->array[i] = v->array[i + 1];
  }
  v->array[v->size - 1] = NULL;

  v->size--;
}

// ------------------------ SORT FUNCTIONS ------------------------

static void merge_sort(Vector v, int (*cmp)(const void *a, const void *b),
                       unsigned int left, unsigned int right) {
  if (left < right) {
    unsigned int middle = left + (right - left) / 2;
    merge_sort(v, cmp, left, middle);
    merge_sort(v, cmp, middle + 1, right);

    Vector aux = NULL;
    aux = vector_initialize(aux);
    unsigned int i = left, j = middle + 1;
    while (i <= middle && j <= right) {
      if (cmp(v->array[i], v->array[j]) <= 0) {
        vector_push_back(aux, v->array[i]);
        i++;
      } else {
        vector_push_back(aux, v->array[j]);
        j++;
      }
    }
    while (i <= middle) {
      vector_push_back(aux, v->array[i]);
      i++;
    }
    while (j <= right) {
      vector_push_back(aux, v->array[j]);
      j++;
    }

    for (unsigned int idx = 0; idx < aux->size; idx++) {
      vector_assign(v, aux->array[idx], idx + left);
    }

    vector_free(aux);

    __CONDITION_ERROR((i == middle + 1 && j == right + 1), "merge_sort",
                      "Bad sorting");
  }
}

void vector_merge_sort(Vector v, int (*cmp)(const void *a, const void *b)) {
  __CONDITION_ERROR((v != NULL), "vector_merge_sort", "Vector is NULL");

  merge_sort(v, cmp, 0, v->size - 1);
}