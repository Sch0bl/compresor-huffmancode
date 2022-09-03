#include "serializador.h"

/**
 * Genera una copia de un puntero a char.
 */
static inline void *copia_caracter(void *dato) {
  char *nuevoDato = malloc(sizeof(char));
  assert(nuevoDato != NULL);
  nuevoDato[0] = *(char *) dato;
  return nuevoDato;
}

/**
 * Función identidad para manejo de memoria.
 */
static inline void *id(void *dato) {
  return dato;
}


/**
 * Función auxiliar para función serializar.
 */
void serializar_aux(BTree arbolHuff, char *arbol, int *posArbol, int *posHojas) {
  if (arbolHuff->izq == NULL) {
    arbol[*posArbol] = '1';
    *posArbol += 1;
    arbol[*posHojas] = *((InfoChar) arbolHuff->dato)->carc;
    *posHojas += 1;
  } else {
    arbol[*posArbol] = '0';
    *posArbol += 1;
    serializar_aux(arbolHuff->izq, arbol, posArbol, posHojas);
    serializar_aux(arbolHuff->der, arbol, posArbol, posHojas);
  }
}

void serializar(BTree arbolHuff, char *nombreArch) {
  int len = strlen(nombreArch);
  char *arbol = malloc(sizeof(char) * NUM_NODOS);
  assert(arbol != NULL);
  int posArbol = 0;
  int posHojas = NUM_NODOS - NUM_CARC;
  serializar_aux(arbolHuff, arbol, &posArbol, &posHojas);
  writefile(strcat(nombreArch, ".tree"), arbol, NUM_NODOS);
  nombreArch[len] = 0;
  free(arbol);
}

/**
 * Función auxiliar para función parsear.
 */
BTree parsear_aux(BTree arbol, char *buff, int *posArbol, int *posHojas) {
  if (buff[*posArbol] == '0') {
    *posArbol += 1;
    arbol = btree_unir(NULL, btree_crear(), btree_crear(), id);
    arbol->izq = parsear_aux(arbol->izq, buff, posArbol, posHojas);
    arbol->der = parsear_aux(arbol->der, buff, posArbol, posHojas);
  } else {
    char dato = buff[*posHojas];
    arbol = btree_unir((void *) &dato, NULL, NULL,
                       (FuncionCopiadora) copia_caracter);
    *posHojas += 1;
    *posArbol += 1;
  }
  return arbol;
}

BTree parsear(char *buff) {
  int posArbol = 0;
  int posHojas = NUM_NODOS - NUM_CARC;
  BTree arbol = btree_crear();
  arbol = parsear_aux(arbol, buff, &posArbol, &posHojas);
  return arbol;
}
