#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "compress.h"
#include "binary.h"
#include "linked.h"

int main(int argc, char ** argv){
    if(argc != 2){
        fprintf(stderr, "!Error must provide file to be decompressed!\nUsage decompress <file.txt.compress>\nQuit\n");
        return EXIT_FAILURE;
    }
    FILE * inFile = fopen(argv[1], "r");
    if(inFile == NULL){
        fprintf(stderr, "!Error provided file could not be opened!\nQuit\n");
        return EXIT_FAILURE;
    }

    //read the header of the compressed file bit by bit and reform the binary tree
    unsigned char whichbit = 8;
    unsigned char curbyte = 0;

    TreeNode * Root = buildTreeFromHeader(inFile, &whichbit, &curbyte);

    FILE * deCompressFile = fopen(strcat(argv[1], ".decompress"),"w");
    if(deCompressFile == NULL){
        fprintf(stderr, "!Error cannot write decompressed output file!\nQuit\n");
        return EXIT_FAILURE;
    }
    
    //read and convert compressed file to normal text
    readBody(deCompressFile, inFile, &whichbit, &curbyte, Root);
    fclose(inFile);
    fclose(deCompressFile);
    FreeTree(Root);
}

void readBody(FILE * outFile, FILE * inFile, unsigned char * whichbit, unsigned char * curbyte, TreeNode * Root){
    int bit;
    TreeNode * tr = Root;
    while(1){
        bit = readBit(inFile, whichbit, curbyte);
        if(bit == 0){
            tr = tr->left;
        }else{
            tr = tr->right;
        }
        if(tr-right  == NULL && tr->left == NULL){
            if(tr->label == (255)){break;}
            fprintf(outFile, "%c", tr->label);
            tr==Root;
        }
    }
}


