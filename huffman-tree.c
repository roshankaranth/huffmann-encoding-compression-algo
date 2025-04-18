#include "huffman-tree.h"
#include "min-heap.h"

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

// void main(){
//     FILE *fptr = fopen("input.txt","r");

//     if(!fptr){
//         printf("Error opening file!");
//         return;
//     }

//     int characterSet[128];
//     for(int i = 0 ; i < 128 ; i++){
//         characterSet[i] = 0;
//     }

//     char line[1000];
//     while(fgets(line,1000,fptr)){
//         for(int i = 0 ; i < strlen(line)-1; i++){
//             characterSet[line[i]]++;
//         }
//     }

//     Heap* h = heap_create();

//     for(int i = 0 ; i < 128 ; i++){
//         if(characterSet[i] == 0) continue;
//         Node* newNode = createNode((char)i);
//         Element element = createElement(characterSet[i],newNode);

//         insert(h,element);
//     }

//     build_max_heap(h);

//     while(h->size > 1){
//         Element e1 = extract_maximum(h);
//         Element e2 = extract_maximum(h);

//         Node* newNode = createNode(' ');
//         newNode->right = e2.node;
//         newNode->left = e1.node;

//         Element newEle = createElement(e1.freq + e2.freq, newNode);
//         insert(h,newEle);
//     }

//     Element ele = extract_maximum(h);

// }