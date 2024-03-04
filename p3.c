/* Elijah Paulman */

/*
    Prototype 3 tests sorting a linked list.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Thing 
{
    char* str;
    struct Thing *next;
};

typedef bool (* ComparisonFunction)(void *data1, void *data2);

void sort(struct Thing **head, ComparisonFunction cf) 
{
    struct Thing *current, *index;
    char *temp;

    for(current = *head; current->next != NULL; current = current->next) 
    {
        for(index = current->next; index != NULL; index = index->next) 
        {
            if(cf(current->str, index->str))
             {
                temp = current->str;
                current->str = index->str;
                index->str = temp;
            }
        }
    }
}

bool compareStrings(void *data1, void *data2) 
{
    char *str1 = (char *)data1;
    char *str2 = (char *)data2;
    return strcmp(str1, str2) > 0;
}

void printList(struct Thing* head) 
{
    struct Thing* temp = head;
    while(temp != NULL) 
    {
        printf("%s -> ", temp->str);
        temp = temp->next;
    }
    printf("NULL\n");
}

struct Thing* createNode(char* str) 
{
    struct Thing* newNode = (struct Thing*)malloc(sizeof(struct Thing));
    newNode->str = str;
    newNode->next = NULL;
    return newNode;
}

int main() 
{
    struct Thing* head = createNode("World");
    head->next = createNode("Hello");
    head->next->next = createNode("Test");
    head->next->next->next = createNode("Systems");

    printf("Before sorting:\n");
    printList(head);

    sort(&head, compareStrings);

    printf("After sorting:\n");
    printList(head);

    return 0;
}