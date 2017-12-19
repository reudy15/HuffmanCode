#ifndef BINARY_H
#define BINARY_H
#include "compress.h"

TreeNode * buildTreeFromLL(ListNode * head);
ListNode * buildNode(ListNode * NodeL, ListNode * NodeR);
void createHeader(TreeNode * Tree, FILE * fp);
void writeHeader(TreeNode * Tree, unsigned char * whichbit, unsigned char * curbyte, FILE * fp);
void writeBit(FILE * fp, unsigned char bit, unsigned char * whichbit, unsigned char * curbyte);
int readBit(FILE * fp, unsigned char * whichbit, unsigned char * curbyte);
TreeNode * buildTreeFromHeader(FILE * fp, unsigned char * whichbit, unsigned char * curbyte);
void getTable(long * Table, TreeNode * Root, long Value);
void FreeTree(TreeNode * t);

#endif
