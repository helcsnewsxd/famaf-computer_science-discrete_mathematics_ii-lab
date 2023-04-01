#include "APIG23.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../errors/error.h"
#include "../vector/vector.h"

// ------------------------ FUNCIONES Y ESTRUCTURAS AUXILIARES
// ------------------------

struct pair {
  u32 first;
  u32 second;
};
typedef struct pair Pair;

static int cmp_pair(const void* a, const void* b) {
  Pair valA = *((Pair*)a), valB = *((Pair*)b);
  if (valA.first < valB.first)
    return -1;
  else if (valA.first > valB.first)
    return 1;
  else if (valA.second < valB.second)
    return -1;
  else if (valA.second > valB.second)
    return 1;
  return 0;
}

static int cmp(const void* a, const void* b) {
  u32 valA = *((int*)a), valB = *((int*)b);
  if (valA < valB)
    return -1;
  else if (valA > valB)
    return 1;
  return 0;
}

// ------------------------ FUNCIONES CONSTRUCTIVAS ------------------------

Grafo ConstruirGrafo() {
  char buffer[4095];
  u32 cant_vertices = 0;
  u32 cant_aristas = 0;
  u32 cant_aristas_leidas = 0;

  // Vector auxiliar para guardar los nodos. Memoria separada al vector aristas
  Vector nombre_nodos_viejo = NULL;
  nombre_nodos_viejo = vector_inicializar(nombre_nodos_viejo);

  // Contiene aristas de los nodos. El primer elemento del vector con el 2do, el
  // 3er con el 4to, etc ... Memoria separada al vector nombre_nodos_viejo
  Vector aristas = NULL;
  aristas = vector_inicializar(aristas);

  Grafo g = NULL;
  while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
    if (strncmp(buffer, "p edge ", 7) == 0) {
      sscanf(buffer + 7, "%u%*[ ]%u", &cant_vertices, &cant_aristas);
      continue;
    } else if (buffer[0] == 'c' || buffer[0] == '0') {
      continue;
    } else if (strncmp(buffer, "e ", 2) == 0) {
      u32* lado1 = malloc(sizeof(u32));
      u32* lado2 = malloc(sizeof(u32));

      sscanf(buffer + 2, "%u%*[ ]%u", &(*lado1), &(*lado2));

      Pair* nueva_arista = malloc(sizeof(Pair));
      if (*lado1 < *lado2) {
        nueva_arista->first = *lado1;
        nueva_arista->second = *lado2;
      } else {
        nueva_arista->first = *lado2;
        nueva_arista->second = *lado1;
      }

      // Agregas vértice en la lista de nodos
      vector_encolar(nombre_nodos_viejo, lado1);
      vector_encolar(nombre_nodos_viejo, lado2);
      vector_encolar(aristas, nueva_arista);
      cant_aristas_leidas++;
      if (cant_aristas_leidas == cant_aristas) {
        break;
      }
    } else {
      __ERROR_INPUT_GRAFO(cant_aristas_leidas != 0,
                          "Línea con formato inválido.\n");
      __ERROR_INPUT_GRAFO(false,
                          "Mala la lectura de aristas. Cantidad insuficiente "
                          "para la construcción del grafo.\n");
    }
  }

  // Contiene nombre de los nodos
  Vector nombre_nodos_nuevo = NULL;
  nombre_nodos_nuevo = vector_inicializar(nombre_nodos_nuevo);

  vector_ordenar(nombre_nodos_viejo, cmp);
  u32 nodos_tam = vector_tamano(nombre_nodos_viejo);
  for (u32 i = 0; i < nodos_tam; i++) {
    if (i == 0) {
      u32* elem_copy = malloc(sizeof(u32));
      memcpy(elem_copy, vector_elemento(nombre_nodos_viejo, i), sizeof(u32));
      vector_encolar(nombre_nodos_nuevo, elem_copy);
    } else if (*(u32*)vector_elemento(nombre_nodos_viejo, i) !=
               *(u32*)vector_elemento(nombre_nodos_viejo, i - 1)) {
      u32* elem_copy = malloc(sizeof(u32));
      memcpy(elem_copy, vector_elemento(nombre_nodos_viejo, i), sizeof(u32));
      vector_encolar(nombre_nodos_nuevo, elem_copy);
    }
  }
  // Libero vector auxiliar de nodos
  vector_liberar(nombre_nodos_viejo);

  // Inicializo grafo
  g = grafo_inicializar(cant_vertices, nombre_nodos_nuevo);

  // Agrego aristas usando el vector auxiliar aristas
  vector_ordenar(aristas, cmp_pair);
  u32* ind_act = malloc(sizeof(u32));
  *ind_act = 0;

  u32 aristas_tam = vector_tamano(aristas);
  for (u32 i = 0; i < aristas_tam; i++) {
    Pair* arista = vector_elemento(aristas, i);
    u32 ind1 = *ind_act;
    u32 ind2 =
        vector_busqueda_ordenada(nombre_nodos_nuevo, &(arista->second), cmp);

    if (arista->first != *(u32*)vector_elemento(nombre_nodos_nuevo, *ind_act))
      ind1 = *ind_act =
          vector_busqueda_ordenada(nombre_nodos_nuevo, &(arista->first), cmp);

    grafo_anadir_arista(g, ind1, ind2);
  }
  free(ind_act);
  // Libero aristas
  vector_liberar(aristas);

  return g;
}

// ------------------------ FUNCIONES DESTRUCTIVAS ------------------------

void DestruirGrafo(Grafo G) { grafo_liberar(G); }

// ------------------------ FUNCIONES INFORMATIVAS DEL GRAFO
// ------------------------

u32 NumeroDeVertices(Grafo G) { return grafo_cnt_nodos(G); }

u32 NumeroDeLados(Grafo G) { return grafo_cnt_aristas(G); }

u32 Delta(Grafo G) { return grafo_Delta(G); }

// ------------------------ FUNCIONES INFORMATIVAS DE VÉRTICES
// ------------------------

u32 Nombre(u32 i, Grafo G) { return grafo_nombre_nodo(G, i); }

u32 Grado(u32 i, Grafo G) { return grafo_grado_nodo(G, i); }

u32 IndiceVecino(u32 j, u32 i, Grafo G) {
  return grafo_vecino_jesimo_nodo(G, i, j);
}