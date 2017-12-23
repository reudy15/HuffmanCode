#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "compress.h"
#include "linked.h"
#include "binary.h"

int main(int argc, char ** argv){
    if (argc != 2){
        fprintf(stderr, "!Must provide file to be compressed!\nUsage compress <file.txt>\n");
        return EXIT_FAILURE;
    }
    FILE * inFile = fopen(argv[1], "r");
    if(inFile == NULL){
        fprintf(stderr, "Error could not open the provided file\n Quit\n");
        return EXIT_FAILURE;
    }

    //count the frequency of the ascii values within the given file 
    long *asciiFreq = freqASCII(inFile);

    //pseudo end of file marker 
    asciiFreq[255]=1;
    
    //create linked list of present ascii values by frequency appeared
    ListNode * head = NULL;
    for(int i=0; i<ASCII_SIZE; i++){
        if(asciiFreq[i] != 0){
            ListNode * newNode = createNode(asciiFreq[i],i);
            insertNode(&head, newNode);
        }
    }
    free(asciiFreq);

    //create binary tree from the LinkedList
    TreeNode * Root = buildTreeFromLL(head);

    FILE * compressedFile = fopen(strcat(argv[1], ".compress"), "wb");
    if (compressedFile == NULL){
        fprintf(stderr, "Error! Cannot write to compressed output file\nQuit\n");
        return EXIT_FAILURE;
    }
    
    //writting the head of the compressed file bit by bit to new file
    unsigned char whichbit = 0;
    unsigned char curbyte = 0;
    writeHeader(Root, &whichbit, &curbyte, compressedFile);
    
    //get table of compressed ascii values
    long * Table = malloc(sizeof(long)*ASCII_SIZE);
    long Value = 0;
    getTable(Table, Root, Value);

    rewind(inFile);
    int ch;
    while((ch=fgetc(inFile)) != EOF){
        writeBody(ch, compressedFile, &whichbit, &curbyte, Table);
    }
    writeBody(255, compressedFile, &whichbit, &curbyte, Table);

    while(whichbit != 0){
        writeBit(compressedFile, 0x00, &whichbit, &curbyte);
    }
    free(Table);
    fclose(inFile);
    fclose(compressedFile);
    FreeTree(Root);
}

long * freqASCII(FILE * fp){
    long * asciiFreq = (long *)malloc(sizeof(long) * ASCII_SIZE);
    if(asciiFreq == NULL){
        return NULL;
    }
    for (int i = 0; i < ASCII_SIZE; i++){asciiFreq[i]=0;}
    int ch;
    while ((ch = fgetc(fp)) != EOF){
        asciiFreq[ch] += 1;
    }
    return asciiFreq;
}

void writeBody(int ch, FILE * compressedFile, unsigned char * whichbit, unsigned char * curbyte, long * Table){
    int length = ((int)log10(Table[ch]));
    for (int x=length; x>=0; x--){
        int dv = (int)pow(10,x);
        int bit = (((int)Table[ch]/dv) % 10) -1;
        if (bit == 0){writeBit(compressedFile, 0x00, whichbit, curbyte);}
        else{writeBit(compressedFile, 0x01, whichbit, curbyte);}
    }
}

