projekti: projekti.o linkedlist.o
	->	gcc -o projekti projekti.o linkedlist.o
projekti.o: projekti.c linkedlist.h
	->	gcc -c projekti.c -std=c99 -pedantic -Wall
linkedlist.o: linkedlist.c linkedlist.h
	->	gcc -c linkedlist.c -std=c99 -pedantic -Wall

