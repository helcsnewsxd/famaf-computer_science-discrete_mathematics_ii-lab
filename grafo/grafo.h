#ifndef _grafo_H_
#define _grafo_H_

#include <stdio.h>
#include "../vector/vector.h"

// --------------------- TAD ---------------------

/** Vertices se representan con unsigned int de 32 bits
 */
typedef unsigned int u32;

/** Estructura de datos del Grafo
 */

typedef struct NodoSt Nodo;

typedef struct GrafoSt *Grafo;

// --------------------- CONSTRUCTORES ---------------------

/*
  CREACIÓN -> Creador del Grafo
  @param u32 cant_vertices
  @return Grafo vacío
  @note Crea grafo e inicializa campos respectivos
  @note Precondición: true
  @note Postcondicion: grafo != NULL
*/
Grafo crear_grafo(u32 cant_vertices);

// --------------------- FUNCIONES GRAFO ---------------------

/*
  ¿Cuántos vértices tiene?
  @param Grafo grafo
  @return u32 número de vértices
  @note Devuelve cantidad de vértices en el grafo
  @note Precondición: grafo != NULL
  @note Postcondicion: cant_vertices != 0
*/
u32 grafo_cant_vertices(Grafo grafo);

/*
  ¿Cuántas aristas tiene?
  @param Grafo grafo
  @return u32 número de aristas
  @note Devuelve cantidad de aristas en el grafo
  @note Precondición: grafo != NULL
*/
u32 grafo_cant_aristas(Grafo grafo);

/*
  ¿Cual es el Delta del grafo?
  @param Grafo grafo
  @return u32 Delta del grafo
  @note Devuelve grado máximo del grafo
  @note Precondición: grafo != NULL
*/
u32 grafo_delta(Grafo grafo);

/*
  ADICIÓN -> Añade una arista
  @param Grafo grafo
  @param u32 i
  @param u32 j
  @return void
  @note Agrega al grafo una arista entre los vértices en Orden Natural i y j
  @note Precondición: (grafo != NULL) && (0 <= i < grafo->n) && (0 <= j < grafo->n)
  @note Postcondicion: grafo != NULL
*/
void grafo_anade_arista(Grafo grafo, int i, int j);

/*
  DESTRUCCIÓN: Libera la memoria ocupada por un grafo
  @param Grafo grafo
  @return void
  @note Libera la memoria ocupada por el grafo y sus respectivos vectores a los vértices y vecinos
  @note Precondición: grafo != NULL
  @note Postcondicion: grafo == NULL
*/
Grafo grafo_destruir(Grafo grafo);

// --------------------- FUNCIONES NODOS ---------------------

/*
  Obtiene el nodo i de la lista de vértices de grafo
  @param Grafo grafo
  @param u32 i
  @return Nodo*
  @note Precondición: grafo !=  && i < grafo->n
  @note Postcondicion: Nodo *nodo != NULL
*/
Nodo *obtener_nodo(Grafo grafo, u32 i);


// --------------------- DEBUGGING ---------------------

/*
  DEGUB -> Imprimir vértices del grafo con sus respectivos vecinos y deltas
  @param Grafo grafo
  @note Precondicion: grafo != NULL
*/
void grafo_print(Grafo grafo);

#endif