#include "huffarbol.h"
#include "codificador.h"
#include "decodificador.h"
#include "serializador.h"


int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Parámatros incorrectos...\n");
    exit(1);
  }
  int longi[1];
  if (strcmp(argv[1], "c") == 0 || strcmp(argv[1], "C") == 0) {
    char *buff = readfile(argv[2], longi);
    BTree arbolHuff = crea_huff_arbol(buff, *longi);
    codificar(arbolHuff, buff, *longi, argv[2]);
    serializar(arbolHuff, argv[2]);
    destruye_huff_arbol(arbolHuff);
    free(buff);
    printf("Codificación exitosa.\n");
  } else if (strcmp(argv[1], "d") == 0 || strcmp(argv[1], "D") == 0) {
    int longii[1];
    char *nombreArch = argv[2];
    int len = strlen(argv[2]);
    char *textoImplotado = readfile(argv[2], longi);
    nombreArch[len - 3] = 0;
    char *buffSer = readfile(strcat(nombreArch, ".tree"), longii);
    nombreArch[len - 3] = 0;
    char *textoCodificado = explode(textoImplotado, *longi, longii);
    BTree arbolParseado = parsear(buffSer);
    decodificar(textoCodificado, *longii, arbolParseado, nombreArch);
    btree_destruir(arbolParseado, free);
    free(buffSer);
    free(textoImplotado);
    free(textoCodificado);
    printf("Decodificación exitosa.\n");
  } else {
    fprintf(stderr, "Opción incorrecta, ingrese C o D.\n");
    exit(1);
  }
  return 0;
}
