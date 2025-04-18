#include "min-heap.h"

Heap* heap_create(){
    Heap* h = (Heap*)malloc(sizeof(Heap));

    h->data = (Element*)malloc(sizeof(int));
    h->size = 0;
    h->capacity = 1;
    h->depth = 0;

    return h;
}

int power(int a, int n){
    int res = 1;
    for(int i = 0 ; i < n ; i++){
        res *= a;
    }

    return res;
}

void add_to_tree(Heap* h, Element val){
    
    if(h->capacity == h->size){
        h->depth++;
        h->data = (Element*)realloc(h->data,sizeof(Element)*(power(2,h->depth+1) -1));
        h->capacity = power(2,h->depth+1)-1;

    }

    h->data[h->size] = val;
    h->size++;

}

int parent(Heap* h, int node){
    return (node-1)/2;
}

int left_child(Heap* h, int node){
    return 2*(node) + 1;
}

int right_child(Heap* h, int node){
    return 2*(node) + 2;
}

// void display(Heap* h){
//     for(int i = 0 ; i < h->size ; i++){
//         printf("%d ",h->data[i]);
//     }
//     printf("\n");
// }

void max_heapify(Heap* h, int index){
    
    int left = left_child(h,index);
    int right = right_child(h,index);
    int smallest = index;

    if(left < h->size && h->data[left].freq > h->data[smallest].freq){
        smallest = left;
    }

    if(right < h->size && h->data[right].freq > h->data[smallest].freq){
        smallest = right;
    }

    if(smallest != index){
        Element temp = h->data[index];
        h->data[index] = h->data[smallest];
        h->data[smallest] = temp;
        max_heapify(h,smallest);
    }
}

Heap* build_max_heap(Heap* h){
    int size =h->size;

    for(int i = h->size-1 ; i>= 0 ;i--){
        max_heapify(h,i);
    }

    return h;
}

void increase_key(Heap* h, int x, Element k)
{
    h->data[x] = k;
    // Complete the function here
    int iparent = parent(h,x);
    int index = x;

    if(iparent >= 0 && h->data[iparent].freq < h->data[index].freq){
        index = iparent;
    }

    if(index != x){
        h->data[x] = h->data[iparent];
        h->data[iparent] = k;
        increase_key(h,iparent,k);
    }

    return;
}

void insert(Heap* h, Element value)
{
    add_to_tree(h, value);
    // Complete the function here
    increase_key(h,h->size-1,value);
    return;
}

Element maximum(Heap* h)
{
        return h->data[0];
}

Element extract_maximum(Heap* h)
{
    Element max = maximum(h);
    // Complete the function here
    h->data[0] = h->data[h->size-1];
    h->size--;
    max_heapify(h,0);

    return max;
}

int isEmpty(Heap* h){
    if(h->size == 0) return 1;
    return 0;
}



