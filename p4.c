/* Elijah Paulman */

/*
    Prototype 4 tests the llib any function
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Thing 
{
    char* str;
    struct Thing *next;
};

typedef bool (* CriteriaFunction)(void *data, void *helper);

bool any(struct Thing *head, CriteriaFunction yes, void *helper) 
{
    struct Thing *current = head;
    while (current != NULL) 
    {
        if (yes(current->str, helper)) 
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

bool isMatch(void *data, void *helper) 
{
    char *str = (char *)data;
    char *toMatch = (char *)helper;
    return strcmp(str, toMatch) == 0;
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
    struct Thing* head = createNode("Hello");
    head->next = createNode("World");
    head->next->next = createNode("Test");
    head->next->next->next = createNode("Systems");

    char* toMatch = "Systems";
    if (any(head, isMatch, toMatch)) 
    {
        printf("Match found!\n");
    } else 
    {
        printf("Match not found!\n");
    }

    return 0;
}