all: project

main.o: main.c linkedlist.h user.h
	gcc main.c -c

user.o: user.c user.h
	gcc user.c -c

linkedlist.o: linkedlist.c linkedlist.h
	gcc linkedlist.c -c

project: main.o linkedlist.o user.o
	gcc main.o linkedlist.o user.o -o project
