/*
---------------------------------------------------------------------
			PROYECTO DE MATEMÁTICA DISCRETA II - 2017

		INTEGRANTES: 
		Astrada Lucas Ezequiel - leakarate06@gmail.com
		Fernandez Articó Lautaro - fernandezarticolautaro@gmail.com
---------------------------------------------------------------------
*/


#include "JonSnow.h"
#include "Parser.h"

struct _WinterSt_t
{
	u32 NumeroVertices; /* Cantidad de vértices  */
	u32 NumeroAristas; /* Cantidad de aristas */
	u32 ColoresColoreo; /* Cantidad de colores totales del coloreo */
	Vertex *ArregloVertices[NumeroVertices]; /* Arreglo de vértices */
	Vertex *Orden[NumeroVertices]; /* Arreglo de punteros a vértices, indican orden */

};

struct _VertexSt_t
{
	u32 VerticeNombre; /* Nombre real  */
	u32 VerticeEtiqueta; /* Etiqueta */
	u32 VerticeColor; /* Color del vértice */
	u32 VerticeGrado; /* Grado del vértice */
	Vertex *VerticeVecinos[VerticeGrado]; /* Arreglo de punteros a los vecinos del vértice */
};


// 	ESTRUCTURA PARA LA LISTA DE COLORES

/*typedef struct ElementoLista {
  char                *dato;
  struct ElementoLista *siguiente;
}Elemento;
typedef struct ListaIdentificar {
  Elemento *inicio;
  Elemento *fin;
  int tamaño;
}Lista;
*/


/* Nodo de la lista enlazada. Representa a un color j de la lista enlazada de colores */

typedef struct _ColorJNodoSt_t
{
	u32 ColorJ; // Color que representa el nodo.
	ColorJNodo *Siguiente; // Puntero 'Next' de la lista enlazada.
} ColorJNodo;

/* Lista de nodos de colores */
typedef struct _ListaColoresSt_t
{
	ColorJNodo *PrimerColor; // Puntero al primer color de la lista de colores.
} ListaColores;

// ESTRUCTURA PARA LA LISTA DE VECINOS ASOCIADOS A CADA COLOR

/* Nodo de la lista de vertices pintados por cada color j */
typedef struct _VerticesColorJNodoSt_t
{
	Vertex *VerticeColorJ; // Vertice pintado de color J
	VerticesColorJNodo *Siguiente; // Puntero 'Next' al siguiente elemento de la lista de pintados por j.
} VerticesColorJNodo;

/* Lista de vertices (color j) enlazados */
typedef struct _ListaVerticesColorJSt_t
{
	VerticesColorJNodo *PrimerVerticeColorJ; //Primer vertice pintado con j.
} _ListaVerticesColorJ;

/*



Estas dos estructuras son las que vamos a usar para el coloreo,
son dos listas enlazadas, y nos dan la posibilidad de allocar memoria para
	- un nuevo color 
	- un nuevo vertices en alguno de los colores ya usados 

Recordar que dijimos que basicamente esas dos opciones sintetizan
los dos caminos posibles al correr Greedy.

struct _VerticesConElMismoColorSt_t
{
	Vertex vecino;
	VerticesConElMismoColor;
};

struct _ColoresSt_t
{
	u32 Color;
	VerticesConElMismoColor VerticesDeColor;
	Colores next;	
};



*/






/* Funciones de Contrucción / Destrucción del grafo. */

WinterIsHere WinterIsComing(void){
	u32 PrimerVértice = 0;
	u32 SegundoVértice = 0;

	/* GRAFO */
	WinterIsHere NuevoGrafo = NULL; /* Creando un puntero a la estructura de grafo */
	NuevoGrafo = calloc(1, sizeof (struct _WinterSt_t)); /* Allocando memoria para la estructura de grafo */
	NuevoGrafo->ColoresColoreo = 0; /* El total de colores inicial es 0 */

	FormatoCorrecto(); //???
	CCase(); //???
	PCase(NuevoGrafo->NumeroVertices, NuevoGrafo->NumeroAristas); //???

	/* ARISTAS */
	for (int i=0; i<NuevoGrafo->NumeroVertices; i++) {
		Vertex NuevoVertice = NULL;
		NuevoVertice = calloc(NuevoGrafo->NumeroVertices, sizeof (struct _VertexSt_t));
		NuevoVertice->VerticeColor = i; /* En un principio, todos los vértices son coloreados con color i */
		ECase(PrimerVértice, SegundoVértice);
			/* Hacer algo con los vértices obtenidos */
	}
	return NuevoGrafo; 
}


	int Primavera(WinterIsHere W){}

/* Funciones de coloreo. */

	u32 Greedy(WinterIsHere W){}
	int Bipartito(WinterIsHere W){}

/* Funciones para extraer información de datos del grafo. */

	u32 NumeroDeVertices(WinterIsHere W){
		return W->NumeroAristas;
	}
	u32 NumeroDeLados(WinterIsHere W){
		return W->NumeroAristas;
	}
	u32 NumeroDeColores(WinterIsHere W){
		return W->Coloreo;
	}
	u32 IesimoVerticeEnElOrden(WinterIsHere W, u32 i){}

/* Funciones de ordenación. */

	void OrdenNatural(WinterIsHere W){}
	void OrdenWelshPowell(WinterIsHere W){}
	void AleatorizarVertices(WinterIsHere W, u32 x){}
	void ReordenManteniendoBloqueColores(WinterIsHere W, u32 x){}

/* Funciones de los vértices. */

	u32 NombreDelVertice(WinterIsHere W, u32 x){
		/* Retornar VertexName de x */
	}
	u32 ColorDelVertice(WinterIsHere W, u32 x){}
	u32 GradoDelVertice(WinterIsHere W, u32 x){}
	u32 IesimoVecino(WinterIsHere W, u32 x, u32 i){
		/* Devuelve la etiqueta del vecino numero i
		del vertice cuya etiqueta es x */
	}
