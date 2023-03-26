#ifndef ESTRUCTURA_GRAFO_H_
#define ESTRUCTURA_GRAFO_H_

// ------------------------ LIBRERÍAS (usadas por tipos y TADs)
// ------------------------

#include "../../vector/vector.h"

// ------------------------ TIPOS DE DATOS ------------------------

typedef unsigned int u32;

// ------------------------ ESTRUCTURAS DE DATOS ------------------------

/**
 * @brief Estructura de datos del grafo (incluye nombre de los nodos)
 */
struct GrafoSt;

// ------------------------ FUNCIONES CONTRUCTIVAS ------------------------

/**
 * @brief Crea el grafo con la cantidad de nodos y nombres especificados (el
 * índice de un nodo corresponde a la posición de donde se encuentre el nombre
 * en el vector luego de ser ordenado)
 * @param cnt_nodos
 * @param nombre_nodos -> Vector (la estructura toma la responsabilidad
 * del vector y su memoria)
 * @return Puntero a la estructura del grafo
 * @pre nombre_nodos != NULL
 * @post g != NULL
 */
struct GrafoSt* grafo_inicializar(u32 cnt_nodos, Vector nombre_nodos);

/**
 * @brief Agrega la arista (nombreNodoI, nombreNodoJ) en el grafo g
 * @param g
 * @param nombreNodoI
 * @param nombreNodoJ
 * @pre g != NULL
 */
void grafo_anadir_arista(struct GrafoSt* g, u32 nombreNodoI, u32 nombreNodoJ);

// ------------------------ FUNCIONES DESTRUCTIVAS ------------------------

/**
 * @brief Elimina y libera la memoria usada para la estructura del grafo
 * @param g
 * @post g == NULL
 */
void grafo_liberar(struct GrafoSt* g);

// ------------------------ FUNCIONES INFORMATIVAS ------------------------

/**
 * @brief Devuelve la cantidad de nodos del grafo g
 * @param g
 * @return Cantidad de nodos
 * @pre g != NULL
 */
u32 grafo_cnt_nodos(struct GrafoSt* g);

/**
 * @brief Devuelve la cantidad de aristas del grafo g
 * @param g
 * @return Cantidad de aristas
 * @pre g != NULL
 */
u32 grafo_cnt_aristas(struct GrafoSt* g);

/**
 * @brief Devuelve el Delta (máximo grado) del grafo g
 * @param g
 * @return Delta
 * @pre g != NULL
 */
u32 grafo_Delta(struct GrafoSt* g);

// ------------------------ FUNCIONES INFORMATIVAS (nodos)
// ------------------------

/**
 * @brief Devuelve el nombre del nodo con índice "indiceNodo"
 * @param g
 * @param indiceNodo
 * @return Nombre del nodo especificado
 * @pre g != NULL && indiceNodo < grafo_cnt_nodos(g)
 */
u32 grafo_nombre_nodo(struct GrafoSt* g, u32 indiceNodo);

/**
 * @brief Devuelve el grado del nodo con índice "indiceNodo"
 * @param g
 * @param indiceNodo
 * @return Grafo del nodo especificado
 * @pre g != NULL && indiceNodo < grafo_cnt_nodos(g)
 */
u32 grafo_grado_nodo(struct GrafoSt* g, u32 indiceNodo);

/**
 * @brief Devuelve el j-ésimo vecino del nodo con índice "indiceNodo"
 * @param g
 * @param indiceNodo
 * @param j
 * @return J-ésimo vecino del nodo especificado
 * @pre g != NULL && indiceNodo < grafo_cnt_nodos(g) && j < grafo_grado_nodo(g,
 * indiceNodo)
 * @post indiceNodoVec < grafo_cnt_nodos(g)
 */
u32 grafo_vecino_jesimo_nodo(struct GrafoSt* g, u32 indiceNodo, u32 j);

#endif