#ifndef _GRAFO_H
#define _GRAFO_H

#include <stdint.h>

// Portabilidad -> u32 de 32 bits para cualquier arquitectura.
typedef uint32_t u32;

// Tipo de datos auxiliar para definir longitudes.
typedef uint32_t size32;

// Tipo 'vertice': nombre real, etiqueta, color, grado y vecinos.
typedef struct _vertice_t vertice_t;

// Tipo 'grafo': N, M y un arreglo de vertices que lo componen.
typedef struct _grafo_t *grafo_t;


#endif