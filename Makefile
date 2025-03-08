main: main.o linkedlist.o
	gcc -o projekti main.o linkedlist.o
main.o: main.c linkedlist.h
	gcc -c main.c -std=c99 -pedantic -Wall
linkedlist.o: linkedlist.c linkedlist.h
	gcc -c linkedlist.c -std=c99 -pedantic -Wall

