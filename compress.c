#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

#define ALPHABET_SIZE 128
int encoding_arr[ALPHABET_SIZE];

typedef struct node Node;

struct node{
    char data;
    Node* right;
    Node* left;

};

typedef struct element{
    int freq;
    Node* node;
}Element;

typedef struct heap{
    Element* data;
    int size;
    int capacity;
    int depth;
}Heap;

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

void min_heapify(Heap* h, int index){
    
    int left = left_child(h,index);
    int right = right_child(h,index);
    int smallest = index;

    if(left < h->size && h->data[left].freq < h->data[smallest].freq){
        smallest = left;
    }

    if(right < h->size && h->data[right].freq < h->data[smallest].freq){
        smallest = right;
    }

    if(smallest != index){
        Element temp = h->data[index];
        h->data[index] = h->data[smallest];
        h->data[smallest] = temp;
        min_heapify(h,smallest);
    }
}

Heap* build_min_heap(Heap* h){
    int size =h->size;

    for(int i = h->size-1 ; i>= 0 ;i--){
        min_heapify(h,i);
    }

    return h;
}

void decrease_key(Heap* h, int x, Element k)
{
    h->data[x] = k;
    // Complete the function here
    int iparent = parent(h,x);
    int index = x;

    if(iparent >= 0 && h->data[iparent].freq > h->data[index].freq){
        index = iparent;
    }

    if(index != x){
        h->data[x] = h->data[iparent];
        h->data[iparent] = k;
        decrease_key(h,iparent,k);
    }

    return;
}

void insert(Heap* h, Element value)
{
    add_to_tree(h, value);
    // Complete the function here
    decrease_key(h,h->size-1,value);
    return;
}

Element minimum(Heap* h)
{
        return h->data[0];
}

Element extract_minimum(Heap* h)
{
    Element min = minimum(h);
    // Complete the function here
    h->data[0] = h->data[h->size-1];
    h->size--;
    min_heapify(h,0);

    return min;
}

int isEmpty(Heap* h){
    if(h->size == 0) return 1;
    return 0;
}

void recursiveTraverse(int binary_encoding, Node* node){
    if(node == NULL) return;

    recursiveTraverse(binary_encoding*2, node->left);
    recursiveTraverse(binary_encoding*2 + 1, node->right);

    encoding_arr[(int)node->data] = binary_encoding;
}

void huffmannEncoding(Node* root){
    recursiveTraverse(0,root);
}

Node* createNode(char ch){
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = ch;
    temp->right = NULL;
    temp->left = NULL;

    return temp;
}

Element createElement(int freq, Node* node){
    Element e;
    e.freq = freq;
    e.node = node;

    return e;
}

Node* createHuffmanTree(FILE* fptr){

    if(!fptr){
        printf("Error opening file!");
        return NULL;
    }

    int characterSet[128];
    for(int i = 0 ; i < 128 ; i++){
        characterSet[i] = 0;
    }

    char line[1000];
    while(fgets(line,1000,fptr)){
        for(int i = 0 ; i < strlen(line)-1; i++){
            characterSet[line[i]]++;
        }
    }

    Heap* h = heap_create();

    for(int i = 0 ; i < 128 ; i++){
        if(characterSet[i] == 0) continue;
        Node* newNode = createNode((char)i);
        Element element = createElement(characterSet[i],newNode);

        insert(h,element);
    }

    build_min_heap(h);

    while(h->size > 1){
        Element e1 = extract_minimum(h);
        Element e2 = extract_minimum(h);

        Node* newNode = createNode(' ');
        newNode->right = e2.node;
        newNode->left = e1.node;

        Element newEle = createElement(e1.freq + e2.freq, newNode);
        insert(h,newEle);
    }

    Element ele = extract_minimum(h);
    return ele.node;
}

FILE* encoding(FILE* inputFile){
    FILE* fptr = fopen("data_compressed.bin","wb");
    
    char ch;
    char buffer = (char)0;
    int left = 8;
    while((ch = (char)fgetc(inputFile)) != EOF){
        int code = encoding_arr[ch];
        int index = 7;
        while((((code>>index) & 1) == 0) && index >= 0){
            index--;
        } 

        if(index == -1){
            left--;
            if(left==0){

                fputc(buffer,fptr);
                buffer = (char)0;
                left = 8;
            }
        }else{
            while(index >= 0){
                buffer = buffer|(((code>>index) & 1)<<(left-1));
                index--;
                left--;
                if(left==0){
    
                    fputc(buffer,fptr);
                    buffer = (char)0;
                    left = 8;
                }
            }
        }
    }
    if(left != 8) fputc(buffer,fptr);

    return fptr;
}

void decoding(FILE* data_compressed, Node* root){
    
}

void main(){
    
    FILE* fptr = fopen("input.txt","r");
    if(fptr == NULL){
        printf("Error opening file!");
        return;
    }

    Node* rootHuffmanTree = createHuffmanTree(fptr); 
    recursiveTraverse(0,rootHuffmanTree);
    fseek(fptr,0,SEEK_SET);
    //encoding input file
    FILE* outputFile = encoding(fptr);
    // //decoding compressed file
    //decoding(outputFile, rootHuffmanTree);
}