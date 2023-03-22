#ifndef VECTOR_H_
#define VECTOR_H_

// ------------------------ LIBRARIES (USED FOR TYPES) ------------------------

#include <stdbool.h>
#include <stdio.h>

// ------------------------ STRUCTURE ------------------------

struct VectorSt;

typedef struct VectorSt *Vector;

// ------------------------ CONSTRUCTIVE FUNCTIONS ------------------------

/**
 * @brief Vector inicialization (create the structure and allocate needed
 * memory)
 * @param v
 * @return Vector initialized
 * @pre v == NULL
 * @post v != NULL
 */
Vector vector_initialize(Vector v);

/**
 * @brief Push a element in the end of the vector (the structure generates a
 * copy of the element)
 * @param v
 * @param el
 * @pre v != NULL && el != NULL
 * @post vector_element(v, vector_size(v)-1) == el
 */
void vector_push_back(Vector v, void *el);

// ------------------------ DESTRUCTIVE FUNCTIONS ------------------------

/**
 * @brief Free and erase all the structure and memory used (only local)
 * @param v
 * @post v == NULL
 */
void vector_free(Vector v);

// ------------------------ INFORMATIVE FUNCTIONS ------------------------

/**
 * @brief Check if the vector is empty
 * @param v
 * @return True if the vector is empty (0 elements) and False otherwise
 * @pre v != NULL
 */
bool vector_is_empty(Vector v);

/**
 * @brief Calculate the size of the vector
 * @param v
 * @return Size of the vector
 * @pre v != NULL
 */
size_t vector_size(Vector v);

/**
 * @brief Element with index idx into the vector (returns a copy)
 * @param v
 * @param idx
 * @return Pointer to a copy of the element
 * @pre v != NULL && idx < vector_size(v)
 * @post el != NULL
 */
void *vector_element(Vector v, unsigned int idx);

/**
 * @brief Search with O(N) complexity an element into the vector
 * @param v
 * @param el
 * @param cmp
 * @return Index of the element or vector_size(v) otherwise
 * @pre v != NULL && el != NULL
 * @post idx == vector_size(v) || cmp(vector_element(v, idx), el) == 0
 */
unsigned int vector_search(Vector v, void *el,
                           int (*cmp)(const void *a, const void *b));

/**
 * @brief Search with O(logN) complexity an element into the vector
 * @param v
 * @param el
 * @param cmp
 * @return Index of the element or vector_size(v) otherwise
 * @pre v != NULL && el != NULL && v is sorted (with cmp function)
 * @post idx == vector_size(v) || cmp(vector_element(v, idx), el) == 0
 */
unsigned int vector_sorted_search(Vector v, void *el,
                                  int (*cmp)(const void *a, const void *b));

// ------------------------ MODIFICATIVE FUNCTIONS ------------------------

/**
 * @brief Assign element el to position idx of the vector (the structure use a
 * copy of the element)
 * @param v
 * @param el
 * @param idx
 * @pre v != NULL && el != NULL && idx < vector_size(v)
 * @post vector_element(v, idx) == el
 */
void vector_assign(Vector v, void *el, unsigned int idx);

// ------------------------ ERASE FUNCTIONS ------------------------

/**
 * @brief Erase an element from the end of the vector
 * @param v
 * @pre v != NULL && !vector_is_empty(v)
 */
void vector_pop_back(Vector v);

/**
 * @brief Erase with O(N) complexity an element in position idx of the vector
 * @param v
 * @param idx
 * @pre v != NULL && !vector_is_empty(v) && idx < vector_size(v)
 */
void vector_erase(Vector v, unsigned int idx);

// ------------------------ SORT FUNCTIONS ------------------------

/**
 * @brief Sort with O(NlogN) complexity the vector
 * @param v
 * @param cmp
 * @pre v != NULL
 */
void vector_merge_sort(Vector v, int (*cmp)(const void *a, const void *b));

#endif