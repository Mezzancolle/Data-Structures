#include <set_linkedlist.h>

// Hash function (djb33x) to generate a hash value for a given key
size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

// Function to create a new set table with a specified hashmap size and maximum elements per bucket
struct set_table* set_table_new(const size_t hashmap_size, const size_t max_elements_per_bucket)
{
    struct set_table* table = malloc(sizeof(struct set_table));
    if (!table)
    {
        return NULL;  // Memory allocation failure, return NULL.
    }

    table->hashmap_size = hashmap_size;
    table->nodes = calloc(table->hashmap_size, sizeof(struct set_node*));

    if (!table->nodes)
    {
        free(table);
        return NULL;  // Memory allocation failure, return NULL.
    }

    table->max_elements_per_bucket = max_elements_per_bucket;

    return table;  // Return the newly created set table.
}

// Function to find a node with a specified key in the set table
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
            return head;  // Return the found node.
        }

        head = CAST_TO_SET_NODE(head->list_item.next);
    }

    return NULL;  // Return NULL if the node with the specified key is not found.
}

// Function to insert a new node with a specified key and key length into the set table
struct set_node* set_insert(struct set_table* table, const char* key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);

    size_t index = hash % table->hashmap_size;

    // Check if the element already exists
    struct set_node* existing_node = set_find(table, key);
    if (existing_node != NULL) {
        printf("Element already exists\n");
        return NULL;  // Return NULL if the node with the specified key already exists.
    }

    struct set_node* head = table->nodes[index];

    size_t element_count = 0;
    struct set_node* current = head;

    // Count the elements in the current bucket
    while (current)
    {
        element_count++;
        current = CAST_TO_SET_NODE(current->list_item.next);
    }

    // Check for collision and exceeding maximum elements per bucket
    if (element_count >= table->max_elements_per_bucket)
    {
        printf("COLLISION: Exceeded maximum elements per bucket at index %llu\n", index);
        return NULL;  // Return NULL if the maximum elements per bucket are exceeded.
    }

    // Allocate memory for the new node
    struct set_node* new_item = malloc(sizeof(struct set_node));
    if (!new_item)
    {
        return NULL;  // Return NULL if memory allocation fails.
    }

    // Initialize the new node with the provided key and key length
    new_item->key = key;
    new_item->key_len = key_len;
    new_item->list_item.next = NULL;

    // Insert the new node into the set table
    if (!head)
    {
        table->nodes[index] = new_item;  // Set as the first node in the bucket
    }
    else
    {
        struct set_node* tail = table->nodes[index];
        while (tail->list_item.next)
        {
            tail = CAST_TO_SET_NODE(tail->list_item.next);
        }
        tail->list_item.next = &new_item->list_item;  // Append to the end of the bucket
    }

    return new_item;  // Return the newly inserted node.
}

// Function to print the elements in the set table
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

// Function to remove a node with a specified key from the set table
struct set_node* set_remove(struct set_table* table, const char* key)
{
    const size_t key_len = strlen(key);
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;

    struct set_node* head = table->nodes[index];
    struct set_node* current = head;
    struct set_node* prev = NULL;

    // Traverse the linked list in the bucket to find the node with the specified key
    while (current)
    {
        if (current->key_len == key_len && memcmp(current->key, key, key_len) == 0)
        {
            break;  // Break the loop if the node with the specified key is found.
        }

        prev = current;
        current = CAST_TO_SET_NODE(current->list_item.next);
    }

    if (current)
    {
        if (prev)
        {
            prev->list_item.next = current->list_item.next;  // Remove the node from the linked list
        }
        else
        {
            table->nodes[index] = CAST_TO_SET_NODE(current->list_item.next);  // Update the head of the bucket
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

    return current;  // Return the removed node.
}