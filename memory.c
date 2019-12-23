//
// Created by 傅康 on 2019/12/23.
//

#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

Status initList(pList *p, Element size) {
    (*p) = (pList)malloc(sizeof(List));
    (*p)->head = (pNode) malloc(sizeof(Node));
    (*p)->free = size;
    (*p)->used = 0;
    (*p)->used = (*p)->free/size*1.0;
    (*p)->head->data = NULL;
    (*p)->head->last = NULL;
    (*p)->head->next = (pNode) malloc(sizeof(Node));

    pNode q = (*p)->head->next;
    q->data = (pMemory)malloc(sizeof(Memory));
    q->last = (*p)->head;
    q->next = NULL;
    q->data->size = size;
    q->data->isUse = FREE;
    q->data->addr = 0;
}


Status run(pList list){
    int way;
    int id;
    int size;
    int result;
    while (TRUE){
        printList(list);
        printf("1 BESTFIT\n2 FIRSTFIT\n3 RELEASE\n0 QUIT\n");
        printf("------------\n");
        scanf("%d",&way);
        switch (way){
            case BESTFIT:
                printf("1 BESTFIT\n");
                printf("------------\n");
                scanf("%d %d",&id, &size);
                result = bestFit(list,id, size);
                if(result == FALSE){
                    printf("FALSE\n");
                }
                break;
            case FIRSTFIT:
                printf("2 FIRSTFIT\n");
                printf("------------\n");
                scanf("%d %d",&id, &size);
                result = firstFit(list, id, size);
                if(result == FALSE){
                    printf("FALSE\n");
                }
                break;
            case RELEASE:
                printf("3 RELEASE\n");
                printf("------------\n");
                printList(list);
                printf("id: ");
                scanf("%d",&id);
                release(list, id);
                break;
            case QUIT:
                printf("4 QUIT\n");
                printf("------------\n");
                return OK;
        }

    }
}
Status printList(pList list) {
    for (pNode p = list->head->next; p != NULL; p = p->next) {
        printNode(p);
    }
}

Status printNode(pNode p) {
    printf("addr:%d\tid:%d\tsize:%d\t", p->data->addr, p->data->id, p->data->size);
    switch (p->data->isUse) {
        case FREE:
            printf("FREE\n");
            break;
        case USE:
            printf("USE\n");
            break;
    }
}

Status release(pList list, Element id) {
    for (pNode p = list->head->next; p != NULL; p = p->next) {
        if (p->data->id == id) {
            p->data->isUse = FREE;
            p->data->id = 0;
            list->free += p->data->size;
            list->used -= p->data->size;
            list->percent = (list->used )*1.0/ (list->used+list->free)*1.0;
            if (p->last != NULL) {
                if (p->last != list->head && p->last->data->isUse == FREE)
                {
                    pNode q = p->last->last;
                    p->data->isUse = FREE;
                    p->data->addr -= p->last->data->size;
                    p->data->size += p->last->data->size;
                    q->next = p;
                    p->last = q;
                }
            }
            if (p->next != NULL && p->next->data->isUse == FREE) {
                pNode next = p->next->next;
                p->data->size += p->next->data->size;
                p->next = next;
                if (next){
                    next->last = p;
                }
            }
        }
    }
}

Status firstFit(pList list, Element id, Element size) {
    pNode x = (pNode) malloc(sizeof(Node));
    x->data = (pMemory) malloc(sizeof(Memory));
    x->data->isUse = USE;
    x->data->id = id;
    x->data->size = size;
    x->next = NULL;
    x->last = NULL;

    pNode p = list->head->next;
    while (p) {
        if (p->data->size >= size && p->data->isUse == FREE) {
            if (p->data->size == size) {
                x = p;
                list->used += p->data->size;
                list->free -= p->data->size;
                list->percent = list->used / (list->used+list->free)*1.0;
                return SUCCESS;
            } else {
                pNode next = p->next;
                pNode last = p->last;
                last->next = x;
                x->last = last;
                x->next = p;
                p->last = x;
                list->used += x->data->size;
                list->free -= x->data->size;
                list->percent = list->used / (list->used+list->free)*1.0;
                x->data->addr = p->data->addr;
                p->data->addr += size;
                p->data->size -= size;
                return SUCCESS;
            }
        }
        p = p->next;
    }
    return FALSE;
}

Status bestFit(pList list, Element id, Element size) {
    pNode x = (pNode) malloc(sizeof(Node));
    x->data = (pMemory) malloc(sizeof(Memory));
    x->data->isUse = USE;
    x->data->id = id;
    x->data->size = size;
    x->next = NULL;
    x->last = NULL;

    int min = list->free;
    pNode p = list->head;
    pNode y = NULL;
    while (p->next) {
        int d = p->next->data->size - size;
        if (d >= 0 && p->next->data->isUse == FREE) {
            if (d < min) {
                min = d;
                y = p->next;
            }
        }
        p = p->next;
    }
    if (!y) {
        return FALSE;
    } else {
        if (y->data->size == size) {
            x = y;
            list->free -= x->data->size;
            list->used += x->data->size;
            list->percent = list->used / (list->used+list->free)*1.0;
        } else {
            pNode next = y->next;
            pNode last = y->last;
            last->next = x;
            x->last = last;
            x->next = y;
            y->last = x;

            list->free -= x->data->size;
            list->used += x->data->size;
            list->percent = list->used / (list->used+list->free)*1.0;
            x->data->addr = y->data->addr;
            y->data->addr += size;
            y->data->size -= size;
            return SUCCESS;
        }
    }
}