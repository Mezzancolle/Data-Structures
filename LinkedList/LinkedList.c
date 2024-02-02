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
        last_item = current_item;  // Traverse the list to find the last item.
        current_item = current_item->next;
    }

    return last_item; 
};

struct list_item* list_append(struct list_item** head, struct list_item* item)
{
    struct list_item* tail = list_get_tail(*head);  // Get the current tail of the list.
    if (!tail)
    {
        *head = item;  // If the list is empty, set the head to the new item.
        (*head)->count = 1;
    }
    else
    {
        tail->next = item;  // Append the new item to the end of the list.
        (*head)->count++;
    }

    item->next = NULL;  // Set the next pointer of the new item to NULL.

    return item;  // Return the appended item.
};

unsigned int list_lenght(struct list_item* head)
{
    return head->count; 
}

// Function to pop an item from the front of the linked list
struct list_item* list_pop(struct list_item** head)
{
    if (!(*head))
    {
        return NULL;
    }

    struct list_item *current_head = *head;
    const unsigned int current_count = current_head->count;
    *head = (*head)->next;  // Move the head to the next item.
    if (*head)
    {
        (*head)->count = current_count - 1;  // Update the count in the new head.
    }

    current_head->next = NULL;  // Set the next pointer of the popped item to NULL.
    
    return current_head;  // Return the popped item.
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
                prev_head->next = current_head->next;  // Remove the item from the middle or end.
            }
            else
            {
                *head = current_head->next;  // Remove the item from the beginning.
            }

            if (*head)
            {
                (*head)->count = current_count - 1;  // Update the count in the new head.
            }
            current_head->next = NULL;  // Set the next pointer of the removed item to NULL.
            return current_head;  // Return the removed item.
        }

        prev_head = current_head;
        current_head = current_head->next;
    }

    return current_head;  // If the value is not found, return NULL.
}

struct list_item* list_remove_by_index(struct list_item** head, unsigned int index)
{
    if (!(*head) || index >= (*head)->count)
    {
        return NULL;  // If the list is empty or the index is out of bounds, return NULL.
    }

    struct list_item* current_head = *head;
    struct list_item* prev_head = NULL;
    const unsigned int current_count = current_head->count;

    for (unsigned int i = 0; i < index; ++i)
    {
        prev_head = current_head;
        current_head = current_head->next;  // Traverse the list to the specified index.
    }

    if (prev_head)
    {
        prev_head->next = current_head->next;  // Remove the item from the middle or end.
    }
    else
    {
        *head = current_head->next;  // Remove the item from the beginning.
    }

    if (*head)
    {
        (*head)->count = current_count - 1;  // Update the count in the new head.
    }

    current_head->next = NULL;  // Set the next pointer of the removed item to NULL.
    return current_head;  // Return the removed item.
}

void list_reverse(struct list_item** head)
{
    if (!head || !(*head))
    {
        return;  // If the list is empty or the head is NULL, return.
    }

    unsigned int original_count = (*head)->count;

    struct list_item* prev_head = NULL;
    struct list_item* current_head = *head;
    struct list_item* next_head = NULL;

    while (current_head)
    {
        next_head = current_head->next;  // Save the next pointer.
        current_head->next = prev_head;  // Reverse the next pointer.
        prev_head = current_head;
        current_head = next_head;
    }

    *head = prev_head;  // Set the head to the new first item.

    (*head)->count = original_count;  // Update the count in the new head.
}

void PrintList(struct list_item* head)
{
    if (!head)
    {
        printf("List is empty\n");  // If the list is empty, print a message and return.
        return;
    }

    struct list_item* current_head = head;
    
    printf("List Length: %u\n", list_lenght(head));  // Print the length of the list.

    while (current_head != NULL)
    {
        struct int_item* int_item = INT_ITEM(current_head);
        printf("%d ", int_item->value);  // Print the value of each item.
        current_head = current_head->next;
    }

    printf("\n");
}