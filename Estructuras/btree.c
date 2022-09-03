#include "btree.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

BTree btree_crear() {
  return NULL;
}

void btree_destruir(BTree arbol, FuncionDestructora destr) {
  if (arbol != NULL) {
    btree_destruir(arbol->izq, destr);
    btree_destruir(arbol->der, destr);
    destr(arbol->dato);
    free(arbol);
  }
}

int btree_empty(BTree arbol) {
  return arbol == NULL;
}

BTree btree_unir(void *dato, BTree izq, BTree der, FuncionCopiadora copiar) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = copiar(dato);
  nuevoNodo->izq = izq;
  nuevoNodo->der = der;
  return nuevoNodo;
}

void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,
                    FuncionVisitante visit) {
  if (btree_empty(arbol)) {
    return;
  }
  if (orden == BTREE_RECORRIDO_PRE) {
    visit(arbol->dato);
  }
  btree_recorrer(arbol->izq, orden, visit);
  if (orden == BTREE_RECORRIDO_IN) {
    visit(arbol->dato);
  }
  btree_recorrer(arbol->der, orden, visit);
  if (orden == BTREE_RECORRIDO_POST) {
    visit(arbol->dato);
  }
}

