#ifndef GRAFO_SIMPLE_H_
#define GRAFO_SIMPLE_H_

// --------------------- LIBRERÍAS (USADAS POR TIPOS O TAD)
// ---------------------

#include "../vector/vector.h"

// --------------------- ESTRUCTURAS DE DATOS ---------------------

/**
 * @brief Estructura de datos del Grafo Simple ==> Los "nombres" de los nodos
 * son los índices. Es decir, si tengo N nodos, todos van desde 0 a N - 1
 */
typedef struct GrafoSimpleSt* GrafoSimple;

// --------------------- FUNCIONES CONSTRUCTORAS ---------------------

/**
 * @brief Crear el nuevo grafo dada una cierta cantidad de nodos (tienen nombre
 * en rango [0, cnt_vertices))
 * @param cnt_vertices
 * @return Grafo creado sin aristas
 * @post grafo != NULL
 */
GrafoSimple grafo_simple_inicializar(unsigned int cnt_vertices);

/**
 * @brief Añade la arista entre los nodos i, j
 * @param gs
 * @param i
 * @param j
 * @pre gs != NULL && i < grafo_simple_cnt_nodos(gs) && j <
 * grafo_simple_cnt_nodos(gs)
 * @post grafo_simple_cnt_aristas(gs) >= 1
 */
void grafo_simple_anadir_arista(GrafoSimple gs, unsigned int i, unsigned int j);

// --------------------- FUNCIONES DESTRUCTORAS ---------------------

/**
 * @brief Libero y elimino el grafo (y toda la memoria asignada para ello)
 * @param gs
 * @post gs == NULL
 */
void grafo_simple_liberar(GrafoSimple gs);

// --------------------- FUNCIONES INFORMATIVAS ---------------------

/**
 * @brief ¿Cuántos vértices tiene?
 * @param gs
 * @return Cantidad de vértices
 * @pre gs != NULL
 */
unsigned int grafo_simple_cnt_nodos(GrafoSimple gs);

/**
 * @brief ¿Cuántas aristas tiene?
 * @param gs
 * @return Cantidad de aristas
 * @pre gs != NULL
 */
unsigned int grafo_simple_cnt_aristas(GrafoSimple gs);

/**
 * @brief ¿Cuál es el Delta del grafo?
 * @param gs
 * @return Delta del grafo (máximo grado)
 * @pre gs != NULL
 */
unsigned int grafo_simple_Delta(GrafoSimple gs);

// --------------------- FUNCIONES INFORMATIVAS (DE NODOS) ---------------------

/**
 * @brief Lista de vecinos del nodo pedido
 * @param gs
 * @param nodo
 * @return Vector con indices de vecinos
 * @pre gs != NULL && indice < grafo_simple_cnt_nodos(gs)
 * @post v != NULL
 */
Vector grafo_simple_vecinos_nodo(GrafoSimple gs, unsigned int indice);

/**
 * @brief Grafo del nodo pedido
 * @param gs
 * @param indice
 * @return Grado del nodo
 * @pre gs != NULL && indice < grafo_simple_cnt_nodos(gs)
 */
unsigned int grafo_simple_grado_nodo(GrafoSimple gs, unsigned int indice);

#endif