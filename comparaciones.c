/*
   Funcion que fija las 'reglas' para ordenar el arreglo de lados espejados.
   Ordena ascendentemente segun el primer vertice del par que forman un lado.
*/

int comparar_vertices_u(const void* a, const void* b) {
      // Casteo argumentos a punteros a la estructura 'lado'.
      lado32* lado_a = (lado32*) a;
      lado32* lado_b = (lado32*) b;
      // resultado = 0 -> iguales.
      // resultado < 0 -> lado_a es mas chico.
      // resultado > 0 -> lado_a es mas grande. 
      int resultado = (lado_a -> vertice_u) - (lado_b -> vertice_u);

      return(resultado);
}

int comparar_vertices_v(const void* a, const void* b) {
      // Casteo argumentos a punteros a la estructura 'lado'.
      lado32* lado_a = (lado32*) a;
      lado32* lado_b = (lado32*) b;
      // resultado = 0 -> iguales.
      // resultado < 0 -> lado_a es mas chico.
      // resultado > 0 -> lado_a es mas grande. 
      int resultado = (lado_a -> vertice_v) - (lado_b -> vertice_v);

      return(resultado);
}
