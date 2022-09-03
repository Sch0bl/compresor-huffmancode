Trabajo práctico Codificación de Huffman.

EJECUCIÓN DEL PROGRAMA.

Utilizar el comando "make" para generar el ejecutable.

TESTEOS.

Todas las funciones fueron testeadas durante la creación del programa y, una 
vez finalizado el mismo, este fue testeado con archivos de distintos tamaño y
tipo. Por ejemplo, imágenes, .pdf, textos, binarios, ejecutables, entre otros.

El script "testscript" que se encuentra en el archivo pude utilizarse para tes_
tear múlitple archivos a la vez. Para utilizarlo, ingrese en la consola bash

user-pc-$ ./testscript "filepath1" "filepath2" ...

Ejemplo. ./testscript ArchivosPruebas/*

El script genera el ejecutable, comprime, descomprime y compara
todos los archivos ingresados por paramatros con el comando "diff". Los archi_
vos generados en el proceso son limpiados. También muestra el tiempo de ejecu_
ción de cada archivo.

ELECCIONES DE ESTRUCTURAS

/*********** Listas ordenadas simplemente elazadas generales ***************/

La idea detras de la utilización de esta estructura es la simplicidad con la 
que nos permite armar el arbol de Huff, ya que nos deja guardar las hojas del
arbol en orden creciente. Esto nos permite trabajar de manera simple con los
nodos con menor peso, unirlos en un nuevo nodo y volver ingresarlos hasta
que el arbol quede completo.


/*****************    Listas doblemente elazadas generales    ***************/

Las listas doblemente enlazadas nos permiten guardar las información de los 
codigos asociados de manera sencilla. Cuando recorremos el arbol, usamos las
listas como "pilas" guardando un "0" o un "1" a medida que avanzamos las ramas
del arbol y sacándo estos útimos cuando volvemos a los nodos. Luego, recorremos 
la lista asociada a cada char para obtener su codificación correspondiente.

CONCLUSIONES

La realización de este trabajo práctico fue entretenida, nos permitió adentrar_
nos en el mundo de la compresión, entender que todos los archivos son solo se_
cuencias de 1 y 0, entender la utilidad detras de los arboles binarios y aprender
un poco mas del apasianante mundo de las ciencias de la computación.   
