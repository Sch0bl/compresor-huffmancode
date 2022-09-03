#include "huffarbol.h"
#include <stdio.h>

/**
 * Función identidad para manejo de memoria.
 */
static inline void *id(void *dato) {
  return dato;
}

/**
 * Función nula (no libera los punteros) para manejo de memoria.
 */
static inline void null( __attribute__ ((unused))
                        void *data) {
  return;
}

/**
 * Crea los nodos del arbol de huff.
 * (aloca memoria para la estructura _InfoChar y para los caracteres)
 */
BTree crea_hojas_huff(char carc) {
  InfoChar nuevaInfo = malloc(sizeof(struct _InfoChar));
  assert(nuevaInfo != NULL);
  nuevaInfo->carc = (char *) malloc(sizeof(char));
  assert(nuevaInfo->carc != NULL);
  *nuevaInfo->carc = carc;
  nuevaInfo->peso = 0;
  BTree hojaHuff = btree_unir((void *) nuevaInfo, btree_crear(), btree_crear(),
                              id);
  return hojaHuff;
}

/**
 * Destruye la estructura InfoChar.
 * (libera la memoria de los caracteres y de la estructura)
 */
void destruir_info_char(InfoChar inf) {
  free(inf->carc);
  free(inf);
}

/**
 * Compara el peso de los nodos de un arbol de huff. Devuelve un número
 * positivo si el primer dato es mayor que el segundo, devuelve cero si
 * son iguales y un número negativo en caso contrario.
 * Esta función tiene la forma adecuada para usarse en la función qsort.
 */
int compara_hojas_huff_qsort(BTree * hoja1, BTree * hoja2) {
  return ((InfoChar) (*hoja2)->dato)->peso - ((InfoChar) (*hoja1)->dato)->peso;
}

/**
 * Compara el peso de los nodos de un arbol de huff. Devuelve un número
 * positivo si el primer dato es mayor que el segundo, devuelve cero si
 * son iguales y un número negativo en caso contrario.
 * Esta función tiene la forma adecuada para usarse como (FuncionComparadora)
 * en la estructura SGList
 */
int compara_hojas_huff(BTree hoja1, BTree hoja2) {
  return ((InfoChar) hoja1->dato)->peso - ((InfoChar) hoja2->dato)->peso;
}

/**
 * Genera un arreglo con todos los nodos del arbol de huff.
 * (aloca memoria para el arreglo y en la función crea_hojas_huff
 * para la estructura _InfoChar y para los caracteres)
 */
BTree *genera_arreglo_hojas(char *texto, int longi) {
  BTree *arr = malloc((sizeof(BTree) * NUM_CARC));
  assert(arr != NULL);
  for (int i = 0; i < NUM_CARC; i++)
    arr[i] = crea_hojas_huff((char) i);
  for (int j = 0; j < longi; j++) {
    ((InfoChar) arr[(unsigned char) texto[j]]->dato)->peso++;
  }
  return arr;
}

/**
 * Destruye la estructura InfoChar
 * (libera la memoria alocada para _InfoChar y para los caracteres)
 */
void destruye_hojas_huff(BTree hoja) {
  btree_destruir(hoja, (FuncionDestructora) destruir_info_char);
}

/**
 * Genera una lista ordenada con los nodos del arbol de Huff que se encuentran
 * en el arreglo.
 * (aloca memoria para los nodos de la lista pero no para los datos)
 */
SGList genera_lista_ordenada_hojas(BTree * arr, int longi) {
  SGList listaOrdenaHojas = sglist_arr((void **) arr, longi, id,
                                       (FuncionComparadora)
                                       compara_hojas_huff_qsort);
  return listaOrdenaHojas;
}

/**
 * Genera el arbol de Huff a partir de una lista ordenada de las hojas.
 * (libera la memoria alocada para la lista pero no la de sus datos
 * ya que estos se usan en el arbol)
 */
BTree genera_huff_arbol(SGList lista) {
  BTree nuevoNodo, nodoIzq, nodoDer;
  while (lista->sig != NULL) {  //Mientras la lista no tenga un único elemento.
    nodoIzq = sglist_primer_elemento(lista, id);
    lista = sglist_eliminar(lista, null);
    nodoDer = sglist_primer_elemento(lista, id);
    lista = sglist_eliminar(lista, null);
    InfoChar sumaPesos = malloc(sizeof(struct _InfoChar));
    assert(sumaPesos != NULL);
    sumaPesos->carc = NULL;
    sumaPesos->peso = ((InfoChar) nodoIzq->dato)->peso +
        ((InfoChar) nodoDer->dato)->peso;
    nuevoNodo = btree_unir((void *) sumaPesos, nodoIzq, nodoDer, id);
    lista = sglist_insertar(lista, (void *) nuevoNodo,
                            id, (FuncionComparadora) compara_hojas_huff);
  }
  sglist_destruir(lista, null);
  return nuevoNodo;
}

BTree crea_huff_arbol(char *buff, int longi) {
  BTree *arr = genera_arreglo_hojas(buff, longi);
  SGList listaHojas = genera_lista_ordenada_hojas(arr, NUM_CARC);
  BTree arbolHuff = genera_huff_arbol(listaHojas);
  free(arr);
  return arbolHuff;
}

void destruye_huff_arbol(BTree arbolHuff) {
  btree_destruir(arbolHuff, (FuncionDestructora) destruir_info_char);
}
