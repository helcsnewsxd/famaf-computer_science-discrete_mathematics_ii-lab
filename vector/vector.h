#ifndef VECTOR_H_
#define VECTOR_H_

// ------------------------ LIBRERIAS (USADAS PARA LOS TIPOS) ------------------------

#include <stdbool.h>
#include <stdio.h>

// ------------------------ ESTRUCTURA ------------------------

struct VectorSt;

typedef struct VectorSt *Vector;

// ------------------------ FUNCIONES CONSTRUCTIVAS ------------------------

/**
 * @brief Inicialización del vector (crea la estructura y reserva la
 * memoria necesaria)
 * @param v
 * @return Vector inicializado
 * @pre v == NULL
 * @post v != NULL
 */
Vector vector_initialize(Vector v);

/**
 * @brief Vector inicialization (create the structure and allocate needed
 * memory) -> creates n elements equals to el
 * @param v
 * @param n
 * @param el
 * @return Vector inicializado con n elementos iguales a el (copia del mismo)
 * @pre v == NULL
 * @post v != NULL
 */
Vector vector_initialize_with_elements(Vector v, unsigned int n, void *el);

/**
 * @brief Inserta un elemento al final del array del vector (la estructura genera una copia del vector)
 * @param v
 * @param el
 * @pre v != NULL && el != NULL
 * @post vector_element(v, vector_size(v)-1) == el
 */
void vector_push_back(Vector v, void *el);

// ------------------------ FUNCIONES DESTRUCTIVAS ------------------------

/**
 * @brief Libera y elimina toda la memoria utilizada por el vector v
 * @param v
 * @post v == NULL
 */
void vector_free(Vector v);

// ------------------------ FUNCIONES INFORMATIVAS ------------------------

/**
 * @brief Verifica si el array del vector v no tiene elementos
 * @param v
 * @return True si el vector esta vacío (0 elementos) y False caso contrario
 * @pre v != NULL
 */
bool vector_is_empty(Vector v);

/**
 * @brief Calcula el tamaño del vector
 * @param v
 * @return Tamaño del vector
 * @pre v != NULL
 */
size_t vector_size(Vector v);

/**
 * @brief Devuelve el elemento del array indexado en idx del vector v (devuelve una copia)
 * @param v
 * @param idx
 * @return Puntero a una copia del elemento
 * @pre v != NULL && idx < vector_size(v)
 * @post el != NULL
 */
void *vector_element(Vector v, unsigned int idx);

/**
 * @brief Busca con complejidad O(N) un elemento el en el vector
 * @param v
 * @param el
 * @param cmp
 * @return Índice del elemento en el array del vector o vector_size(v) caso contrario
 * @pre v != NULL && el != NULL
 * @post idx == vector_size(v) || cmp(vector_element(v, idx), el) == 0
 */
unsigned int vector_search(Vector v, void *el,
                           int (*cmp)(const void *a, const void *b));

/**
 * @brief Busca con complejidad O(N) un elemento el en el vector. Supone que el array de v está ordenado
 * @param v
 * @param el
 * @param cmp
 * @return Índice del elemento en el array del vector o vector_size(v) caso contrario
 * @pre v != NULL && el != NULL && v is sorted (with cmp function)
 * @post idx == vector_size(v) || cmp(vector_element(v, idx), el) == 0
 */
unsigned int vector_sorted_search(Vector v, void *el,
                                  int (*cmp)(const void *a, const void *b));

// ------------------------ FUNCIONES MODIFICATIVAS ------------------------

/**
 * @brief Asigna un elemento el a la posición idx del arreglo del vector (usa una copia de el)
 * @param v
 * @param el
 * @param idx
 * @pre v != NULL && el != NULL && idx < vector_size(v)
 * @post vector_element(v, idx) == el
 */
void vector_assign(Vector v, void *el, unsigned int idx);

// ------------------------ FUNCIONES DE ELIMINACIÓN ------------------------

/**
 * @brief Elimina un elemento del array del vector v
 * @param v
 * @pre v != NULL && !vector_is_empty(v)
 */
void vector_pop_back(Vector v);

/**
 * @brief Elimina con una complejidad O(N) un elemento en la posición idx del arreglo del vector v
 * @param v
 * @param idx
 * @pre v != NULL && !vector_is_empty(v) && idx < vector_size(v)
 */
void vector_erase(Vector v, unsigned int idx);

// ------------------------ FUNCIONES DE ORDENAMIENTO ------------------------

/**
 * @brief Ordena con una complejidad de O(NlogN) el array del vector v
 * @param v
 * @param cmp
 * @pre v != NULL
 */
void vector_merge_sort(Vector v, int (*cmp)(const void *a, const void *b));

#endif
