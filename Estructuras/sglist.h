#ifndef __SGLIST_H__
#define __SGLIST_H__

/**
 * FuncionComparadora retorna un entero negativo si el primer argumento es
 * menor que el segundo, 0 si son iguales, y un entero positivo en caso
 * contrario.
 */
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef void (*FuncionVisitanteExtra)(void *dato, void* datoExtra);

typedef struct _GNodo {
  void *dato;
  struct _GNodo *sig;
} GNodo;

typedef GNodo *SGList;

/**
 * Devuelve una lista vacía.
 */
SGList sglist_crear();

/**
 * Destruye la lista.
 */
void sglist_destruir(SGList lista, FuncionDestructora destr);

/**
 * Determina si la lista es vacía.
 */
int sglist_vacia(SGList lista);

/**
 * Recorre la lista, utilizando la funcion pasada.
 */
void sglist_recorrer(SGList lista, FuncionVisitante visitar);

/**
 * Inserta un nuevo dato en la lista ordenada. La función de comparación es
 * la que determina el criterio de ordenación.
 */
SGList sglist_insertar(SGList lista, void *dato, FuncionCopia copia,
                       FuncionComparadora compara);

/**
 * Busca un dato en la lista ordenada, retornando 1 si lo encuentra y 0
 * en caso contrario.
 */
int sglist_buscar(SGList lista, void *dato, FuncionComparadora compara);

/**
 * Construye una lista ordenada a partir de un arreglo de elementos y su
 * longitud.
 */
SGList sglist_arr(void **arreglo, int n, FuncionCopia copia,
                  FuncionComparadora compara);

/**
 * Retorna una copia del primer elemento de la lista o NULL si la lista es
 * vacía.
 */
void *sglist_primer_elemento(SGList lista, FuncionCopia copia);

/**
 * Elimina el primer elemento de la lista.
 */
SGList sglist_eliminar(SGList lista, FuncionDestructora destr);

#endif /* __SGLIST_H__ */
