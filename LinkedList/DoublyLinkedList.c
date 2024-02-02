#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIST_ITEM(x) &(x.list_item)
#define INT_ITEM(x) ((struct int_item*)(x))

struct list_item
{
    struct list_item* prev;
    struct list_item* next;
    unsigned int count;
};

struct int_item
{
    struct list_item list_item;
    int value;
};

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

    item->prev = tail;
    item->next = NULL;

    return item;  // Return the appended item.
};

unsigned int list_lenght(struct list_item* head)
{
    return head->count;
}

struct list_item* list_insert_after(struct list_item** head, struct list_item* after_item, struct list_item* new_item)
{
    if (!after_item || !new_item)
    {
        return NULL;  // If either the after_item or new_item is NULL, return NULL.
    }

    new_item->prev = after_item;
    new_item->next = after_item->next;

    if (after_item->next)
    {
        after_item->next->prev = new_item;  // Update the previous pointer of the item after the new_item.
    }

    after_item->next = new_item;  // Update the next pointer of after_item to new_item.

    (*head)->count++;  // Increment the count of items in the list.

    if (!new_item->next)
    {
        list_get_tail(new_item);  // If new_item is now the last item, update the tail of the list.
    }

    return new_item;  // Return the inserted item.
}

struct list_item* list_insert_before(struct list_item** head, struct list_item* before_item, struct list_item* new_item)
{
    if (!before_item || !new_item)
    {
        return NULL;  // If either the before or new_item is NULL, return NULL.
    }

    new_item->next = before_item;
    new_item->prev = before_item->prev;

    if (before_item->prev)
    {
        before_item->prev->next = new_item;  // Update the next pointer of the item before before_item.
    }

    before_item->prev = new_item;  // Update the prev pointer of before_item to new_item.

    (*head)->count++;  // Increment the count of items in the list.

    if (!new_item->prev)
    {
        struct list_item* last_head = (*head);
        (*head) = new_item;
        new_item->next = last_head;
        (*head)->count = last_head->count;  // If new_item becomes the first item, update the head and count.
    }

    return new_item;  // Return the inserted item.
}

struct list_item* list_remove_by_value(struct list_item** head, int value)
{
    if (!(*head))
    {
        return NULL;  // If the list is empty, return NULL.
    }

    struct list_item* current_head = *head;
    (*head)->prev = NULL;
    const unsigned int current_count = current_head->count;

    while (current_head)
    {
        struct int_item* int_item = INT_ITEM(current_head);

        if (int_item->value == value)
        {
            if ((*head)->prev)
            {
                (*head)->prev->next = current_head->next;
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

        (*head)->prev = current_head;
        current_head = current_head->next;
    }

    return current_head;
}

// Function to shuffle the linked list using Fisher-Yates algorithm
void list_shuffle(struct list_item** head)
{
    if (!head || !(*head) || !(*head)->next)
    {
        return;  // If the list is empty or has only one element, return.
    }

    // Initialize the random number generator with a different seed at each execution
    srand((unsigned int)time(NULL));

    // Calculate the length of the list
    unsigned int length = list_lenght(*head);

    // Fisher-Yates algorithm to shuffle the list
    struct list_item* current = *head;
    for (unsigned int i = length - 1; i > 0; --i)
    {
        // Generate a random index between 0 and i (inclusive)
        unsigned int j = rand() % (i + 1);

        // Swap values between the current element and the element at position j
        struct int_item* current_int_item = INT_ITEM(current);
        struct int_item* swap_int_item = INT_ITEM(current);

        // Find the element at position j
        for (unsigned int k = 0; k < j; ++k)
        {
            swap_int_item = INT_ITEM(swap_int_item->list_item.next);
        }

        // Swap values
        int temp = current_int_item->value;
        current_int_item->value = swap_int_item->value;
        swap_int_item->value = temp;

        // Move to the next element
        current = current->next;
    }
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

int main(int argc, char** argv)
{
    struct list_item* head = NULL;

    struct int_item int_item;
    int_item.value = 100;
    list_append(&head, LIST_ITEM(int_item));

    struct int_item int_item1;
    int_item1.value = 120;
    list_insert_after(&head, head, LIST_ITEM(int_item1));

    struct int_item int_item2;
    int_item2.value = 130;
    list_insert_after(&head, LIST_ITEM(int_item1), LIST_ITEM(int_item2));

    struct int_item int_item3;
    int_item3.value = 99;
    list_insert_before(&head, LIST_ITEM(int_item2), LIST_ITEM(int_item3));

    struct int_item int_item4;
    int_item4.value = 44;
    list_insert_before(&head, head, LIST_ITEM(int_item4));

    list_remove_by_value(&head, 100);

    PrintList(head);

    list_shuffle(&head);
    PrintList(head);

}