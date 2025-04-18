#ifndef HUFFMAN_TREE
#define HUFFMAN_TREE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

#endif