all: project

main.o: main.c linkedlist.h user.h presupuesto.h actors.h linkedlistactores.h canales.h linkedlistcanales.h linkedlistprograma.h dato.h
	gcc main.c -c

user.o: user.c user.h
	gcc user.c -c

presupuesto.o: presupuesto.c presupuesto.h
	gcc presupuesto.c -c

linkedlist.o: linkedlist.c linkedlist.h
	gcc linkedlist.c -c

linkedlistactores.o: linkedlistactores.c linkedlistactores.h
	gcc linkedlistactores.c -c

linkedlistcanales.o: linkedlistcanales.c linkedlistcanales.h
	gcc linkedlistcanales.c -c

dato.o: dato.c dato.h
	gcc dato.c -c

actors.o: actors.c actors.h
	gcc actors.c -c

canales.o: canales.c canales.h
	gcc canales.c -c

project: main.o linkedlist.o user.o presupuesto.o actors.o linkedlistactores.o canales.o linkedlistcanales.o linkedlistprograma.o dato.o
	gcc main.o linkedlist.o user.o presupuesto.o actors.o linkedlistactores.o canales.o linkedlistcanales.o linkedlistprograma.o dato.o -o project
