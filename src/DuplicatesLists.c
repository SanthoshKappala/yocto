#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 1000

struct Node {
    int data;
    struct Node *next;
};

struct Node *start = NULL;
int hashTable[HASH_SIZE] = {0};   // global hash table for duplicate check

int hashValue(int value) {
    if (value < 0) value = -value;  // fix negative index
    return value % HASH_SIZE;
}

void insert(int element) {
    int index = hashValue(element);

    // Check duplicate BEFORE insertion
    if (hashTable[index] == 1) {
        printf("Duplicate value %d ignored automatically\n", element);
        return;
    }

    hashTable[index] = 1;  // Mark as present

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = element;
    newNode->next = NULL;

    if (start == NULL) {
        start = newNode;
    } else {
        struct Node *temp = start;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

void deleteNode(int element) {
    if (start == NULL) {
        printf("List is empty\n");
        return;
    }

    int index = hashValue(element);

    struct Node *temp = start;
    struct Node *prev = NULL;

    // Case 1: deleting head
    if (temp != NULL && temp->data == element) {
        start = temp->next;
        free(temp);
        hashTable[index] = 0;
        printf("Deleted %d\n", element);
        return;
    }

    // Case 2: search inside list
    while (temp != NULL && temp->data != element) {
        prev = temp;
        temp = temp->next;
    }

    // Case 3: not found
    if (temp == NULL) {
        printf("Element %d not found in list\n", element);
        return;
    }

    // Case 4: delete found node
    prev->next = temp->next;
    free(temp);
    hashTable[index] = 0;

    printf("Deleted %d\n", element);
}

void display() {
    struct Node *temp = start;

    if (temp == NULL) {
        printf("List is empty\n");
        return;
    }

    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    int choice, value;

    while (1) {
        printf("\n1. Insert\n2. Delete\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert(value);
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                deleteNode(value);
                break;

            case 3:
                display();
                break;

            case 4:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
