#include <stdio.h>
#include <stdlib.h>
#include "list.h"

list_t add_elem(list_t head, int x, int y, int v){
    list_t node = (list_t)malloc(sizeof *node);
    node->x = x;
    node->y = y;
    node->v = v;
    node->next = NULL;
    if(head == NULL){
        return node;
    }
    else{
        list_t itr = head;
        while(itr->next != NULL)
            itr = itr->next;
        itr->next = node;
        return head;

    }
}

void show_list(list_t head){
    list_t itr = head;
    while(itr != NULL){
        printf("%d %d %d\n",itr->x,itr->y, itr->v);
        itr = itr->next;
    }
}

int list_size(list_t head){
    int size = 0;
    list_t itr = head;
    while(itr != NULL){
        size++;
        itr = itr->next;
    }
    return size;
}


list_t get_elem(list_t head, int index){
    list_t itr = head;
    int i=0;
    while(itr != NULL){
        if(i==index)
            break;
        itr = itr->next;
        i++;
    }
    return itr;
}

list_t remove_elem(list_t head, int x, int y){
    list_t itr = head;
    if(itr->x == x && itr->y == y){
        list_t tmp = itr->next;
        free(itr);
        return tmp;
    }
    while(itr->next != NULL){

        if(itr->next->x == x && itr->next->y == y){
            if(itr->next->next == NULL ){
                itr->next = NULL;
                return head;
            }
            else {
                list_t tmp = itr->next;
                itr->next = itr->next->next;
                free(tmp);
            }
        }
        itr = itr->next;
    }
    return head;
}


list_t free_list(list_t head){
    list_t itr;
    while(head != NULL){
        itr = head;
        head = head->next;
        free(itr);
    }
    return NULL;
}





