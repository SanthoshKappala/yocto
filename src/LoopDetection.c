#include <stdio.h>
#include <stdlib.h>
#define HASH_SIZE 1000
struct Node {
    int data;
    struct Node *next;
};
struct Node *start = NULL;

int hashAddress(struct Node *addr) {
    return ((unsigned long)addr) % HASH_SIZE;
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
}

void display() {
    struct Node *slow = start, *fast = start;
    int loopDetected = 0;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            loopDetected = 1;
            break;
        }
    }

    struct Node *temp = start;
    int count = 0;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
        count++;

        if (loopDetected && count > 50) {
            printf("...LOOP DETECTED...\n");
            return;
        }
    }
    if (!loopDetected)
        printf("NULL\n");
}
void createLoop(int pos) {
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
    } else {
        printf("Invalid position.\n");
    }
}
int detectAndRemoveLoopByAddress() {
    struct Node *hashTable[HASH_SIZE] = {NULL};
    struct Node *temp = start;
    struct Node *prev = NULL;

    while (temp != NULL) {
        int index = hashAddress(temp);
        if (hashTable[index] == temp) {
            printf("Loop detected by ADDRESS at node with data = %d\n", temp->data);
            if (prev != NULL)
                prev->next = NULL;
            printf("Loop removed successfully.\n");
            return 1;
        }
        hashTable[index] = temp;
        prev = temp;
        temp = temp->next;
    }

    printf("No loop found (by address)\n");
    return 0;
}

int main() {
    int choice, value, pos;

    while (1) {
        printf("\n1.Insert\n2.Display\n3.Create Loop\n4.Detect+Remove Loop (Address)\n5.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert(value);
                break;
            case 2:
                display();
                break;
            case 3:
                printf("Enter position to create loop at: ");
                scanf("%d", &pos);
                createLoop(pos);
                break;
            case 4:
                detectAndRemoveLoopByAddress();
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
