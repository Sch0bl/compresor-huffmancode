#ifndef _HUFF_ARBOL_
#define _HUFF_ARBOL_

#define NUM_CARC 256  //Cantidad de caracteres en el código ASCII.

#include <stdlib.h>
#include <assert.h>
#include "../Estructuras/sglist.h"
#include "../Estructuras/btree.h"

struct _InfoChar {
  char *carc;
  int peso;
};

typedef struct _InfoChar* InfoChar;

/**
 * Crea el arbol de Huff a partir del buff a codificar.
 * (aloca memoria para los datos del arbol, tanto el arr como listaHojas
 * son liberados antes de finalizar esta función)
 */
BTree crea_huff_arbol(char* buff, int longi);

/**
 * Destruye el arbol de Huff.
 * (libera la memoria de los datos del arbol)
 */
void destruye_huff_arbol(BTree arbolHuff);

#endif
