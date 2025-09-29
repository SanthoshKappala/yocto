#include <stdio.h>
int main() {
    float a, b, result;
    int choice;
    printf("Enter two numbers: ");
    scanf("%f %f", &a, &b);
    printf("Choose operation:\n");
    printf("1. Add\n2. Subtract\n3. Multiply\n4. Divide\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            result = a + b;
            printf("Result: %.2f\n", result);
            break;
        case 2:
            result = a - b;
            printf("Result: %.2f\n", result);
            break;
        case 3:
            result = a * b;
            printf("Result: %.2f\n", result);
            break;
        case 4:
            if (b == 0) {
                printf("Error: Division by zero\n");
            } else {
                result = a / b;
                printf("Result: %.2f\n", result);
            }
            break;
        default:
            printf("Invalid choice\n");
    }
    return 0;
}
