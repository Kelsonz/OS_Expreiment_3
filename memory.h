//
// Created by 傅康 on 2019/12/23.
//

#ifndef EXP3_MEMORY_H
#define EXP3_MEMORY_H
#define USE 1
#define FREE -1
#define SUCCESS 1
#define FALSE -1
#define BESTFIT 1
#define FIRSTFIT 2
#define RELEASE 3
#define TRUE 1
#define OK 1
#define QUIT 0
typedef int Element;
typedef int Status;
typedef int bool;
typedef struct Memory {
    Element id;
    Element size;
    Element addr;
    Element isUse;
} Memory, *pMemory;
typedef struct Node {
    pMemory data;
    struct Node *next;
    struct Node *last;
} Node, *pNode;
typedef struct List {
    Element used;
    Element free;
    double percent;
    pNode head;
} List, *pList;

Status initList(pList *p, Element size);

Status firstFit(pList list, Element id, Element size);

Status bestFit(pList list, Element id, Element size);

Status release(pList list, Element id);
Status printList(pList list);
Status printNode(pNode p);
Status run(pList list);
#endif //EXP3_MEMORY_H
