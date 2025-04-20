runHuffmanTree : compress.o
	gcc -o huffman-tree_exe compress.o
	./huffman-tree_exe 

compress.o : compress.c
	gcc -c compress.c

clean : 
	-rm *.o
	-rm *_exe