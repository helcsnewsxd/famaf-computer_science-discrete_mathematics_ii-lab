#include "APIG23.h"

#include <stdbool.h>


// Saltear lineas consecutivas de stdin que comiencen con caracter
static void saltear_lineas_que_comiencen_con(char caracter) {
  char c;
  // si el primer caracter es <caracter> avanza hasta el final de la linea
  while ((c = getchar()) == caracter) {
    while (getchar() != '\n' && !feof(stdin))
      ;
  }
  // como revisamos el primer caracter de la segunda linea
  // debemos volver a agregarlo a stdin
  ungetc(c, stdin);
}

static u32 alocar_vertices_y_lados_segun_input(Grafo G) {
  // Lectura de la cantidad de vertices y lados
  u32 ret = scanf("p edge %u %u", &G->n, &G->m);
  if (ret != 2) {
    return 1;
  }
  // Reserva de memoria para los arreglos de vertices y lados_vecinos
  G->vertices = malloc(G->n * sizeof(struct VerticeSt));
  if (G->vertices == NULL) {
    return 1;
  }
  G->lados_vecinos = malloc(2 * G->m * sizeof(u32));
  if (G->lados_vecinos == NULL) {
    free(G->vertices);
    return 1;
  }
  return 0;
}

static u32 leer_lados_desde_input(Grafo G, struct LadoSt *lados_temp) {
  // Lectura de los lados y almacenamiento en el arreglo auxiliar. Su
  // complejidad es O(m)
  for (u32 i = 0; i < G->m; i++) {
    // Se lee el lado y se guarda en el arreglo auxiliar
    u32 ret = scanf(" e %u %u", &lados_temp[i * 2].v1, &lados_temp[i * 2].v2);
    if (ret != 2) {
      return 1;
    }
    // Se agrega el lado inverso al leido
    lados_temp[i * 2 + 1].v1 = lados_temp[i * 2].v2;
    lados_temp[i * 2 + 1].v2 = lados_temp[i * 2].v1;

    // Se guarda la ubicacion que tendrá en lados_temp_aux el indice del vertice
    // v2 del lado
    lados_temp[i * 2].ubicacion_indice_v2 = i * 2;
    lados_temp[i * 2 + 1].ubicacion_indice_v2 = i * 2 + 1;
  }
  return 0;
}

// Función auxiliar para comparar dos lados. Se usa en qsort y da un orden
// ascendente comparando v1 y luego comparando v2 en caso de empate
static int comparacion_lados(const void *a, const void *b) {
  struct LadoSt *lado1 = (struct LadoSt *)a;
  struct LadoSt *lado2 = (struct LadoSt *)b;
  if (lado1->v1 < lado2->v1)
    return -1;
  else if (lado1->v1 > lado2->v1)
    return 1;
  else if (lado1->v2 < lado2->v2)
    return -1;
  else if (lado1->v2 > lado2->v2)
    return 1;
  else
    return 0;
}

static void asignar_nombre_y_grado(Grafo G, struct LadoSt *lados_temp,
                                   u32 *lados_temp_aux) {
  // Se recorre el arreglo auxiliar y se asigna el nombre del vertice y el grado
  // de cada vertice. Su complejidad es O(m)
  u32 j = 0;
  for (u32 i = 0; i < G->n; i++) {
    // Se asigna el nombre del vertice en el arreglo de vertices y se inicializa
    // el grado en 0
    G->vertices[i].nombre = lados_temp[j].v1;
    G->vertices[i].grado = 0;

    // Se recorre el arreglo auxiliar hasta que se encuentre un lado que no
    // tenga el mismo v1 que el vertice actual (Como están ordenados por v1,
    // cuando se encuentre un lado con un v1 distinto siginifica que ya se
    // recorrieron todos los lados que tienen el vertice actual)
    while (j < 2 * G->m && lados_temp[j].v1 == G->vertices[i].nombre) {
      // Se incrementa el grado del vertice actual
      G->vertices[i].grado++;
      // Se guarda el indice del vertice v1 del lado en el arreglo auxiliar (En
      // la ubicación que leerá el lado inverso para saber la posición de su v2)
      if (lados_temp[j].ubicacion_indice_v2 % 2 == 0) {
        lados_temp_aux[lados_temp[j].ubicacion_indice_v2 + 1] = i;
      } else {
        lados_temp_aux[lados_temp[j].ubicacion_indice_v2 - 1] = i;
      }
      j++;
    }

    // Se actualiza el valor de delta si el grado del vertice actual es mayor
    // que el actual valor de delta
    if (G->vertices[i].grado > G->delta) G->delta = G->vertices[i].grado;
  }
}

