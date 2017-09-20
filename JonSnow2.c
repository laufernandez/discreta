/*
---------------------------------------------------------------------
			PROYECTO DE MATEMÁTICA DISCRETA II - 2017

		INTEGRANTES: 
		Astrada Lucas Ezequiel - leakarate06@gmail.com
		Fernandez Articó Lautaro - fernandezarticolautaro@gmail.com
---------------------------------------------------------------------
*/



#include "carga.h"
#include "JonSnow.h"
#include "comparaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef unsigned int u32;

/*
struct _WinterSt_t
{
	u32 n_vertices; // Cantidad de vértices
	u32 m_lados; // Cantidad de lados 
	u32 colores_coloreo; // Cantidad de colores totales del coloreo
	vertice *p_grafo; // Puntero 
};
*/
/*
struct _vertice_t
{
	u32 vertice_nombre; // Nombre real
//	u32 vertice_etiqueta; // Etiqueta 
	u32 vertice_color; // Color del vértice
	u32 vertice_grado; // Grado del vértice
	u32 *vertices_vecinos; // Punteros a los vecinos del vértice
};

*/
// Funciones de Contrucción / Destrucción del grafo.

WinterIsHere WinterIsComing(void){
	
	// Creamos un grafo
	WinterIsHere grafo = NULL; // Creando un puntero a la estructura de grafo 
	grafo = calloc(1, sizeof (struct _WinterSt_t)); // Allocando memoria para la estructura de grafo
	grafo->n_vertices = 0; // Cantidad de vértices del grafo inicializada en 0.
	grafo->m_lados = 0; // Cantidad de lados del grafo inicializada en 0.
	grafo->colores_coloreo = 0; // El total de colores inicial es 0
	grafo->p_grafo = NULL; // Puntero a vértices
	lectura_carga(&grafo);

	

	return grafo; 
}


int Primavera(WinterIsHere W){
	free(W);
	W = NULL;
	return 0;
}

// Funciones de coloreo.
/*
	u32 Greedy(WinterIsHere W){}
	int Bipartito(WinterIsHere W){}

// Funciones para extraer información de datos del grafo.

	u32 NumeroDeVertices(WinterIsHere W){
		return W->n_vertices;
	}
	u32 NumeroDeLados(WinterIsHere W){
		return W->m_lados;
	}
	u32 NumeroDeColores(WinterIsHere W){
		return W->colores_coloreo;
	}
	u32 IesimoVerticeEnElOrden(WinterIsHere W, u32 i){}

// Funciones de ordenación.

	void OrdenNatural(WinterIsHere W){
	}
	void OrdenWelshPowell(WinterIsHere W){
	}
	void AleatorizarVertices(WinterIsHere W, u32 x){}
	void ReordenManteniendoBloqueColores(WinterIsHere W, u32 x){}

// Funciones de los vértices.

	u32 NombreDelVertice(WinterIsHere W, u32 x){}
	u32 ColorDelVertice(WinterIsHere W, u32 x){}
	u32 GradoDelVertice(WinterIsHere W, u32 x){}
	u32 IesimoVecino(WinterIsHere W, u32 x, u32 i){}
*/

int main (void) {
	WinterIsHere hola = WinterIsComing();
	printf("%u\n", hola->n_vertices );
	printf("%u\n", hola->m_lados );
	printf("el vertice %u tiene grado %u", hola->p_grafo[0]->vertice_nombre, hola->p_grafo[0]->vertice_grado);
	free(hola);
	return 0;
}
