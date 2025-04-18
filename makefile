runHuffmanTree : huffman-tree.o min-heap.o encoding.o compress.o
	gcc -o huffman-tree_exe huffman-tree.o min-heap.o encoding.o compress.o
	./huffman-tree_exe 

compress.o : compress.c
	gcc -c compress.c

encoding.o : encoding.c
	gcc -c encoding.c

huffman-tree.o : huffman-tree.c
	gcc -c huffman-tree.c

min-heap.o : min-heap.c
	gcc -c min-heap.c

clean : 
	rm *.o
	rm *_exe