static void asignar_vecinos(Grafo G, struct LadoSt *lados_temp,
                            u32 *lados_temp_aux) {
  // Se recorre el arreglo de vertices y se asignan los vecinos de cada vertice.
  // Su complejidad es O(m)
  u32 j = 0;
  for (u32 i = 0; i < G->n; i++) {
    // Se asigna la dirección del primer vecino del vertice actual en el arreglo
    // de lados_vecinos
    G->vertices[i].vecinos = &G->lados_vecinos[j];
    // Se recorre el arreglo auxiliar hasta que se encuentre un lado que no
    // tenga el mismo v1 que el vertice actual (Como están ordenados por v1,
    // cuando se encuentre un lado con un v1 distinto siginifica que ya se
    // recorrieron todos los lados que tienen el vertice actual)
    while (j < 2 * G->m && lados_temp[j].v1 == G->vertices[i].nombre) {
      // Se asigna el indice del vertice v2 del lado en el arreglo de
      // lados_vecinos
      G->lados_vecinos[j] = lados_temp_aux[lados_temp[j].ubicacion_indice_v2];
      j++;
    }
  }
}

Grafo ConstruirGrafo() {
  // Inicialización del grafo
  Grafo G = malloc(sizeof(struct GrafoSt));
  if (G == NULL) {
    return NULL;
  }
  G->n = 0;
  G->m = 0;
  G->delta = 0;
  G->vertices = NULL;
  G->lados_vecinos = NULL;

  saltear_lineas_que_comiencen_con('c');

  u32 ret = alocar_vertices_y_lados_segun_input(G);
  if (ret) {
    free(G);
    return NULL;
  }

  // Arreglo auxiliar para almacenar los lados y arreglo auxiliar para luego
  // asignar los indices de los lados vecinos
  struct LadoSt *lados_temp = malloc(2 * G->m * sizeof(struct LadoSt));
  if (lados_temp == NULL) {
    free(G);
    free(G->vertices);
    free(G->lados_vecinos);
    return NULL;
  }

  u32 *lados_temp_aux = malloc(2 * G->m * sizeof(u32));
  if (lados_temp_aux == NULL) {
    free(G->vertices);
    free(G->lados_vecinos);
    free(G);
    free(lados_temp);
    return NULL;
  }

  ret = leer_lados_desde_input(G, lados_temp);
  if (ret) {
    free(G->vertices);
    free(G->lados_vecinos);
    free(G);
    free(lados_temp);
    free(lados_temp_aux);
    return NULL;
  }

  // Ordenamiento de los lados a partir de v1. Su complejidad se supone que es
  // O(m log m) dependiendo de la implementación de qsort
  qsort(lados_temp, 2 * G->m, sizeof(struct LadoSt), comparacion_lados);

  asignar_nombre_y_grado(G, lados_temp, lados_temp_aux);

  asignar_vecinos(G, lados_temp, lados_temp_aux);

  // Libero la memoria de los arreglos auxiliares
  free(lados_temp);
  free(lados_temp_aux);

  return G;
}

void DestruirGrafo(Grafo G) {
  free(G->vertices);
  free(G->lados_vecinos);
  free(G);
}

u32 NumeroDeVertices(Grafo G) { return G->n; }

u32 NumeroDeLados(Grafo G) { return G->m; }

u32 Delta(Grafo G) { return G->delta; }

u32 Nombre(u32 i, Grafo G) { return G->vertices[i].nombre; }

u32 Grado(u32 i, Grafo G) {
  return NumeroDeVertices(G) > i ? G->vertices[i].grado : MAX_U32;
}

u32 IndiceVecino(u32 j, u32 i, Grafo G) {
  return NumeroDeVertices(G) > i && Grado(i, G) > j ? G->vertices[i].vecinos[j]
                                                    : MAX_U32;
}
