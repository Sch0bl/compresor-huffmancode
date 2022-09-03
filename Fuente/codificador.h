#ifndef _HUFF_COD_
#define _HUFF_COD_

#include "huffarbol.h"
#include "io.h"
#include "../Estructuras/dlist.h"
#include <string.h>

typedef struct _EntradasTabla {
  DLista *codigo;
  int longitud;
  int peso;
} EntradasTabla;

typedef EntradasTabla *Tabla;

/**
 * Escribe en el archivo codificado el texto codificado.
 * (aloca memoria con las funciones crear_tabla y codigos_huff que es
 * liberada con la función destruir_tabla;
 * aloca memoria con crear_buff_codificado y con implode, ambas son liberadas)
 */
void codificar(BTree arbolHuff, char *buff, int longi, char *nombreArch);

#endif
