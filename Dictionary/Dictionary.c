#include <Dictionary.h>

struct dictionary* dictionary_new(const size_t hashmap_size, const size_t max_elements_per_bucket, enum ValueType value_type)
{
    struct dictionary* dict = malloc(sizeof(struct dictionary));
    if (!dict)
    {
        return NULL;
    }

    dict->set = set_table_new(hashmap_size, max_elements_per_bucket);

    if (!dict->set)
    {
        free(dict);
        return NULL;
    }

    dict->value_type = value_type;

    return dict;
}

struct set_node* set_insert_key_value(struct set_table* table, const char* key, const size_t key_len, struct dict_node* value)
{
    size_t hash = djb33x_hash(key, key_len);

    size_t index = hash % table->hashmap_size;

    struct set_node* existing_node = set_find(table, key);
    if (existing_node)
    {
        printf("Element already exists in the set\n");
        return NULL;
    }

    struct set_node* head = table->nodes[index];

    size_t element_count = 0;
    struct set_node* current = head;
    
    while (current)
    {
        element_count++;
        current = CAST_TO_SET_NODE(current->list_item.next);
    }

    if (element_count >= table->max_elements_per_bucket)
    {
        printf("COLLISION: Exceeded maximum elements per bucket at index %llu\n", index);
        return NULL;
    }

    value->set_node.key = key;
    value->set_node.key_len = key_len;
    value->set_node.list_item.next = NULL;

    if (!head)
    {
        table->nodes[index] = &value->set_node;
    }
    else
    {
        struct set_node* tail = table->nodes[index];
        while (tail->list_item.next)
        {
            tail = CAST_TO_SET_NODE(tail->list_item.next);
        }
        tail->list_item.next = &value->set_node.list_item;
    }

    return &value->set_node;
}

void dictionary_insert(struct dictionary* dict, const char* key, const size_t key_len, void* value)
{
    struct dict_node* node = malloc(sizeof(struct dict_node));
    if (!node)
    {
        return;
    }

    node->set_node.key = key;
    node->set_node.key_len = key_len;
    node->set_node.list_item.next = NULL;

    switch (dict->value_type)
    {
    case INT_TYPE:
        node->int_value = *((int*)value);
        break;
    case CHAR_TYPE:
        node->char_value = *((char**)value);
        break;
    }

    set_insert_key_value(dict->set, key, key_len, node);
}

void dictionary_remove(struct dictionary* dict, const char* key)
{
    const size_t key_len = strlen(key);
    struct set_node* removed_node = set_remove(dict->set, key);

    if (removed_node != NULL)
    {
        struct dict_node* dict_node = CAST_TO_DICT_NODE(removed_node);
        free(dict_node);
        printf("Key removed: %s\n", key);
    }
    else
    {
        printf("Key not found for removal\n");
    }

    printf("\n");
}

void print_dictionary(struct dictionary* dict)
{
    if (dict == NULL || dict->set == NULL)
    {
        printf("Dictionary is NULL\n");
        return;
    }

    printf("Dictionary:\n");

    for (size_t i = 0; i < dict->set->hashmap_size; ++i)
    {
        struct set_node* set_head = dict->set->nodes[i];

        while (set_head != NULL)
        {
            struct dict_node* dict_node = CAST_TO_DICT_NODE(set_head);

            printf("Index: %llu, Key: %s, Value: ", i, dict_node->set_node.key);

            switch (dict->value_type)
            {
            case INT_TYPE:
                printf("%d", dict_node->int_value);
                break;
            case CHAR_TYPE:
                printf("%s", dict_node->char_value);
                break;
            default:
                printf("Unsupported value type");
                break;
            }

            printf("\n");

            set_head = CAST_TO_SET_NODE(set_head->list_item.next);
        }
    }

    printf("\n");
}