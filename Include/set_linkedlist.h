#ifndef SET_LINKED_LIST_H
#define SET_LINKED_LIST_H

#include <string.h>
#include <linkedlist.h>

#define CAST_TO_SET_NODE(x) (struct set_node*)x
#define CAST_TO_DICT_NODE(x) (struct dict_node*)x

struct set_node
{
    struct list_item list_item;
    const char* key;
    size_t key_len;
};

struct set_table
{
    struct set_node** nodes;
    size_t hashmap_size;
    size_t max_elements_per_bucket;
};

size_t djb33x_hash(const char *key, const size_t keylen);
struct set_table* set_table_new(const size_t hashmap_size, const size_t max_elements_per_bucket);
struct set_node* set_find(struct set_table* table, const char* key);
struct set_node* set_insert(struct set_table* table, const char* key, const size_t key_len);
void print_set(struct set_table* table);
struct set_node* set_remove(struct set_table* table, const char* key);

#endif 