# Main project files
projekti: main.o linkedlist.o binarytree.o namelist.o avl_tree.o
	gcc -o projekti main.o linkedlist.o binarytree.o namelist.o avl_tree.o

main.o: main.c linkedlist.h
	gcc -c main.c -std=c99 -pedantic -Wall

linkedlist.o: linkedlist.c linkedlist.h
	gcc -c linkedlist.c -std=c99 -pedantic -Wall

binarytree.o: binarytree.c binarytree.h
	gcc -c binarytree.c -std=c99 -pedantic -Wall

namelist.o: namelist.c namelist.h
	gcc -c namelist.c -std=c99 -pedantic -Wall

avl_tree.o: avl_tree.c avl_tree.h
	gcc -c avl_tree.c -std=c99 -pedantic -Wall

# Test files
test_sorting: test_sorting.o linkedlist.o
	gcc -o test_sorting test_sorting.o linkedlist.o

test_sorting.o: test_sorting.c linkedlist.h
	gcc -c test_sorting.c -std=c99 -pedantic -Wall

binary_tree_tests: binary_tree_tests.o binarytree.o linkedlist.o
	gcc -o binary_tree_tests binary_tree_tests.o binarytree.o linkedlist.o namelist.o

binary_tree_tests.o: binary_tree_tests.c binarytree.h linkedlist.h
	gcc -c binary_tree_tests.c -std=c99 -pedantic -Wall

test: test_sorting binary_tree_tests
	@echo "Running test_sorting:"
	./test_sorting
	@echo "Running binary_tree_tests:"
	./binary_tree_tests