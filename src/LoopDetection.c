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
int detectAndRemoveLoopByAddress()
{
    struct Node *hashTable[HASH_SIZE] = {NULL};
    struct Node *temp = start;
    struct Node *prev = NULL;

    while (temp != NULL) {
        int index = hashAddress(temp);
        if (hashTable[index] == temp) {
            printf("Loop detected by ADDRESS at node with data = %d\n", temp->data);
            if (prev != NULL)
                prev->next = NULL;
            printf("Loop removed and node %d deleted from index %d\n", temp->data, index);
            free(temp);
            return 1;
        }
        hashTable[index] = temp;
        prev = temp;
        temp = temp->next;
    }

    printf("No loop found (by address)\n");
    return 0;
}
int detectAndRemoveByValue()
{
    int hashTable[HASH_SIZE] = {0};
    struct Node *temp = start;
    struct Node *prev = NULL;

    while (temp != NULL) {
        int index = hashValue(temp->data);
        if (hashTable[index] == 1) {
            printf("Duplicate detected by VALUE at data = %d\n", temp->data);
            if (prev != NULL)
                prev->next = temp->next;
            else
                start = temp->next;
            printf("Duplicate value %d removed from index %d\n", temp->data, index);
            free(temp);
            return 1;
        }
        hashTable[index] = 1;
        prev = temp;
        temp = temp->next;
    }

    printf("No duplicate value found.\n");
    return 0;
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
        printf("\n1.Insert\n2.Delete\n3.Display\n4.Create Loop\n5.Detect+Remove Loop (Address)\n6.Detect+Remove Duplicate (Value)\n7.Exit\n");
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
                detectAndRemoveLoopByAddress();
                break;
            case 6:
                detectAndRemoveByValue();
                break;
            case 7:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
