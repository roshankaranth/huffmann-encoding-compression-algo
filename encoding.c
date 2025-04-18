#include "encoding.h"

void recursiveTraverse(int binary_encoding, Node* node){
    if(node == NULL) return;

    recursiveTraverse(binary_encoding*2, node->left);
    recursiveTraverse(binary_encoding*2 + 1, node->right);

    encoding_arr[(int)node->data] = binary_encoding;
}

void encoding(Node* root){
    recursiveTraverse(0,root);
}
