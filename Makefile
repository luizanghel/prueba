CC = gcc
CFLAGS = -Wall

all: canales

mi_programa: main.o canales.o
    $(CC) $(CFLAGS) $^ -o $@

main.o: main.c canales.h
    $(CC) $(CFLAGS) -c $< -o $@

canales.o: canales.c canales.h
    $(CC) $(CFLAGS) -c $< -o $@
