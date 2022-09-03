#include "sglist.h"
#include <assert.h>
#include <stdlib.h>

SGList sglist_crear() {
  return NULL;
}

void sglist_destruir(SGList lista, FuncionDestructora destr) {
  GNodo *nodoADest;
  while (lista != NULL) {
    nodoADest = lista;
    lista = lista->sig;
    destr(nodoADest->dato);
    free(nodoADest);
  }
}

int sglist_vacia(SGList lista) {
  return (lista == NULL);
}

void sglist_recorrer(SGList lista, FuncionVisitante visitar) {
  for (GNodo * nodo = lista; nodo != NULL; nodo = nodo->sig)
    visitar(nodo->dato);
}

SGList sglist_insertar(SGList lista, void *dato, FuncionCopia copia,
                       FuncionComparadora compara) {
  GNodo *nuevoNodo = malloc(sizeof(GNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = copia(dato);
  if (lista == NULL) {
    lista = nuevoNodo;
    nuevoNodo->sig = NULL;
  } else if (compara(lista->dato, dato) >= 0) {
    nuevoNodo->sig = lista;
    lista = nuevoNodo;
  } else {
    GNodo *nodo = lista;
    for (; nodo->sig != NULL && compara((nodo->sig)->dato, dato) < 0;
         nodo = nodo->sig);
    // Estoy parada en el nodo anterior al que debo asignar.
    GNodo *temp = nodo->sig;
    nodo->sig = nuevoNodo;
    nuevoNodo->sig = temp;
  }
  return lista;
}

int sglist_buscar(SGList lista, void *dato, FuncionComparadora compara) {
  int valor = 0;
  if (!sglist_vacia(lista)) {
    GNodo *nodo = lista;
    if (compara(dato, nodo->dato) >= 0) {
      for (; nodo != NULL && valor == 0; nodo = nodo->sig) {
        valor = (compara(dato, nodo->dato) == 0);
      }
    }
  }
  return valor;
}

SGList sglist_arr(void **arreglo, int longitud, FuncionCopia copia,
                  FuncionComparadora compara) {
  qsort(arreglo, longitud, sizeof(void **),
        (int (*)(const void *, const void *)) compara);
  //qsort ordena de manera eficiente en forma creciente.
  SGList lista = sglist_crear();
  for (int i = 0; i < longitud; i++) {
    GNodo *nuevoNodo = malloc(sizeof(GNodo));
    assert(nuevoNodo != NULL);
    nuevoNodo->dato = copia(arreglo[i]);
    nuevoNodo->sig = lista;
    lista = nuevoNodo;
  }
  return lista;
}

void *sglist_primer_elemento(SGList lista, FuncionCopia copia) {
  if (lista == NULL) {
    return NULL;
  } else {
    return copia(lista->dato);
  }
}

SGList sglist_eliminar(SGList lista, FuncionDestructora destr) {
  if (lista != NULL) {
    SGList temp = lista;
    lista = lista->sig;
    destr(temp->dato);
    free(temp);
  }
  return lista;
}
