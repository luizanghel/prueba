all: project

main.o: main.c user.h anuncios.h
	gcc main.c -g -c

linkedlist.o: linkedlist.c linkedlist.h
	gcc linkedlist.c -g -c

dato.o: dato.c dato.h
	gcc dato.c -g -c

pelicula.o: pelicula.c pelicula.h
	gcc pelicula.c -g -c

linkedlistcanales.o: linkedlistcanales.c linkedlistcanales.h
	gcc linkedlistcanales.c -g -c

linkedlistprograma.o: linkedlistprograma.c linkedlistprograma.h
	gcc linkedlistprograma.c -g -c

canales.o: canales.c linkedlistcanales.h linkedlistprograma.h dato.h canales.h
	gcc canales.c -g -c

user.o: user.c linkedlist.h dato.h canales.h dato.h linkedlistcanales.h pelicula.h user.h
	gcc user.c -g -c

linkedlistactores.o: linkedlistactores.c linkedlistactores.h
	gcc linkedlistactores.c -g -c

actors.o: actors.c linkedlistactores.h actors.h canales.h linkedlistprograma.h user.h actors.h
	gcc actors.c -g -c

anuncios.o: anuncios.c anuncios.h linkedlistadvertisements.h
	gcc anuncios.c -g -c

linkedlistadvertisements.o: linkedlistadvertisements.c linkedlistadvertisements.h
	gcc linkedlistadvertisements.c -g -c

project: main.o linkedlist.o user.o presupuesto.o actors.o linkedlistactores.o canales.o linkedlistcanales.o linkedlistprograma.o dato.o anuncios.o linkedlistadvertisements.o pelicula.o
	gcc main.o linkedlist.o user.o presupuesto.o actors.o linkedlistactores.o canales.o linkedlistcanales.o linkedlistprograma.o dato.o anuncios.o linkedlistadvertisements.o pelicula.o -g -o project

gdb: project
	gdb -tui ./project

valgrind: project
	valgrind ./project
