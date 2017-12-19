#include <stdio.h>
#include <stdlib.h>
#include "binary.h"
#include "compress.h"
#include "linked.h"

TreeNode * buildTreeFromLL(ListNode * head){
    while(head->next != NULL){
        ListNode * temp = buildNode(head, head->next);
        Remove(&head);
        insertNode(&head, temp);
    }
    TreeNode * Root = head->ptr;
    FreeList(head);
    return(Root);
}

ListNode * buildNode(ListNode * NodeL, ListNode * NodeR){
    ListNode * retv = createNode((NodeL->ptr->count + NodeR->ptr->count), 0);
    retv->ptr->left = NodeL->ptr;
    retv->ptr->right = NodeR->ptr;
    return(retv);
}

void getTable(long * Table, TreeNode * Root, long Value){
    if(Root->right == NULL && Root->left == NULL){
        Table[Root->label] = Value;
    }else{
        getTable(Table, Root->left, Value*10+1);
        getTable(Table, Root->right, Value*10+2);
    }
}

void writeHeader(TreeNode * Tree, unsigned char * whichbit, unsigned char * curbyte, FILE * fp){
    if(Tree->left == NULL && Tree->right == NULL){
        writeBit(fp, 0x01, whichbit, curbyte);
        for(int i = 0; i<8; i++){
            writeBit(fp, Tree->label >> (7-i), whichbit, curbyte);
        }
    }else{
        writeBit(fp, 0x00, whichbit, curbyte);
        if(Tree->left != NULL){writeHeader(Tree->left, whichbit, curbyte, fp);}
        if(Tree->right != NULL){writeHeader(Tree->right, whichbit, curbyte, fp);}
    }
}

void writeBit(FILE * fp, unsigned char bit, unsigned char * whichbit, unsigned char * curbyte){
    if((* whichbit) == 0){* curbyte = 0;}
    unsigned char temp = bit << (7 - (* whichbit));
    * curbyte |= temp;
    if((* whichbit) == 7){
        fwrite(curbyte, sizeof(unsigned char), 1, fp);
    }
    * whichbit = ((* whichbit) + 1) % 8;
}

int readBit(FILE * fp, unsigned char * whichbit, unsigned char * curbyte){
    if((* whichbit) == 8){
        fread(curbyte, sizeof(unsigned char), 1, fp);
        * whichbit = 0;
    }
    int ret = !!((* curbyte) & 0x80);
    * whichbit += 1;
    * cutbyte <<= 1;
    return ret;
}

TreeNode * buildTreeFromHeader(FILE * fp, unsigned char * whichbit, unsigned char * curbyte){
    int bit = readBit(fp, whichbit, curbyte);
    TreeNode * node = malloc(sizeof(TreeNode));
    if(bit == 1){
        unsigned char temp = 0;
        for(int i = 0; i < 8; i++){
            if(readBit(fp, whichbit, curbyte) == 1){
                temp |= (0x01 << (7-i));
            }else{
                temp |= (0x00 << (7-i));
            }
        }
        node->label = temp;
        return node;
    }
    node->left = buildTreeFromHeader(fp, whichbit, curbyte);
    node->right = buildTreeFromHeader(fp, whichbit, curbyte);
    return node;
}

void FreeTree(TreeNode * t){
    if(t == NULL) return;
    FreeTree(t->left);
    FreeTree(t->right);
    free(t);
}

