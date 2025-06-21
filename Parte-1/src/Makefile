CC = gcc
CFLAGS = -Wall -O2
OBJ = main.o busca.o util.o

tp3_parte1: $(OBJ)
	$(CC) $(CFLAGS) -o tp3_parte1 $(OBJ)

main.o: main.c busca.h util.h
busca.o: busca.c busca.h
util.o: util.c util.h

clean:
	rm -f *.o tp3_parte1
