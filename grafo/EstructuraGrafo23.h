#ifndef GRAFO_H_
#define GRAFO_H_

// ------------------------ TIPOS DE DATOS ------------------------

#include "../vector/vector.h"

typedef unsigned int u32;

// --------------------- ESTRUCTURAS DE DATOS ---------------------

/**
 * @brief Estructura de datos del grafo (incluye nombre de los nodos)
 */
typedef struct GrafoStAux GrafoSt;

// --------------------- FUNCIONES CONSTRUCTORAS ---------------------

/**
 * @brief Crear el nuevo grafo dada una cierta cantidad de nodos y sus nombres
 * @param cnt_vertices
 * @param nombre_nodos
 * @return GrafoSt* creado sin aristas
 * @post grafo != NULL
 */
GrafoSt* grafo_inicializar(u32 cnt_vertices, Vector nombre_nodos);

/**
 * @brief Añade la arista entre los nodos i, j
 * @param g
 * @param i
 * @param j
 * @pre g != NULL && i < grafo_cnt_nodos(g) && j <
 * grafo_cnt_nodos(g)
 * @post grafo_cnt_aristas(g) >= 1
 */
void grafo_anadir_arista(GrafoSt* g, u32 i, u32 j);

// --------------------- FUNCIONES DESTRUCTORAS ---------------------

/**
 * @brief Libero y elimino el grafo (y toda la memoria asignada para ello)
 * @param g
 * @post g == NULL
 */
void grafo_liberar(GrafoSt* g);

// --------------------- FUNCIONES INFORMATIVAS ---------------------

/**
 * @brief ¿Cuántos vértices tiene?
 * @param g
 * @return Cantidad de vértices
 * @pre g != NULL
 */
u32 grafo_cnt_nodos(GrafoSt* g);

/**
 * @brief ¿Cuántas aristas tiene?
 * @param g
 * @return Cantidad de aristas
 * @pre g != NULL
 */
u32 grafo_cnt_aristas(GrafoSt* g);

/**
 * @brief ¿Cuál es el Delta del grafo?
 * @param g
 * @return Delta del grafo (máximo grado)
 * @pre g != NULL
 */
u32 grafo_Delta(GrafoSt* g);

// --------------------- FUNCIONES INFORMATIVAS (DE NODOS) ---------------------

/**
 * @brief Devuelve el nombre del nodo con índice "indiceNodo"
 * @param g
 * @param indiceNodo
 * @return Nombre del nodo especificado
 * @pre g != NULL && indiceNodo < grafo_cnt_nodos(g)
 */
u32 grafo_nombre_nodo(GrafoSt* g, u32 indiceNodo);

/**
 * @brief Devuelve el grado del nodo con índice "indiceNodo"
 * @param g
 * @param indiceNodo
 * @return Grafo del nodo especificado
 * @pre g != NULL && indiceNodo < grafo_cnt_nodos(g)
 */
u32 grafo_grado_nodo(GrafoSt* g, u32 indiceNodo);

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
u32 grafo_vecino_jesimo_nodo(GrafoSt* g, u32 indiceNodo, u32 j);

#endif