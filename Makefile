main: main.o linkedlist.o binarytree.o
	gcc -o projekti main.o linkedlist.o binarytree.o
main.o: main.c linkedlist.h
	gcc -c main.c -std=c99 -pedantic -Wall
linkedlist.o: linkedlist.c linkedlist.h
	gcc -c linkedlist.c -std=c99 -pedantic -Wall
binarytree.o: binarytree.c binarytree.h
	gcc -c binarytree.c -std=c99 -pedantic -Wall
