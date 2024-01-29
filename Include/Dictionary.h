#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <set_linkedlist.h>

enum ValueType
{
    INT_TYPE,
    CHAR_TYPE,
};

struct dictionary
{
    struct set_table* set;
    enum ValueType value_type;
};


struct dict_node
{
    struct set_node set_node;
    union {
        int int_value;
        char* char_value;
    };
};

struct dictionary* dictionary_new(const size_t hashmap_size, const size_t max_elements_per_bucket, enum ValueType value_type);
struct set_node* set_insert_key_value(struct set_table* table, const char* key, const size_t key_len, struct dict_node* value);
void dictionary_insert(struct dictionary* dict, const char* key, const size_t key_len, void* value);
void* dictionary_find(struct dictionary* dict, const char* key, enum ValueType value_type);
void dictionary_remove(struct dictionary* dict, const char* key);
void print_dictionary(struct dictionary* dict);

#endif