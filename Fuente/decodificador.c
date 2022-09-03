#include "decodificador.h"

void decodificar(char *buff, int longi, BTree arbolHuff, char *nombreArch) {
  int len = strlen(nombreArch);
  FILE *archivo = fopen(strcat(nombreArch, ".dec"), "wb");
  if (archivo == NULL) {
    fprintf(stderr, "Error de archivo.dec");
    exit(1);
  }
  BTree arbolAux;
  for (int i = 0; i < longi;) {
    arbolAux = arbolHuff;
    while (arbolAux->dato == NULL) {
      if (buff[i] == '0')
        arbolAux = arbolAux->izq;
      else
        arbolAux = arbolAux->der;
      i++;
    }
    fputc(*(char *) arbolAux->dato, archivo);
  }
  nombreArch[len] = 0;
  fclose(archivo);
}
