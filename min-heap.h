#ifndef MIN_HEAP
#define MIN_HEAP

#include<stdio.h>
#include<stdlib.h>
#include"huffman-tree.h"

typedef struct heap{
    Element* data;
    int size;
    int capacity;
    int depth;
}Heap;


Heap* heap_create();
void insert(Heap* h, Element val);
Heap* build_max_heap(Heap* h);
Element extract_maximum(Heap* h);
Element maximum(Heap* h);

#endif