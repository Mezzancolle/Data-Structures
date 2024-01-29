#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define CAST_LIST(x) &(x.list_item)
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

    item->prev = tail;
    item->next = NULL;

    return item;
};

unsigned int list_lenght(struct list_item* head)
{
    return head->count;
}

struct list_item* list_insert_after(struct list_item** head,struct list_item* after, struct list_item* new_item)
{
    if (!after || !new_item)
    {
        return NULL;
    }

    new_item->prev = after;
    new_item->next = after->next;

    if (after->next)
    {
        after->next->prev = new_item;
    }

    after->next = new_item;

    (*head)->count++;

    if (!new_item->next)
    {
        list_get_tail(new_item);
    }

    return new_item;
}

struct list_item* list_insert_before(struct list_item** head, struct list_item* before, struct list_item* new_item)
{
    if (!before || !new_item)
    {
        return NULL;
    }

    new_item->next = before;
    new_item->prev = before->prev;

    if (before->prev)
    {
        before->prev->next = new_item;
    }

    before->prev = new_item;

    (*head)->count++;

    if (!new_item->prev)
    {
        struct list_item* last_head = (*head);
        (*head) = new_item;
        new_item->next = last_head;
        (*head)->count = last_head->count;
    }
    
    return new_item;
}

struct list_item* list_remove_by_value(struct list_item** head, int value)
{
    if (!(*head))
    {
        return NULL;
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

void list_shuffle(struct list_item** head)
{
    if (!head || !(*head) || !(*head)->next)
    {
        return;
    }

    // Inizializza il generatore di numeri casuali con un seme diverso ad ogni esecuzione
    srand((unsigned int)time(NULL));

    // Calcola la lunghezza della lista
    unsigned int length = list_lenght(*head);

    // Algoritmo di Fisher-Yates per mescolare la lista
    struct list_item* current = *head;
    for (unsigned int i = length - 1; i > 0; --i)
    {
        // Genera un indice casuale compreso tra 0 e i incluso
        unsigned int j = rand() % (i + 1);

        // Scambia i valori tra l'elemento corrente e l'elemento alla posizione j
        struct int_item* current_int_item = INT_ITEM(current);
        struct int_item* swap_int_item = INT_ITEM(current);

        // Trova l'elemento alla posizione j
        for (unsigned int k = 0; k < j; ++k)
        {
            swap_int_item = INT_ITEM(swap_int_item->list_item.next);
        }

        // Scambia i valori
        int temp = current_int_item->value;
        current_int_item->value = swap_int_item->value;
        swap_int_item->value = temp;

        // Passa all'elemento successivo
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
    list_append(&head, CAST_LIST(int_item));

    struct int_item int_item1;
    int_item1.value = 120;
    list_insert_after(&head, head, CAST_LIST(int_item1));

    struct int_item int_item2;
    int_item2.value = 130;
    list_insert_after(&head, CAST_LIST(int_item1), CAST_LIST(int_item2));

    struct int_item int_item3;
    int_item3.value = 99;
    list_insert_before(&head, CAST_LIST(int_item2), CAST_LIST(int_item3));

    struct int_item int_item4;
    int_item4.value = 44;
    list_insert_before(&head, head, CAST_LIST(int_item4));

    list_remove_by_value(&head, 100);

    PrintList(head);

    list_shuffle(&head);
    PrintList(head);

}