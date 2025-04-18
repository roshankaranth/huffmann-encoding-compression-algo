#include<stdio.h>
#include<stdbool.h>
#include "encoding.h"

void encoding(FILE* inputFile){
    FILE* fptr = fopen("data_compressed","wb");

    char line[1000];
    while(fgets(line,1000,inputFile)){
        for(int i = 0 ; i < strlen(line)-1; i++){
            int code = encoding_arr[line[i]];
            bool zero = false;
            while(code > 0){
                int bit = code&1;
                if (bit) zero = true;
                
                if(zero){
                    fwrite(bit,1,1,fptr);
                }

                code = code >> 1;
            }
        }
    }
}

void decoding(FILE* data_compressed){
    
}

void main(){
    
}