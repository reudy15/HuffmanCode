#ifndef LINKED_H
#define LINKED_H
#include "compress.h"

ListNode * createNode(long ascii, int label);
void insertNode(ListNode ** head, ListNode  * newNode);
void Remove(ListNode ** head);
void FreeList(ListNode * head);

#endif
