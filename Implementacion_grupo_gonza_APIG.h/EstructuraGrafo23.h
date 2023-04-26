#ifndef ESTGRAF23_H
#define ESTGRAF23_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Definicion de u32
typedef uint32_t u32;

// Maximo numero representable por u32
#define MAX_U32 4294967295

// Estructura que representa a un vertice
typedef struct VerticeSt {
  u32 nombre;    // Nombre del vertice
  u32 grado;     // Grado del vertice
  u32 *vecinos;  // Arreglo de vecinos con sus indices en la lista de vertices
                 // (Es un subarreglo del arreglo global de lados_vecinos)
} VerticeSt;

// Estructura que representa a un lado (Se usa como estructura auxiliar durante
// la construcción del grafo)
typedef struct LadoSt {
  u32 v1;                   // Nombre del primer vertice
  u32 v2;                   // Nombre del segundo vertice
  u32 ubicacion_indice_v2;  // Ubicacion del indice del vertice v2 del lado en
                            // el arreglo auxiliar del arreglo temporal de lados
} LadoSt;

// Estructura que representa al grafo
typedef struct GrafoSt {
  u32 n;                // Numero de vertices
  u32 m;                // Numero de lados
  u32 delta;            // Delta del grafo
  VerticeSt *vertices;  // Arreglo de vertices
  u32 *lados_vecinos;   // Arreglo de los índices de lados vecinos (global por
                       // grafo para optimizar el acceso)
} GrafoSt;

#endif