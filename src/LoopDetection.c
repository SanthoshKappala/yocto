#include <stdio.h>
#include <stdlib.h>
#define HASH_SIZE 1000
struct Node {
    int data;
    struct Node *next;
};
struct Node *start = NULL;
void insert(int element)
{
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
}
void deleteNode(int element)
{
    if (start == NULL) return;
    struct Node *temp = start;
    struct Node *prev = NULL;

    if (temp->data == element) {
        start = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->data != element) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;

    prev->next = temp->next;
    free(temp);
}

void display()
{
    struct Node *temp = start;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
int hashAddress(struct Node *addr) {
    return ((unsigned long)addr) % HASH_SIZE;
}
int hashValue(int value) {
    return value % HASH_SIZE;
}
int detectLoopByAddress()
{
    struct Node *hashTable[HASH_SIZE] = {NULL};
    struct Node *temp = start;

    while (temp != NULL) {
        int index = hashAddress(temp);
        if (hashTable[index] == temp) {
            printf("Loop detected by ADDRESS at node with data = %d\n", temp->data);
            return 1;
        }
        hashTable[index] = temp;
        temp = temp->next;
    }
    printf("No loop found (by address)\n");
    return 0;
}
int detectLoopByValue()
{
    int hashTable[HASH_SIZE] = {0};
    struct Node *temp = start;

    while (temp != NULL) {
        int index = hashValue(temp->data);
        if (hashTable[index] == 1) {
            printf("Loop detected by VALUE at data = %d\n", temp->data);
            return 1;
        }
        hashTable[index] = 1;
        temp = temp->next;
    }

    printf("No loop found (by value)\n");
    return 0;
}
void removeLoopByHash()
{
    struct Node *hashTable[HASH_SIZE] = {NULL};
    struct Node *temp = start;
    struct Node *prev = NULL;

    while (temp != NULL) {
        int index = hashAddress(temp);
        if (hashTable[index] == temp) {
            printf("Loop found and removed at node with data = %d\n", temp->data);
            if (prev != NULL)
                prev->next = NULL;
            return;
        }
        hashTable[index] = temp;
        prev = temp;
        temp = temp->next;
    }

    printf("No loop to remove.\n");
}

void createLoop(int pos)
{
    if (start == NULL) return;

    struct Node *loopNode = NULL;
    struct Node *temp = start;
    int count = 1;

    while (temp->next != NULL) {
        if (count == pos)
            loopNode = temp;
        temp = temp->next;
        count++;
    }

    if (loopNode != NULL) {
        temp->next = loopNode;
        printf("Loop created at position %d (node with data = %d)\n", pos, loopNode->data);
    }
}
int main()
{
    int choice, value, pos;

    while (1) {
        printf("\n1.Insert\n2.Delete\n3.Display\n4.Create Loop\n5.Detect Loop (Address)\n6.Detect Loop (Value)\n7.Remove Loop\n8.Exit\n");
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
                printf("Enter position to create loop at: ");
                scanf("%d", &pos);
                createLoop(pos);
                break;
            case 5:
                detectLoopByAddress();
                break;
            case 6:
                detectLoopByValue();
                break;
            case 7:
                removeLoopByHash();
                break;
            case 8:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
