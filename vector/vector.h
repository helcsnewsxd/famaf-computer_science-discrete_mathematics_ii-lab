#ifndef VECTOR_H_
#define VECTOR_H_

// ------------------------ LIBRERIAS (USADAS PARA LOS TIPOS)
// ------------------------

#include <stdbool.h>
#include <stdio.h>

// ------------------------ ESTRUCTURA DE DATOS ------------------------

/**
 * @brief Estructura de datos tipo lista
 * @note Los elementos que se coloquen no pertenecen a esta estructura de datos
 * ya que no se genera una copia interna
 * @note Esta estructura no se encarga de conservar los datos pero sí de
 * liberarlos cuando se destruye
 */
typedef struct VectorSt *Vector;

// ------------------------ FUNCIONES CONSTRUCTIVAS ------------------------

/**
 * @brief Inicialización del vector (crea la estructura y reserva la memoria
 * necesaria)
 * @param v
 * @return Vector inicializado
 * @pre v == NULL
 * @post v != NULL
 */
Vector vector_inicializar(Vector v);

/**
 * @brief Inserta un elemento al final del array del vector
 * @param v
 * @param el
 * @pre v != NULL && el != NULL
 * @post vector_elemento(v, vector_tamano(v)-1) == el
 */
void vector_encolar(Vector v, void *el);

// ------------------------ FUNCIONES DESTRUCTIVAS ------------------------

/**
 * @brief Libera y elimina toda la memoria utilizada por la estructura del
 * vector y por los elementos de este
 * @param v
 * @post v == NULL
 */
void vector_liberar(Vector v);

// ------------------------ FUNCIONES INFORMATIVAS ------------------------

/**
 * @brief Verifica si el vector v no tiene elementos
 * @param v
 * @return True si el vector está vacío (0 elementos) y False caso contrario
 * @pre v != NULL
 */
bool vector_esta_vacio(Vector v);

/**
 * @brief Calcula el tamaño del vector
 * @param v
 * @return Tamaño del vector
 * @pre v != NULL
 */
size_t vector_tamano(Vector v);

/**
 * @brief Devuelve un puntero al elemento del vector con el índice indicado
 * @param v
 * @param indice
 * @return Puntero al elemento
 * @pre v != NULL && indice < vector_tamano(v)
 * @post el != NULL
 */
void *vector_elemento(Vector v, unsigned int indice);

/**
 * @brief Busca con complejidad O(N) un elemento "el" en el vector
 * @param v
 * @param el
 * @param cmp
 * @return Índice del elemento en el vector o vector_tamano(v) si no está
 * @pre v != NULL && el != NULL
 * @post indice == vector_tamano(v) || cmp(vector_elemento(v, indice), el) == 0
 */
unsigned int vector_busqueda(Vector v, void *el,
                             int (*cmp)(const void *a, const void *b));

/**
 * @brief Busca con complejidad O(logN) un elemento "el" en el vector. Supone
 * que el vector ya está ordenado
 * @param v
 * @param el
 * @param cmp
 * @return Índice del elemento en el vector o vector_tamano(v) si no está
 * @pre v != NULL && el != NULL && v está ordenado (respecto a cmp)
 * @post indice == vector_tamano(v) || cmp(vector_elemento(v, indice), el) == 0
 */
unsigned int vector_busqueda_ordenada(Vector v, void *el,
                                      int (*cmp)(const void *a, const void *b));

// ------------------------ FUNCIONES MODIFICATIVAS ------------------------

/**
 * @brief Asigna un elemento "el" a la posición "índice" del vector y elimina el
 * que anteriormente se encontraba allí
 * @param v
 * @param el
 * @param indice
 * @pre v != NULL && el != NULL && indice < vector_tamano(v)
 * @post vector_elemento(v, indice) == el
 */
void vector_asignar(Vector v, void *el, unsigned int indice);

/**
 * @brief Ordena con una complejidad de O(NlogN) el vector
 * @param v
 * @param cmp
 * @pre v != NULL
 */
void vector_ordenar(Vector v, int (*cmp)(const void *a, const void *b));

// ------------------------ FUNCIONES DE ELIMINACIÓN ------------------------

/**
 * @brief Elimina y libera la memoria del elemento final del vector v
 * @param v
 * @pre v != NULL && !vector_esta_vacio(v)
 */
void vector_eliminar_ultimo(Vector v);

/**
 * @brief Elimina y libera la memoria con una complejidad O(N) un elemento en la
 * posición indicada
 * @param v
 * @param indice
 * @pre v != NULL && !vector_esta_vacio(v) && indice < vector_tamano(v)
 */
void vector_eliminar(Vector v, unsigned int indice);

#endif