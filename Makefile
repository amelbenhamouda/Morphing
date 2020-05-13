# Makefile Projet
CFLAGS = -ansi -Wall -lMLV

Morphing: bin/main.o bin/graphique.o bin/action.o bin/mecanique.o bin/Delaunay.o
	gcc -o Morphing bin/main.o bin/graphique.o bin/action.o bin/mecanique.o bin/Delaunay.o $(CFLAGS)

bin/graphique.o: ./src/graphique.c ./include/graphique.h ./include/mecanique.h
	gcc -c ./src/graphique.c $(CFLAGS) -o bin/graphique.o

bin/action.o: ./src/action.c ./include/action.h ./include/mecanique.h ./include/graphique.h
	gcc -c ./src/action.c $(CFLAGS) -o bin/action.o

bin/mecanique.o: ./src/mecanique.c ./include/mecanique.h
	gcc -c ./src/mecanique.c $(CFLAGS) -o bin/mecanique.o

bin/main.o: src/main.c ./include/graphique.h ./include/Delaunay.h ./include/mecanique.h ./include/action.h
	gcc -c src/main.c $(CFLAGS) -o bin/main.o
bin/Delaunay.o: ./src/Delaunay.c ./include/Delaunay.h
	gcc -c src/Delaunay.c $(CFLAGS) -o bin/Delaunay.o
clean:
	-rm bin/*.o
	-rm Morphing
