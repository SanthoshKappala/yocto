#include <stdio.h>

float add(float a, float b) {
    return a + b;
}

float sub(float a, float b) {
    return a - b;
}

float mul(float a, float b) {
    return a * b;
}

float divide(float a, float b) {
    if (b == 0) {
        printf("Error: Division by zero\n");
        return 0.0;
    }
    return a / b;
}

int main() {
    float a, b, result;
    int choice;

    printf("Enter two numbers: ");
    if (scanf("%f %f", &a, &b) != 2) {
        printf("Invalid input\n");
        return 1;
    }

    printf("Choose operation:\n");
    printf("1. Add\n2. Subtract\n3. Multiply\n4. Divide\n");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    float (*operation)(float, float) = NULL;

    switch (choice) {
        case 1:
            operation = add;
            break;
        case 2:
            operation = sub;
            break;
        case 3:
            operation = mul;
            break;
        case 4:
            operation = divide;
            break;
        default:
            printf("Invalid choice\n");
            return 1;
    }

    result = operation(a, b);
    printf("Result: %.2f\n", result);

    return 0;
}
