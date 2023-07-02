all:
					gcc -std=c99 main.c handle.c list.c nodearray.c nodetree.c point.c tree.c
					valgrind ./a.out

gen:
					gcc -std=c99 g.c
					./a.out
