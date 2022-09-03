#ifndef __DLIST_H__
#define __DLIST_H__

typedef void (*FuncionDestruir)(void *);
typedef void (*FuncionVisitar)(void *);
typedef void *(*FuncionCopiar)(void *);

typedef enum {
  DLIST_RECORRIDO_HACIA_ADELANTE,
  DLIST_RECORRIDO_HACIA_ATRAS
} DListaOrdenDeRecorrido;

typedef struct _DNodo {
  void *dato;
  struct _DNodo *sig;
  struct _DNodo *ant;
} DNodo;

typedef struct {
  DNodo *primero;
  DNodo *ultimo;
} DLista;

/**
 * Devuelve una lista vacía.
 */
DLista dlist_crear();

/**
 * Determina si la lista es vacía.
 */
int dlist_vacia(DLista lista);

/**
 * Destruye de la lista.
 * (destruye cada nodo)
 */
void dlist_destruir(DLista lista, FuncionDestruir destruir);

/**
 * Recorre la lista, utilizando la funcion y el orden pasados.
 */
void dlist_recorrer(DLista lista, FuncionVisitar visitar,
                    DListaOrdenDeRecorrido orden);

/**
 * Agrega un elemento al inicio de la lista.
 * (aloca memoria para el nodo)
 */
DLista dlist_insertar_inicio(DLista lista, void *dato, FuncionCopiar copiar);

/**
 * Agrega un elemento al final de la lista.
 * (aloca memoria para el nodo)
 */
 DLista dlist_insertar_final(DLista lista, void *dato, FuncionCopiar copiar);

/**
 * Retorna el dato de la posición dada, o NULL si es la lista vacía.
 * Si pos >= largo(lista), retorna el dato del ultimo nodo.
 */
void *dlist_dato(DLista lista, unsigned int pos, FuncionCopiar copiar);

/**
 * Elimina el nodo de la posición dada.
 * Si pos >= largo(lista), elimina el último nodo.
 */
DLista dlist_eliminar(DLista lista, unsigned int pos, FuncionDestruir destruir);

/**
 * Devuelve una copia de la lista en orden reverso.
 */
DLista dlist_copiar_reversa(DLista lista, FuncionCopiar copia);

#endif
