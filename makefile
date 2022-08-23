
all: busca

busca: main.o lista.o
	gcc -o busca main.o lista.o

main.o: main.c lista.h
	gcc -c main.c

lista.o: lista.c lista.h
	gcc -c lista.c

clean:
	rm -rf *.o busca

