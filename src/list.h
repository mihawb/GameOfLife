#ifndef LIST_H
#define LIST_H
//zwyczajnia lista jednokierunkowa, używamy jej w naszym cyklu

typedef struct list{
    int x,y,v;
    struct list *next;
}*list_t;

list_t add_elem(list_t head, int x, int y, int v); //dodaje element do listy
void show_list(list_t head); //pokazuje liste
list_t free_list(list_t head); //zwalnie pamięc

#endif
