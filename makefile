
all: busca

busca: main.o lista.o fila.o
	gcc -o busca main.o lista.o fila.o

main.o: main.c lista.h fila.h
	gcc -c main.c

lista.o: lista.c lista.h
	gcc -c lista.c

clean:
	rm -rf *.o busca

