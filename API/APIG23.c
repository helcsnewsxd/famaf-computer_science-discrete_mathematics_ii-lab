#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "APIG23.h"

// ------------------------ FUNCIONES AUXILIARES ------------------------

static int cmp(const void* a, const void* b) {
  u32 valA = *((int*)a), valB = *((int*)b);
  if (valA < valB)
    return -1;
  else if (valA > valB)
    return 1;
  return 0;
}

void grafo_print(Grafo g) {
  u32 n = NumeroDeVertices(g);

  printf("Cantidad de nodos: %u\nCantidad de aristas: %u\nDelta: %u\nNodos:\n",
         n, NumeroDeLados(g), Delta(g));

  for (u32 i = 0; i < n; i++) {
    printf("    Nombre: %u\n", Nombre(i, g));

    u32 sz = Grado(i, g);
    printf("    Grado: %u\nVecinos: ", sz);

    for (u32 j = 0; j < sz; j++) {
      u32 x = IndiceVecino(j, i, g);
      u32 y = Nombre(x, g);
      printf("(%u, %u) ", x, y);
    }
    printf("\n================\n");
  }
}

// ------------------------ FUNCIONES CONSTRUCTIVAS ------------------------

Grafo ConstruirGrafo(){
  char buffer[4095];
  u32 cant_vertices = 0; u32 cant_aristas = 0;
  u32 cant_aristas_leidas = 0;

  // Contiene nombre de los nodos
  Vector nombre_nodos = NULL; 
  nombre_nodos = vector_inicializar(nombre_nodos); 

  // Contiene aristas de los nodos. El primer elemento del vector con el 2do, el 3er con el 4to, etc ...
  Vector aristas = NULL;
  aristas = vector_inicializar(aristas); 

  Grafo g = NULL;
  while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
    if (strncmp(buffer, "p edge", 6) == 0) {
      sscanf(buffer+6, "%u%*[ ]%u", &cant_vertices, &cant_aristas);
      continue;
    } else if (buffer[0] == 'c' || buffer[0] == '0') {
      continue;
    } else if (buffer[0] == 'e'){
      u32* lado1 = malloc(sizeof(u32));
      u32* lado2 = malloc(sizeof(u32));

      // Utilizo variables auxiliares, asi cuando haga free de aristas, no se borran los elementos de mi grafo original.
      // Se borraban porque metia lado1 y lado2 a mi vector auxiliar aristas, y como lado1 y lado2 tambien se mete en
      // nombres_nodos, el contenido a la direc de memoria de lado1 y lado2 se destruye en el destroy. Por eso necesito
      // una dirección de memoria aparte.
      u32 *lado1_aux = malloc(sizeof(u32));
      u32 *lado2_aux = malloc(sizeof(u32));

      sscanf(buffer+2, "%u%*[ ]%u", &(*lado1), &(*lado2));

      memcpy(lado1_aux, lado1, sizeof(u32));
      memcpy(lado2_aux, lado2, sizeof(u32));

      // Chequeo que el vértice a ingresar no exista ya en mi lista de nodos
      if (!vector_esta_vacio(nombre_nodos)) {
        if (vector_busqueda(nombre_nodos, lado1, cmp) == vector_tamano(nombre_nodos)) {
          vector_encolar(nombre_nodos, lado1);
        } else {
          free(lado1);
        }
        if (vector_busqueda(nombre_nodos, lado2, cmp) == vector_tamano(nombre_nodos)){
          vector_encolar(nombre_nodos, lado2);
        } else {
          free(lado2);
        }
      } else {
        vector_encolar(nombre_nodos, lado1); vector_encolar(nombre_nodos, lado2);
      }

      vector_encolar(aristas, lado1_aux); vector_encolar(aristas, lado2_aux);
      cant_aristas_leidas++;
      if (cant_aristas_leidas == cant_aristas) {
        break;
      }
    }
  }

  g = grafo_inicializar(cant_vertices, nombre_nodos);
  
  for (u32 i = 0; i < vector_tamano(aristas); i = i+2){
    grafo_anadir_arista(g, *((u32 *)vector_elemento(aristas, i)), *((u32 *)vector_elemento(aristas, i+1)));
  }

  vector_liberar(aristas);

  return g;
}

// ------------------------ FUNCIONES DESTRUCTIVAS ------------------------

void DestruirGrafo(Grafo G){
  grafo_liberar(G);
}

// ------------------------ FUNCIONES INFORMATIVAS DEL GRAFO ------------------------

u32 NumeroDeVertices(Grafo G){
  return grafo_cnt_nodos(G);
}

u32 NumeroDeLados(Grafo G){
  return grafo_cnt_aristas(G);
}

u32 Delta(Grafo G){
  return grafo_Delta(G);
}

// ------------------------ FUNCIONES INFORMATIVAS DE VÉRTICES ------------------------

u32 Nombre(u32 i, Grafo G){
  return grafo_nombre_nodo(G, i);
}
u32 Grado(u32 i, Grafo G){
  return grafo_grado_nodo(G, i);
}
u32 IndiceVecino(u32 j, u32 i, Grafo G){
  return grafo_vecino_jesimo_nodo(G, i, j);
}

// ------------------------ MAIN TESTING ------------------------

int main(void){
  Grafo g = NULL;
  g = ConstruirGrafo();
  grafo_print(g);
  DestruirGrafo(g);


  return 0;
}
