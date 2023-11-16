all: project

main.o: main.c linkedlist.h user.h presupuesto.h
	gcc main.c -c

user.o: user.c user.h
	gcc user.c -c

presupuesto.o: presupuesto.c presupuesto.h
	gcc presupuesto.c -c

linkedlist.o: linkedlist.c linkedlist.h
	gcc linkedlist.c -c

project: main.o linkedlist.o user.o presupuesto.o
	gcc main.o linkedlist.o user.o presupuesto.o -o project
