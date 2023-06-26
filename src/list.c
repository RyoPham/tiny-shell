#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include "list.h"

struct Node* makeNode(pid_t value) {
    struct Node* u = (struct Node*) malloc(sizeof(struct Node));
    u->value = value;
    u->next = NULL;
    return u;
}

struct List* makeList() {
    struct List* list = (struct List*) malloc(sizeof(struct List));
    list->head = list->tail = NULL;
    return list;
}

void add(struct List* list, pid_t value) {
    struct Node* u = makeNode(value);
    if(list->head == NULL) {
        list->head = list->tail = u;
    }
    else {
        list->tail->next = u;
        list->tail = u;
    }
}

void clear(struct List* list) {
    struct Node* temp;
    while(list->head != NULL) {
        temp = list->head->next;
        free(list->head);
        list->head = temp;
    }
}