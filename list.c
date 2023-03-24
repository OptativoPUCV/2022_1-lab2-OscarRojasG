#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List *list = (List *) calloc(1, sizeof(List));
    return list;
}

void * firstList(List * list) {
    list->current = list->head;
    if (list->head) {
        return list->head->data;
    }
    return NULL;
}

void * nextList(List * list) {
    if (list->current == NULL) {
        return NULL;
    }

    Node *node = list->current->next;
    list->current = node;

    if (node) return node->data;
    return NULL;
}

void * lastList(List * list) {
    list->current = list->tail;
    if (list->tail) {
        return list->tail->data;
    }

    return NULL;
}

void * prevList(List * list) {
    if (list->current == NULL) {
        return NULL;
    }

    Node *node = list->current->prev;
    list->current = node;

    if (node) return node->data;
    return NULL;
}

void pushFront(List * list, void * data) {
    Node *node = createNode(data);

    if (list->head) {
        node->next = list->head;
        list->head->prev = node;
    }

    if (list->tail == NULL) {
        list->tail = node;
    }

    list->head = node;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}