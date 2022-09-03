#ifndef _DEC_HUFF_
#define _DEC_HUFF_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Estructuras/btree.h"

/**
 * Escribe en el archivo .dec el texto decodificado del buff.
 */
void decodificar(char* buff, int longi, BTree arbolHuff, char* nombreArch);

#endif
