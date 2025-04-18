runHuffmanTree : huffman-tree.o min-heap.o 
	gcc -o huffman-tree_exe huffman-tree.o min-heap.o
	./huffman-tree_exe 

huffman-tree.o : huffman-tree.c
	gcc -c huffman-tree.c

min-heap.o : min-heap.c
	gcc -c min-heap.c

clean : 
	rm *.o
	rm *_exe