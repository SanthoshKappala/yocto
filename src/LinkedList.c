#include <stdio.h>
#include <stdlib.h>

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
    if (start == NULL) {
        start = newNode;
    } else {
        struct Node *temp = start;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void delete(int element) 
{
    if (start == NULL) return;

    struct Node *temp = start;
    struct Node *prev = NULL;

    if (temp->data == element)
    {
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
int main() {
    int choice, value;
    while (1) {
        printf("\n1.Insert\n2.Delete\n3.Display\n4.Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("enter the value to insert :");
                scanf("%d", &value);
                insert(value);
                break;
            case 2:
                printf("enter the value to delete from the list ");
                scanf("%d", &value);
                delete(value);
                break;
            case 3:
                display();
                break;
            case 4:
                exit(0);
        }
    }
    return 0;
}
