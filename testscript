#!/bin/bash

make  #creamos el ejecutable

for files in "$@"
do
  echo "Ejecución del codificador."
  time ./huff C "$files"
  echo "Ejecución del decodificador."
  time ./huff d "$files.hf"
  diff -s "$files" "$files.dec"
  rm ./"$files".{hf,tree,dec} 
done

make clean
