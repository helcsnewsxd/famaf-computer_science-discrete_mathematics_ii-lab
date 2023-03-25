#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"
#include "../errors/error.h"
#include "../vector/vector.h"

// --------------------- TAD ---------------------

struct NodoSt{
  int nombre;
  u32 grado;
  Vector lista;
};

struct GrafoSt{
	u32 n, m, Delta;
	Vector vertices;
};

// --------------------- CONSTRUCTORES ---------------------

Grafo crear_grafo(u32 cant_vertices){
  __CONDITION_ERROR((cant_vertices != 0), "crear_grafo", "0 vértices leídos");

	Grafo grafo = malloc(sizeof(struct GrafoSt)); // Declaro struct de mi grafo
	grafo->n = cant_vertices; grafo->m = 0; grafo->Delta = 0; // Inicialización de valores

  // Inicialización del vector de vértices, inicializando a su vez los n nodos necesarios para los n vértices
	grafo->vertices = NULL; grafo->vertices = vector_initialize(grafo->vertices); // Inicialización de Vector de vértices

  __CONDITION_ERROR((grafo != NULL), "crear_grafo", "Grafo es null");
	return grafo;
}

// --------------------- AUXILIARES ---------------------

static int cmp_nodo_int(const void *a, const void *b){
  Nodo *A = (Nodo *)a;
  if(A->nombre < *(int *)b)return -1;
  else if(A->nombre==*(int *)b)return 0;
  return 1;
}

static int cmp_nodo_nodo(const void *a, const void *b){
  Nodo *A = (Nodo *)a;
  Nodo *B = (Nodo *)b;
  if(A->nombre < B->nombre)return -1;
  else if(A->nombre==B->nombre)return 0;
  return 1;
}

// --------------------- FUNCIONES GRAFO ---------------------

u32 grafo_cant_vertices(Grafo grafo){
  __CONDITION_ERROR((grafo != NULL), "grafo_cant_vertices", "Grafo es null");
  __CONDITION_ERROR((grafo->n != 0), "grafo_cant_vertices", "0 Vértices leídos");

	return grafo->n;
}

u32 grafo_cant_aristas(Grafo grafo){
	__CONDITION_ERROR((grafo != NULL), "grafo_cant_aristas", "Grafo es null");

	return grafo->m;
}

u32 grafo_delta(Grafo grafo){
	__CONDITION_ERROR((grafo != NULL), "grafo_cant_aristas", "Grafo es null");

	return grafo->Delta;
}

