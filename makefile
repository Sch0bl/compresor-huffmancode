# Makefile para TP_1
# ejecutar desde la terminal escribiendo "make".
# genera automáticamente el ejecutable del programa.

#Banderas de copilacion.
FLAGS = -Wall -Wextra -Werror -std=c99
CC = gcc

#Fuentes de los archivos.
MAIN   = Fuente/main
CODI   = Fuente/codificador
DEC    = Fuente/decodificador
HUFF   = Fuente/huffarbol
SERI   = Fuente/serializador
IO     = Fuente/io
BTREE  = Estructuras/btree
SGLIST = Estructuras/sglist
DLIST  = Estructuras/dlist

FUENTE = $(CODI).o $(DEC).o $(COD) $(HUFF).o $(SERI).o $(IO).o
ESTR   = $(BTREE).o $(SGLIST).o $(DLIST).o


#Generación del ejecutable.
huff: $(MAIN).o $(FUENTE) $(ESTR)
	$(CC) $(FLAGS) -o huff $^

#Genera código objeto
%.o: %.c
	$(CC) -c $(FLAGS) $^ -o $@

#Copila el programa con la opción -g
.PHONY: debug

debug:
	$(CC) -g -o huff $(FLAGS) $(MAIN).c $(CODI).c $(DEC).c $(HUFF).c $(SERI).c \
	$(IO).c $(BTREE).c $(SGLIST).c $(DLIST).c


.PHONY = clean

clean:
	@-rm Fuente/*.o Estructuras/*.o 2>/dev/null || true
	@-rm huff 2>/dev/null || true
	@-rm *.hf 2>/dev/null || true
	@-rm *.tree 2>/dev/null || true
	@-rm *.dec 2>/dev/null || true
