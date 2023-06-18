#ifndef __LIST_H__
#define __LIST_H__

#include <unistd.h>
#include <stdlib.h>

struct Node {
    pid_t value;
    struct Node *next;

};

struct List {
    struct Node* head;
    struct Node* tail;
};

struct Node* makeNode(pid_t value);

struct List* makeList();

void add(struct List* list, pid_t value);

void clear(struct List* list);

#endif