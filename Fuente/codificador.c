#include "codificador.h"

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
 * Copia los datos de la lista en el buff pasado desde la posición,
 * al finalizar el entero pos apunta a la próxima posición a sin escribir.
 */
static inline void copiar_en_buff(DLista lista, char *buff, int *pos) {
  for (DNodo * nodo = lista.primero; nodo != NULL; nodo = nodo->sig) {
    buff[*pos] = *(char *) nodo->dato;
    *pos += 1;
  }
}

/**
 * Crea la tabla vacía con el tamaño correspondiente para utilizar en nuestro
 * codificador.
 * (aloca memoria para la tabla, para las NUM_CARC entradas de la misma y
 * para las listas de cada entrada)
 */
Tabla *crear_tabla() {
  Tabla *tabla = malloc(sizeof(Tabla) * NUM_CARC);
  assert(tabla != NULL);
  for (int i = 0; i < NUM_CARC; i++) {
    tabla[i] = (Tabla) malloc(sizeof(EntradasTabla));
    assert(tabla[i] != NULL);
    tabla[i]->codigo = (DLista *) malloc(sizeof(DLista));
    assert(tabla[i]->codigo != NULL);
  }
  return tabla;
}

/**
 * Destruye la tabla.
 * (libera la memoria pedida para crear la tabla y la memoria que se aloca
 * para cada código en la función busca_codigos)
 */
void destruir_tabla(Tabla * tabla) {
  for (int i = 0; i < NUM_CARC; i++) {
    dlist_destruir(*tabla[i]->codigo, free);
    free(tabla[i]->codigo);
    free(tabla[i]);
  }
  free(tabla);
}

/**
 * Recorre el arbol hasta que encuentra una hoja y en una tabla guarda el
 * código de cada hoja con su peso y la longitud del código.
 * (aloca memoria al insertar elementos en tempCodigo y luevo la libera
 * al eliminar esos elementos, aloca memoria con la función dlist_copiar_reversa
 * y esta queda guardada en cada puntero de la tabla que apunta a un codigo)
 **/
void busca_codigos(BTree arbolHuff, Tabla * tabla, DLista * tempCodigo,
                   char *carcs, int *longitud) {
  if (((InfoChar) arbolHuff->dato)->carc != NULL) {
    char caracter = *((InfoChar) arbolHuff->dato)->carc;
    *tabla[(unsigned char) caracter]->codigo =
      dlist_copiar_reversa(*tempCodigo, copia_caracter);
    (*tabla[(unsigned char) caracter]).peso =
      ((InfoChar) arbolHuff->dato)->peso;
    (*tabla[(unsigned char) caracter]).longitud = *longitud;
  } else {
    *longitud += 1;
    *tempCodigo = dlist_insertar_inicio(*tempCodigo, carcs, copia_caracter);
    busca_codigos(arbolHuff->izq, tabla, tempCodigo, carcs, longitud);
    *tempCodigo = dlist_eliminar(*tempCodigo, 0, free);
    *tempCodigo = dlist_insertar_inicio(*tempCodigo, carcs + 1, copia_caracter);
    busca_codigos(arbolHuff->der, tabla, tempCodigo, carcs, longitud);
    *tempCodigo = dlist_eliminar(*tempCodigo, 0, free);
    *longitud -= 1;
  }
}

/**
 * Rellena una tabla vacía con los datos para codificar porporcionados por
 * el arbolHuff.
 * (aloca la memoria que se requiere en busca_codigos)
 */
void codigos_huff(BTree arbolHuff, Tabla * tabla, char *binario) {
  DLista tempCodigo = dlist_crear();
  int n = 0;
  busca_codigos(arbolHuff, tabla, &tempCodigo, binario, &n);
}

/**
 * Devuelve el tamaño del buff del texto codificado.
 */
int longitud_buff_codificado(Tabla * tabla) {
  int tam = 0;
  for (int i = 0; i < NUM_CARC; i++) {
    tam += (*tabla[i]).peso * (*tabla[i]).longitud;
  }
  return tam;
}

/**
 * Crea el buff codificado con su contenido.
 * (aloca la memoria necesaria para el buff codificado)
 */
char *crear_buff_codificado(Tabla * tabla, char *buff, int longi,
                            int *longiBuffCodificado) {
  *longiBuffCodificado = longitud_buff_codificado(tabla);
  char *buffCodificado = malloc(sizeof(char) * (*longiBuffCodificado));
  assert(buffCodificado != NULL);
  DLista tempCodigo;
  int ultimaPos = 0;
  for (int i = 0; i < longi; i++) {
    tempCodigo = *tabla[(unsigned char) buff[i]]->codigo;
    copiar_en_buff(tempCodigo, buffCodificado, &ultimaPos);
  }
  return buffCodificado;
}

void codificar(BTree arbolHuff, char *buff, int longi, char *nombreArch) {
  int len = strlen(nombreArch);
  char binario[2] = { '0', '1' };
  Tabla *tabla = crear_tabla();
  codigos_huff(arbolHuff, tabla, binario);
  int longiBuffCodificado = 0;
  char *buffCodificado = crear_buff_codificado(tabla, buff, longi,
                                               &longiBuffCodificado);
  destruir_tabla(tabla);
  int ilen;
  char *icodificado = implode(buffCodificado, longiBuffCodificado, &ilen);
  writefile(strcat(nombreArch, ".hf"), icodificado, ilen);
  nombreArch[len] = 0;
  free(buffCodificado);
  free(icodificado);
}
