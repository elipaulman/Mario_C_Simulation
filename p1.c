/* Elijah Paulman */

#include <stdio.h>
#include <stdlib.h>

struct Thing {
    int dval;
    struct Thing *next;
};

void insert(struct Thing *newnode, struct Thing **p2p2change) {
    printf("inserting %d (lives at %p)\n", newnode->dval, newnode);
    while(*p2p2change != NULL && (**p2p2change).dval > newnode->dval) {
        printf("Going past %d\n", (**p2p2change).dval);
        p2p2change = &((**p2p2change).next);
    }
    newnode->next = *p2p2change;
    *p2p2change = newnode;
    printf("Setting changed to %p, next to %p\n", *p2p2change, newnode->next);
}

struct Thing* createNode(int dval) {
    struct Thing* newNode = (struct Thing*)malloc(sizeof(struct Thing));
    newNode->dval = dval;
    newNode->next = NULL;
    return newNode;
}

void printList(struct Thing* head) {
    struct Thing* temp = head;
    while(temp != NULL) {
        printf("%d -> ", temp->dval);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    struct Thing* head = NULL;

    insert(createNode(5), &head);
    printList(head);

    insert(createNode(10), &head);
    printList(head);

    insert(createNode(3), &head);
    printList(head);

    return 0;
}