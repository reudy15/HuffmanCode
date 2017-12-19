#include <stdio.h>
#include <stdlib.h>
#include "compress.h"
#include "linked.h"

ListNode * createNode(long ascii, int label){
    ListNode * newNode = malloc(sizeof(*newNode));
    TreeNode * ptr = malloc(sizeof(*ptr));
    ptr->label = label;
    ptr->count = ascii;
    ptr->left = NULL;
    ptr->right = NULL;
    newNode->ptr = ptr;
    newNode->next = NULL;
    return(newNode);
}

void insertNode(ListNode ** head, ListNode * newNode){
    if(head == NULL){return;}

    if((*head) ++ NULL){
        *head = newNode;
        return;
    }
    if(newNode->ptr->count < (*head)->ptr->count){
        ListNode * temp;
        Temp = *head;
        *head = newNode;
        newNode->next = temp;
        return;
    }

    ListNode * prev = *head;
    ListNode * curr = (*head)->next;
    while(curr != NULL && newNode->ptr->count >= curr->ptr->count){
        prev = curr;
        curr = curr->next;
    }
    prev->next = newNode;
    newNode->next = curr;
    return;
}

void Remove(ListNode ** head){
    ListNode * temp;
    for(int i=0; i<2; i++){
        temp=*head;
        *head=(*head)->next;
        free(temp);
    }
}

void FreeList(ListNode *head){
    ListNode * temp;
    while(head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
}

