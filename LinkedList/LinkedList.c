#include <linkedlist.h>

struct list_item* list_get_tail(struct list_item* head)
{
    if (!head)
    {
        return NULL;
    }

    struct list_item* current_item = head;
    struct list_item* last_item = head;
    while(current_item)
    {
        last_item = current_item;
        current_item = current_item->next;
    }

    return last_item;  
    
};

struct list_item* list_append(struct list_item** head, struct list_item* item)
{
    struct list_item* tail = list_get_tail(*head);
    if (!tail)
    {
        *head = item;
        (*head)->count = 1;
    }
    else
    {
        tail->next = item;
        (*head)->count++;
    }

    item->next = NULL;

    return item;
};

unsigned int list_lenght(struct list_item* head)
{
    return head->count;
}

struct list_item* list_pop(struct list_item** head)
{
    if (!(*head))
    {
        return NULL;
    }

    struct list_item *current_head = *head;
    const unsigned int current_count = current_head->count;
    *head = (*head)->next;
    if (*head)
    {
        (*head)->count = current_count - 1;
    }

    current_head->next = NULL;
    
    return current_head;    
}

struct list_item* list_remove_by_value(struct list_item** head, int value)
{
    if (!(*head))
    {
        return NULL;
    }

    struct list_item* current_head = *head;
    struct list_item* prev_head = NULL;
    const unsigned int current_count = current_head->count;

    while (current_head != NULL)
    {
        struct int_item* int_item = INT_ITEM(current_head);

        if (int_item->value == value)
        {
            if (prev_head)
            {
                prev_head->next = current_head->next;
            }
            else
            {
                *head = current_head->next;
            }

            if (*head)
            {
                (*head)->count = current_count - 1;
            }
            current_head->next = NULL;
            return current_head;
        }

        prev_head = current_head;
        current_head = current_head->next;
    }

    return current_head;
}

struct list_item* list_remove_by_index(struct list_item** head, unsigned int index)
{
    if (!(*head) || index >= (*head)->count)
    {
        return NULL;
    }

    struct list_item* current_head = *head;
    struct list_item* prev_head = NULL;
    const unsigned int current_count = current_head->count;

    for (unsigned int i = 0; i < index; ++i)
    {
        prev_head = current_head;
        current_head = current_head->next;
    }

    if (prev_head)
    {
        prev_head->next = current_head->next;
    }
    else
    {
        *head = current_head->next;
    }

    if (*head)
    {
        (*head)->count = current_count - 1;
    }

    current_head->next = NULL;
    return current_head;
}

void list_reverse(struct list_item** head)
{
    if (!head || !(*head))
    {
        return;
    }

    unsigned int original_count = (*head)->count;

    struct list_item* prev_head = NULL;
    struct list_item* current_head = *head;
    struct list_item* next_head = NULL;

    while (current_head)
    {
        next_head = current_head->next;
        current_head->next = prev_head;
        prev_head = current_head;
        current_head = next_head;
    }

    *head = prev_head;

    (*head)->count = original_count;
}

void PrintList(struct list_item* head)
{
    if (!head)
    {
        printf("List is empty\n");
        return;
    }

    struct list_item* current_head = head;
    
    printf("List Length: %u\n", list_lenght(head));

    while (current_head != NULL)
    {
        struct int_item* int_item = INT_ITEM(current_head);
        printf("%d ", int_item->value);
        current_head = current_head->next;
    }

    printf("\n");
}