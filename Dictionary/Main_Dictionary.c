#include <Dictionary.h>

int main(int argc, char** argv)
{
    struct dictionary* myDictionary = dictionary_new(3, 2, INT_TYPE);
    struct dictionary* myDictionary1 = dictionary_new(3, 2, CHAR_TYPE);

    int value1 = 42;
    int value2 = 22;
    int value3 = 33;

    dictionary_insert(myDictionary, "apple", strlen("apple"), &value1);
    dictionary_insert(myDictionary, "kiwi", strlen("kiwi"), &value2);
    dictionary_insert(myDictionary, "dog", strlen("dog"), &value3);

    print_dictionary(myDictionary);
    dictionary_remove(myDictionary, "kiwi");
    print_dictionary(myDictionary);


    char* value4 = "red apple";
    char* value5 = "a very nice kiwi";
    char* value6 = "this is not a fruit";

    dictionary_insert(myDictionary1, "apple", strlen("apple"), &value4);
    dictionary_insert(myDictionary1, "kiwi", strlen("kiwi"), &value5);
    dictionary_insert(myDictionary1, "dog", strlen("dog"), &value6);

    print_dictionary(myDictionary1);
}