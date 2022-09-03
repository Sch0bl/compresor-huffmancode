#ifndef __BTREE_H__
#define __BTREE_H__

typedef void *(*FuncionCopiadora)(void *);
typedef void (*FuncionDestructora)(void *);
typedef void (*FuncionVisitante)(void *);

typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

struct _BTNodo {
  void *dato;
  struct _BTNodo *izq;
  struct _BTNodo *der;
};

typedef struct _BTNodo *BTree;

/**
 * Devuelve un arbol general vacio.
 */
BTree btree_crear();

/**
 * Destruye el arbol.
 */
void btree_destruir(BTree arbol, FuncionDestructora destr);

/**
 * Determina si el arbol es vacio.
 */
int btree_empty(BTree arbol);

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(void * dato, BTree izq, BTree der, FuncionCopiadora copiar);

/**
 * Recorrido del arbol.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,
                    FuncionVisitante visit);


#endif /** __BTREE_H__ */
