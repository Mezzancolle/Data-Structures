#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define LIST_ITEM(x) &(x.list_item)
#define INT_ITEM(x) ((struct int_item*)(x))

struct list_item {
    struct list_item* next;
    unsigned int count;
};

struct int_item {
    struct list_item list_item;
    int value;
};

struct list_item* list_get_tail(struct list_item* head);
struct list_item* list_append(struct list_item** head, struct list_item* item);
unsigned int list_lenght(struct list_item* head);
struct list_item* list_pop(struct list_item** head);
struct list_item* list_remove_by_value(struct list_item** head, int value);
struct list_item* list_remove_by_index(struct list_item** head, unsigned int index);
void list_reverse(struct list_item** head);
void PrintList(struct list_item* head);

#endif 