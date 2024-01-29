#include <set_linkedlist.h>

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

struct set_table* set_table_new(const size_t hashmap_size, const size_t max_elements_per_bucket)
{
    struct set_table* table = malloc(sizeof(struct set_table));
    if (!table)
    {
        return NULL;
    }

    table->hashmap_size = hashmap_size;
    table->nodes = calloc(table->hashmap_size, sizeof(struct set_node*));

    if (!table->nodes)
    {
        free(table);
        return NULL;
    }

    table->max_elements_per_bucket = max_elements_per_bucket;

    return table;
}

struct set_node* set_find(struct set_table* table, const char* key)
{
    const size_t key_len = strlen(key);

    size_t hash = djb33x_hash(key, key_len);

    size_t index = hash % table->hashmap_size;

    struct set_node* head = table->nodes[index];

    while(head)
    {
        if(head->key_len == key_len && memcmp(head->key, key, key_len) == 0)
        {
            printf("Key Found: %s at index %llu\n", key, index);
            return head;
        }

        
        head = CAST_TO_SET_NODE(head->list_item.next);
    }


    return NULL;
}

struct set_node* set_insert(struct set_table* table, const char* key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);

    size_t index = hash % table->hashmap_size;

    struct set_node* existing_node = set_find(table, key);
    if (existing_node != NULL) {
        printf("Element already exists\n");
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

    struct set_node* new_item = malloc(sizeof(struct set_node));
    if (!new_item)
    {
        return NULL;
    }

    new_item->key = key;
    new_item->key_len = key_len;
    new_item->list_item.next = NULL;

    if (!head)
    {
        table->nodes[index] = new_item;
    }
    else
    {
        struct set_node* tail = table->nodes[index];
        while (tail->list_item.next)
        {
            tail = CAST_TO_SET_NODE(tail->list_item.next);
        }
        tail->list_item.next = &new_item->list_item;
    }

    return new_item;
}

void print_set(struct set_table* table)
{
    for (size_t i = 0; i < table->hashmap_size; i++)
    {
        struct set_node* head = table->nodes[i];

        while(head)
        {
            printf("Index: %llu, Key: %s\n", i, head->key);
            head = CAST_TO_SET_NODE(head->list_item.next);
        }
    }
}

struct set_node* set_remove(struct set_table* table, const char* key)
{
    const size_t key_len = strlen(key);
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;

    struct set_node* head = table->nodes[index];
    struct set_node* current = head;
    struct set_node* prev = NULL;

    while (current)
    {
        if (current->key_len == key_len && memcmp(current->key, key, key_len) == 0)
        {
            break;
        }

        prev = current;
        current = CAST_TO_SET_NODE(current->list_item.next);
    }

    if (current)
    {
        if (prev)
        {
            prev->list_item.next = current->list_item.next;
        }
        else
        {
            table->nodes[index] = CAST_TO_SET_NODE(current->list_item.next);
        }

        if (table->nodes[index])
        {
            table->nodes[index]->list_item.count--;
        }

        current->list_item.next = NULL;

        printf("Element removed successfully: %s, at index %llu\n", key, index);
    }
    else
    {
        printf("Element not found for removal: %s\n", key);
    }

    return current;
}