void grafo_anade_arista(Grafo grafo, int i, int j){
  __CONDITION_ERROR((grafo != NULL), "grafo_anade_aristas", "Grafo es null");
  __CONDITION_ERROR((grafo->vertices != NULL), "grafo_anade_aristas", "Vector vértices es null");

  Vector vector_vertices = grafo->vertices;

  int *el_i = malloc(sizeof(int)); // puntero a i para usar en las funciones
  *el_i = i;

  int *el_j = malloc(sizeof(int)); // puntero a j para usar en las funciones
  *el_j = j;

  // Agrego vértice i a mi lista de vértices:

  // i ya existe? Si no existe, lo agrego
  if (vector_search(vector_vertices, el_i, cmp_nodo_int) == vector_size(vector_vertices)) {
    Nodo *nodo_i = malloc(sizeof(Nodo));
    nodo_i->nombre = i;
    nodo_i->grado = 1;
    nodo_i->lista = NULL; nodo_i->lista = vector_initialize(nodo_i->lista);

    vector_push_back(nodo_i->lista, (int *)el_j); // agrego vecino j a la lista de vecinos de i

    vector_push_back(grafo->vertices,(Nodo *)nodo_i); // agrego nodo de vértice i a mi lista de vecinos

    // actualizo delta
    if(grafo->Delta < nodo_i->grado) grafo->Delta = nodo_i->grado;

    // libero memoria porque vector_push_back copia el nodo
    free(nodo_i);
    nodo_i = NULL;

  } else { // si existe, aumento su grado 
    u32 index = vector_search(vector_vertices, el_i, cmp_nodo_int); // busco el índice del elem ya ordenado supuestamente
    Nodo *nodo_i = (Nodo*)vector_element(vector_vertices, index); // puntero al nodo
    nodo_i->grado++;

    // agrego a j como vecino de i.
    vector_push_back(nodo_i->lista, (int *)el_j);

    // actualizo delta
    if(grafo->Delta < nodo_i->grado) grafo->Delta = nodo_i->grado;
  }
  
  // Agrego vértice j a mi lista de vértices:

  // j ya existe? si no existe lo agrego
  if (vector_search(vector_vertices, el_j, cmp_nodo_int) == vector_size(vector_vertices)) {
    Nodo *nodo_j = malloc(sizeof(Nodo));
    nodo_j->nombre = j;
    nodo_j->grado = 1;
    nodo_j->lista = NULL; nodo_j->lista = vector_initialize(nodo_j->lista);

    // agrego a i como vecino de j.
    vector_push_back(nodo_j->lista, (int *)el_i);

    // agrego j a mi lista de vértices
    vector_push_back(vector_vertices, (Nodo *)nodo_j);

    // actualizo delta
    if(grafo->Delta < nodo_j->grado) grafo->Delta = nodo_j->grado;

    // libero memoria
    free(nodo_j);
    nodo_j = NULL;

  } else { // si existe, aumento su grado
    u32 index = vector_search(vector_vertices, el_j, cmp_nodo_int);
    Nodo *nodo_j = (Nodo*)vector_element(vector_vertices, index);
    nodo_j->grado++;

    // agrego a i como vecino de j.
    vector_push_back(nodo_j->lista, (int *)el_i);

    // actualizo delta
    if(grafo->Delta < nodo_j->grado) grafo->Delta = nodo_j->grado;
  }

  // agrego una arista
  grafo->m++;

  free(el_i);
  free(el_j);

  vector_merge_sort(grafo->vertices, cmp_nodo_nodo); // ordeno lista de vértices

  __CONDITION_ERROR((grafo != NULL), "grafo_anade_aristas", "Grafo es null");
}

Nodo *obtener_nodo(Grafo grafo, u32 i){
  __CONDITION_ERROR((grafo != NULL), "obtener_nodo", "Grafo es null");
  __CONDITION_ERROR((i <= grafo->n), "obtener_nodo", "i está fuera de los límites");
  Nodo *result = (Nodo *)vector_element(grafo->vertices, i);

  __CONDITION_ERROR((result != NULL), "obtener_nodo", "Nodo es null");
  return result;
}

Grafo grafo_destruir(Grafo grafo){
  __CONDITION_ERROR((grafo != NULL), "grafo_destruir", "Grafo es null");

  for (unsigned int i = 0; i < grafo->n; i++) {
    vector_free(obtener_nodo(grafo, i)->lista);
  }

  vector_free(grafo->vertices);
  free(grafo);
  grafo = NULL;

  return grafo;
}

void grafo_print(Grafo grafo){
  __CONDITION_ERROR((grafo != NULL), "grafo_print", "Grafo es null");

  if (grafo->n == 0) {
    printf("Grafo no tiene elementos.\n");
  } else {
    printf("%u %u %u\n", grafo->n, grafo->m, grafo->Delta);
    for(u32 i = 0; i < grafo->n; i++){
      printf("Índice de iteración es: %u\n", i);
      Nodo *nodo_info = obtener_nodo(grafo, i);
      printf("Viendo nodo %u:\n", i);
      printf("  Nombre %u:\n", nodo_info->nombre);
      printf("  Grado -> %u\n", nodo_info->grado);
      printf("  Vecinos -> "); 
      for(u32 j = 0; j < nodo_info->grado; j++) {
        printf("%u ", *((u32 *)vector_element(nodo_info->lista, j)));
      }
      printf("\n");
    }
  }
}