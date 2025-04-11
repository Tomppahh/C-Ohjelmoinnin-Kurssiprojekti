# Main project files
projekti: main.o linkedlist.o binarytree.o namelist.o avl_tree.o rb_tree.o balance_tree.o graph.o
	gcc -o projekti main.o linkedlist.o binarytree.o namelist.o avl_tree.o rb_tree.o balance_tree.o graph.o

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

rb_tree.o: rb_tree.c rb_tree.h
	gcc -c rb_tree.c -std=c99 -pedantic -Wall

balance_tree.o: balance_tree.c balance_tree.h
	gcc -c balance_tree.c -std=c99 -pedantic -Wall

graph.o: graph.c graph.h
	gcc -c graph.c -std=c99 -pedantic -Wall

# Test files
test_sorting: test_sorting.o linkedlist.o
	gcc -o test_sorting test_sorting.o linkedlist.o

test_sorting.o: test_sorting.c linkedlist.h
	gcc -c test_sorting.c -std=c99 -pedantic -Wall

binary_tree_tests: binary_tree_tests.o binarytree.o linkedlist.o
	gcc -o binary_tree_tests binary_tree_tests.o binarytree.o linkedlist.o namelist.o

binary_tree_tests.o: binary_tree_tests.c binarytree.h linkedlist.h
	gcc -c binary_tree_tests.c -std=c99 -pedantic -Wall

graph_tests: graph_tests.o graph.o linkedlist.o
	gcc -o graph_tests graph_tests.o graph.o linkedlist.o

graph_tests.o: graph_tests.c graph.h linkedlist.h
	gcc -c graph_tests.c -std=c99 -pedantic -Wall

test: test_sorting binary_tree_tests graph_tests
	@echo "Running test_sorting:"
	./test_sorting
	@echo "Running binary_tree_tests:"
	./binary_tree_tests
	@echo "Running graph_tests:"
	./graph_tests