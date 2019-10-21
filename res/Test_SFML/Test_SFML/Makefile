CC=g++
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
EXEC=sfml-app

all: $(EXEC)

sfml-app: testpokemon.o
	$(CC) -o sfml-app testpokemon.o $(LDFLAGS)

testpokemon.o: testpokemon.cpp
	$(CC) -o testpokemon.o -c testpokemon.cpp $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
