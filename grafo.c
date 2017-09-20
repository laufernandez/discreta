#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Grafo.h"


// Logitud maxima del buffer de lectura de lineas.
#define BUFFER_SIZE 256

// Estructura auxiliar que abstrae un 'lado' donde cada vertice es un u32.
typedef struct _lado32_t {
    u32 vertice_u;                                /* Primer vertice del 'par'. */
    u32 vertice_v;                       /* Segundo vertice. ('lado derecho'). */
} lado32_t;

// Estructura auxiliar que representa un vertice con toda la info necesaria.
struct _vertice_t {
    u32 nombre;
    u32 etiqueta;
    u32 color;
    u32 grado;
    u32 *vecinos;        /* Los vecinos como un arreglo de u32. Referencias(1) */
};

// Representacion de un grafo como un arreglo de tipos de dato 'vertice'.
struct _grafo_t {
    u32 n_vertices;
    u32 m_lados;
    vertice_t *arreglo_vertices;
};


// Declaracion de funciones auxiliares
lado32_t *espejar_lado(u32 *indice, lado32_t *espejo, u32 u, u32 v);
int comparar_vertices_u(const void* a, const void* b);
int comparar_vertices_v(const void* a, const void* b);


// Funcion que crea un grafo e inicializa su numero de vertices y de lados.
grafo_t crearGrafoDesdeStdin(void) {

    char linea[BUFFER_SIZE];       /* Lineas de BUFFER_SIZE caracteres maximo. */

    u32 n = 0, m = 0;           /* Variables auxiliares temporales para N y M. */
    grafo_t grafo = NULL;                       /* Puntero a estructura grafo. */

    while(fgets(linea, BUFFER_SIZE, stdin)) {
        // Busca la 'p-linea' con N y M ignorando comentarios.
        if(strncmp(linea, "c", 1)) { 
            // Parsea 'p-linea' y almacena en variables temporales.
            if(!strncmp(linea, "p edge ", 7)) {
                sscanf(linea, "%*c %*s %u %u", &n, &m);
                // Fin de lectura de metadata y comentarios.
                break;
            // Si no es 'c-linea' ni 'p-linea' hay un error de formato.
            } else {
                perror("Fomato de entrada invalido.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    // Si los valores leidos son validos creo la estructura y almaceno N y M.
    if(n > 0 && m > 0) {
        grafo = calloc(1, sizeof(struct _grafo_t));
        grafo->n_vertices = n;
        grafo->m_lados = m;
    }

    // Retorna un grafo vacio con N y M inicializadas.
    return (grafo);
}

// Funcion que carga un grafo a partir de vertices y lados leidos desde stdin.
grafo_t cargarGrafoDesdeStdin(grafo_t grafo) {

    char linea[BUFFER_SIZE];

    u32 u = 0;           /* Primer vertice (temporal) leido en cada 'e-linea'. */
    u32 v = 0;                        /* Segundo vertice (temporal) del 'par'. */
    u32 e_lineas = 0;              /* Variable de control para las 'e-lineas'. */

    vertice_t *tmp_vertices = NULL;            /* Arreglo temporal de vertices */

    /*

        Durante el proceso de carga, vamos a utilizar una estructura auxiliar
        'espejo' que almacena de manera temporal cada nueva linea leida desde
        standard input como un lado y su respectivo espejado.
        Esta estructura nos permite manipular los datos de entrada, ordenarlos
        a nuestro antojo y realizar el computo de vecinos y el etiquetado de
        los vertices de manera sencilla.

    */

    // Arreglo aux. de lados espejados. Almacena u-v y v-u para cada 'e-linea'.
    size32 size_espejo = 2 * grafo->m_lados;    /* Long. del arreglo espejado. */
    u32 indice_espejo = 0;        /* Indice para recorrer el arreglo espejado. */
    lado32_t *espejo = calloc(size_espejo, sizeof(struct _lado32_t));


    while(fgets(linea, BUFFER_SIZE, stdin)) {

        // Chequeos parciales de 'e_lineas' leidas y lados espejados parciales.
        assert(e_lineas < grafo->m_lados);
        assert(indice_espejo < size_espejo);

        // Busca las 'e-lineas' con los lados ignorando comentarios.
        if(strncmp(linea, "c", 1)) { 
            // Parsea 'e-linea' y almacena en las variables temporales.
            if(!strncmp(linea, "e", 1)) {
                sscanf(linea, "%*c %u %u", &u, &v);
                // Agrega los lados u-v y v-u al espejo.
                espejo = espejar_lado(&indice_espejo, espejo, u, v);
                e_lineas ++;                         /* Nueva 'e-linea' leida. */
            // Si no es 'c-linea' ni 'p-linea' hay un error de formato.
            } else {
                perror("Fomato de entrada invalido.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    // Chequeos finales.
    assert(e_lineas == grafo->m_lados); 
    assert(indice_espejo == size_espejo);

    // Ordena ascendentemente el espejo segun 1er vertice del par (vertice_u).
    qsort(espejo, size_espejo, sizeof(struct _lado32_t), comparar_vertices_u);

    /* 

        En este punto tenemos el arreglo de lados espejados ordenados de manera
        ascendente segun el primer vertice del 'par' (vertice_u).
        
        Podemos ademas, definir una etiqueta para cada vertice en base al orden
        en que este aparece en el espejo. Generamos asi una biyeccion entre el
        nombre real de un vertice y su etiqueta, guardando ademas, una misma
        relacion para el orden de los vertices. (nombre real ~ etiqueta).

        Para calcular el grado de un vertice, alcanza con contar el numero de
        ocurrencias que tiene el mismo en una de las dos posibles posiciones de
        la estructura lado32_t (vertice_u o vertice_v) a lo largo del arreglo.

        Recorremos el espejo segun el primer vertice de cada par e incrementamos
        por cada nueva aparicion de cada vertice sus respectivos contadores.

        Por ultimo, definimos un coloreo propio inicial donde cada vertice es
        coloreado segun su etiqueta (mas precisamente etiqueta + 1).

    */

    // Conteo y carga de vecinos, etiquetado y coloreo inicial.
    // Alloc de memoria para el arreglo de vertices de nuestro grafo.
    tmp_vertices = calloc(grafo->n_vertices, sizeof(struct _vertice_t));
    // Inicializa el primer vertice del espejo en el arreglo de vertices (*1).
    tmp_vertices[0].nombre = espejo[0].vertice_u;     /* Carga el nombre real. */
    tmp_vertices[0].etiqueta = 0;                    /* Carga primer etiqueta. */
    tmp_vertices[0].color = 1;                        /* Carga con el color 1. */
    u32 tmp_indice = 0;        /* Indice necesario para recorrer tmp_vertices. */

    // Recorre uno a uno los vertices del espejo contando ocurrencias.
    for(int i = 0; i < size_espejo; ++i) {
        // Vertice conocido -> incrementa su grado.
        // La inicializacion (*1) me garantiza que la primera iteracion cae en
        // este caso.
        if(espejo[i].vertice_u == tmp_vertices[tmp_indice].nombre) {
            tmp_vertices[tmp_indice].grado += 1;        /* Grado incrementado. */
        // Vertice nuevo -> agrega a tmp_vertices con grado o valencia = 1.
        } else {
            tmp_indice += 1;      /* Incrementa el indice y agrega el vertice. */
            tmp_vertices[tmp_indice].nombre = espejo[i].vertice_u;
            tmp_vertices[tmp_indice].etiqueta = tmp_indice;       /* Etiqueta. */
            tmp_vertices[tmp_indice].grado = 1;           /* Inicializa grado. */
            tmp_vertices[tmp_indice].color = tmp_indice + 1;       /* Coloreo. */
        }

        /*

            Como paso extra, se renombra cada vertice del espejo con su nueva
            etiqueta.
            A futuro esto sera util para construir los arreglos de vecinos para
            cada vertice. Cada vertice aparece en el arreglo indexado (*2) de
            manera ascendente segun su etiqueta. Si guardamos los vecinos segun
            esta etiqueta, podemos acceder al arreglo de manera constante (*2).

        */

        espejo[i].vertice_u = tmp_indice;  /* Etiquetado (Indice del arreglo). */

    }

    // Un segundo ordenamiento, pero esta vez segun el vertice_v del par, nos
    // facilita el proceso de etiquetado de vecinos que anticipamos.
    qsort(espejo, size_espejo, sizeof(struct _lado32_t), comparar_vertices_v);

    // Etiquetado de vertices_v.
    // Inicializa vertice temporal sobre el cual realiza las comparaciones.
    u32 tmp_vertice = espejo[0].vertice_v;           /* Asegura caer en el if. */
    tmp_indice = 0;        /* El indice que (funciona de etiqueta) vuelve a 0. */
    for(int i = 0; i < size_espejo; ++i) {
        // Lado nuevo -> nueva etiqueta.
        if(espejo[i].vertice_v != tmp_vertice) {
            tmp_indice += 1;                 /* Incremento el indice-etiqueta. */
            tmp_vertice = espejo[i].vertice_v;  /* Actualiza vertice temporal. */
        }
        espejo[i].vertice_v = tmp_indice;    /* Reemplaza nombre por etiqueta. */
    }

    /*
 
        El espejo, por su propiedad espejada (valga la redundancia) nos permite
        realizar la misma lectura de vecinos tomando como vertice 'base' uno de
        tipo vertice_u como asi tambien uno de tipo vertice_v.

        Como vimos, en este punto, tenemos todo el arreglo ordenado de manera
        ascendente segun las etiquetas de los vertices_v. Ademas, los vertices_u
        fueron previamente etiquetados siguiendo el orden de sus nombres reales.

        Cada vertice guarda en su estructura el grado o numero de vecinos.
        Guiandonos en todo esto, podemos inicializar los arreglos de vecinos de
        cada vertice recorriendo el espejo segun vertice_v y agregando para cada
        ocurrencia de este, su correspondiente vecino vertice_u.
        
    */

    // Vecinos.
    tmp_indice = 0;    /* El indice ahora recorrera el espejo (vuelve a cero). */
    for(int i = 0; i < grafo->n_vertices; ++i) {
        // Calloc para cada vertice segun su valencia.
        tmp_vertices[i].vecinos = calloc(tmp_vertices[i].grado, sizeof(u32));
        for(int j = 0; j < tmp_vertices[i].grado; ++j) {
            // Carga los vecinos buscando en las entradas del espejo.
            tmp_vertices[i].vecinos[j] = espejo[tmp_indice].vertice_u;
            tmp_indice += 1;   /* Agrego vecino -> incremento indice temporal. */
        }
    }

    // Finalmente actualizo el grafo con el valor del puntero temporal.
    grafo->arreglo_vertices = tmp_vertices;
    // Libero la estructura temporal espejo.
    free(espejo);

    // Retorna el grafo con los vertices coloreados y vecinos inicializados.
    return (grafo);
}

// Funcion auxiliar para la carga de los lados en la estructura 'espejo'.
lado32_t *espejar_lado(u32 *indice, lado32_t *espejo, u32 u, u32 v) {
    // Carga de lado u-v.
    espejo[*indice].vertice_u = u;
    espejo[*indice].vertice_v = v;
    *indice += 1;
    // Carga de lado espejado v-u.
    espejo[*indice].vertice_v = u;
    espejo[*indice].vertice_u = v;
    *indice += 1;

    return(espejo);                          /* Retorna el espejo actualizado. */
}


// Funciones auxiliares para qsort.
// Compara los vertices de un lado segun el primero del 'par', i.e. vertice_u.
int comparar_vertices_u(const void* a, const void* b) {
      // Casteo argumentos a punteros a la estructura 'lado'.
      lado32_t* lado_a = (lado32_t*) a;
      lado32_t* lado_b = (lado32_t*) b;
      // resultado = 0 -> iguales.
      // resultado < 0 -> lado_a es mas chico.
      // resultado > 0 -> lado_a es mas grande. 
      int resultado = (lado_a -> vertice_u) - (lado_b -> vertice_u);

      return(resultado);
}
// Idem anterior, toma como punto de comparacion el segundo vertice del 'par'.
int comparar_vertices_v(const void* a, const void* b) {

      lado32_t* lado_a = (lado32_t*) a;
      lado32_t* lado_b = (lado32_t*) b;

      int resultado = (lado_a -> vertice_v) - (lado_b -> vertice_v);

      return(resultado);
}

// Idem anterior, toma como punto de comparacion el segundo vertice del 'par'.
int comparar_vertices_nombre_desc(const void* a, const void* b) {

      vertice_t* lado_a = (vertice_t*) a;
      vertice_t* lado_b = (vertice_t*) b;

      int resultado = (lado_b -> nombre) - (lado_a -> nombre);

      return(resultado);
}



int main(void){
	grafo_t grafo = crearGrafoDesdeStdin();
    grafo = cargarGrafoDesdeStdin(grafo);
    for (int i = 0; i < grafo->n_vertices; ++i)
    {
        printf("Vertice %u con %u vecinos y %u color\n", grafo->arreglo_vertices[i].nombre, grafo->arreglo_vertices[i].grado, grafo->arreglo_vertices[i].color);
        for (int j = 0; j < grafo->arreglo_vertices[i].grado; ++j)
        {
            printf("Vecino %u es: %u -> Nombre real: %u \n", j+1, grafo->arreglo_vertices[i].vecinos[j], grafo->arreglo_vertices[grafo->arreglo_vertices[i].vecinos[j]].nombre);
        }
    }
    qsort(grafo->arreglo_vertices, grafo->n_vertices, sizeof(struct _vertice_t), comparar_vertices_nombre_desc);
    printf("SORT DESC NOMBRE REAL\n");
    for (int i = 0; i < grafo->n_vertices; ++i)
    {
        printf("Vertice %u con %u vecinos y %u color\n", grafo->arreglo_vertices[i].nombre, grafo->arreglo_vertices[i].grado, grafo->arreglo_vertices[i].color);
        for (int j = 0; j < grafo->arreglo_vertices[i].grado; ++j)
        {
            printf("Vecino %u es: %u -> Nombre real: %u \n", j+1, grafo->arreglo_vertices[i].vecinos[j], grafo->arreglo_vertices[grafo->arreglo_vertices[i].vecinos[j]].nombre);
        }
    }
	return(0);
}
