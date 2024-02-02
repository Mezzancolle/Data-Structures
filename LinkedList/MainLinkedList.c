#include <linkedlist.h>

int main(int argc, char** argv)
{
    struct list_item* head = NULL;

    struct int_item int_item;
    int_item.value = 100;
    list_append(&head, LIST_ITEM(int_item));

    struct int_item int_item2;
    int_item2.value = 101;
    list_append(&head, LIST_ITEM(int_item2));

    struct int_item int_item3;
    int_item3.value = 120;
    list_append(&head, LIST_ITEM(int_item3));

    list_remove_by_value(&head, 101);

    list_reverse(&head);

    PrintList(head);

    return 0;
}