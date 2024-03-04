/* Elijah Paulman */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "debug.h"
#include "altmem.h"
#include "linkedlist.h"

typedef struct Node
{
    struct Node *next;
    void *data;
} Node;

// creates a new node
static Node* allocate_node(void *data, int text) 
{
    Node *newNode = (Node*)alternative_malloc(sizeof(Node)); 
    static int nodeCount = 0; 
    if(newNode == NULL) 
    {
        if(text) printf("DIAGNOSTIC: Node allocation failed.\n");
        if(DEBUG) printf("DEBUG: linkedlist: allocation failed.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    if(text) printf("DIAGNOSTIC: %d nodes allocated.\n", ++nodeCount); 
    if(DEBUG) printf("DEBUG: linkedlist: allocated pointer is %p\n", (void*)newNode);
    return newNode;
}

// frees a node
static void free_node(Node *node, int text) 
{
    static int nodeCount = 0; 
    alternative_free(node);
    if(text) printf("DIAGNOSTIC: %d nodes freed.\n", ++nodeCount); 
}

// inserts a new node into the linked list
bool insert(void *p2head, void *data, ComparisonFunction goesInFrontOf, int text)
{
    Node *newNode = allocate_node(data, text);
    if (newNode == NULL) 
    {
        //free_node(newNode, text);
        return false;
    }

    Node **p2p2change = (Node**)p2head;
    while(*p2p2change != NULL && goesInFrontOf((*p2p2change)->data, newNode->data)) 
    {
        p2p2change = &((*p2p2change)->next);
    }
    newNode->next = *p2p2change;
    *p2p2change = newNode;

    return true;
}

// iterates over linkedlist and does someNode to each node
void iterate(void *head, ActionFunction doThis)
{
    Node *current = (Node*)head;
    while (current != NULL) 
    {
        doThis(current->data);
        current = current->next;
    }
}

// checks each node of list and returns true if any node meets the criteria
bool any(void *head, CriteriaFunction yes, void *helper)
{
    Node *current = (Node*)head;
    while (current != NULL) 
    {
        if (yes(current->data, helper)) 
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

// deletes nodes that meet the criteria
int deleteSome(void *p2head, CriteriaFunction mustGo, void *helper, ActionFunction disposal, int text)
{
    Node **p2p2change = (Node**)p2head;
    Node *holder;
    int count = 0;

    while (*p2p2change != NULL) 
    {
        if (mustGo((*p2p2change)->data, helper)) 
        {
            holder = *p2p2change;
            *p2p2change = (*p2p2change)->next;
            disposal(holder->data);
            free_node(holder, text);
            count++;
        } else 
        {
            p2p2change = &((*p2p2change)->next);
        }
    }

    return count;
}

// sorts the nodes in the linked list
void sort(void *hptr, ComparisonFunction cf)
{
    Node *current, *index;
    void *temp;

    for(current = (Node*)hptr; current != NULL && current->next != NULL; current = current->next) 
    {
        for(index = current->next; index != NULL; index = index->next) 
        {
            if(!cf(current->data, index->data) && current->data != index->data) 
            {
                temp = current->data;
                current->data = index->data;
                index->data = temp;
            }
        }
    }
}