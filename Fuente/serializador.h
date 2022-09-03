#ifndef _SER_COD_
#define _SER_COD_

#define NUM_NODOS (2 * NUM_CARC - 1) + NUM_CARC //Cantidad de nodos del árbol.

#include "huffarbol.h"
#include "io.h"
#include <string.h>


/**
 * Dado un arbol de Huff escribe su serialización en un archivo.
 */
void serializar(BTree arbolHuff, char* nombreArch);

/**
 * Dado un buff con la serialización retorna el arbol de Huff.
 */
BTree parsear(char *buff);

#endif
