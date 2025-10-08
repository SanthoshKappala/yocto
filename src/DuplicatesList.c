#include <stdio.h>
#include <stdlib.h>
#define HASH_SIZE 1000
struct Node {
    int data;
    struct Node *next;
};
struct Node *start = NULL;
int hashValue(int value) {
    return value % HASH_SIZE;
}
void removeDuplicatesByValue() {
    int hashTable[HASH_SIZE] = {0};
    struct Node *temp = start;
    struct Node *prev = NULL;

    while (temp != NULL) {
        int index = hashValue(temp->data);

        if (hashTable[index] == 1) {
            printf("Auto-removed duplicate value: %d\n", temp->data);

            if (prev != NULL)
                prev->next = temp->next;
            else
                start = temp->next;

            struct Node *del = temp;
            temp = temp->next;
            free(del);
            continue;
        }

        hashTable[index] = 1;
        prev = temp;
        temp = temp->next;
    }
}
void insert(int element) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = element;
    newNode->next = NULL;

    if (start == NULL)
        start = newNode;
    else {
        struct Node *temp = start;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
    removeDuplicatesByValue(); 
}
void deleteNode(int element) {
    if (start == NULL)
        return;
    struct Node *temp = start;
    struct Node *prev = NULL;
    if (temp != NULL && temp->data == element) {
        start = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->data != element) {
        prev = temp;
        temp = temp->next;
    }

    // If not found
    if (temp == NULL)
        return;

    prev->next = temp->next;
    free(temp);
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
