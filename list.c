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
    List *list = (List *) malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    return list;
}

void * firstList(List * list) {
    if(list->head) {
      list->current = list->head;
      return list->head->data;
    }
    return NULL;
}

void * nextList(List * list) {
    if(list->current) {
      list->current = list->current->next;
      if(list->current) return list->current->data;
    }
    return NULL;
}

void * lastList(List * list) {
    if(list->tail) {
      list->current = list->tail;
      return list->current->data;
    }
    return NULL;
}

void * prevList(List * list) {
    if(list->current) {
      list->current = list->current->prev;
      if(list->current) return list->current->data;
    }
    return NULL;
}

void pushFront(List * list, void * data) {
    Node *node = createNode(data);
    node->next = list->head;
    if(list->head) list->head->prev = node;
    else list->tail = node;
    list->head = node;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node *node = createNode(data);
    if(list->current) {
      node->next = list->current->next;
      node->prev = list->current;
      
      if(node->next) node->next->prev = node;
      else list->tail = node;
      
      node->prev->next = node;
    }
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
    Node *current = list->current;
    void *data = NULL;
    if(current) {
      if(current->prev) current->prev->next = current->next;
      else list->head = current->next;
      
      if(current->next) current->next->prev = current->prev;
      else list->tail = current->prev;
      
      data = current->data;
      free(current);
    }
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}