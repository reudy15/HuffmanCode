#ifndef COMPRESS_H
#define COMPRESS_H

#define ASCII_SIZE 256

typedef struct TreeNode{
    int label;
    long count;
    struct TreeNode * left;
    struct TreeNode * right;
} TreeNode;

typedef struct ListNode{
    TreeNode * ptr;
    struct ListNode * next;
} ListNode;

void readBody(FILE * compressFile, FILE * inFile, unsigned char * whichbit, unsigned char * curbyte, TreeNode * Root);
void writeBody(int ch, FILE * compressFile, unsigned char * whichbit, unsigned char * curbyte, long * Table);
long * freqASCII(FILE * inFile);

#endif
