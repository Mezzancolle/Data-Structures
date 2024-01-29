#include <set_linkedlist.h>

int main(int argc, char **argv)
{
    struct set_table* mySet = set_table_new(5,2);
    set_insert(mySet, "banana", 6);
    set_insert(mySet, "banana", 6);
    set_insert(mySet, "apple", 5);
    set_insert(mySet, "kiwi", 5);
    set_insert(mySet, "dog", 4);


    print_set(mySet);
    set_find(mySet, "apple");
    set_remove(mySet, "banana");
    print_set(mySet);


    return 0;
}