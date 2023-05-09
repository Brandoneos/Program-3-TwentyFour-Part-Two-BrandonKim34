#include <stdio.h>
#include <stdlib.h>

int evaluate_expression(char *expr) {
    int result = 0;
    int sign = 1;
    int num = 0;
    int factor = 1;
    int divisor = 1;

    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];

        if (ch >= '0' && ch <= '9') {
            num = num * 10 + (ch - '0');
        } else if (ch == '-') {
            result += sign * factor * (num / divisor);
            num = 0;
            sign = -1;
            factor = 1;
            divisor = 1;
        } else if (ch == '+') {
            result += sign * factor * (num / divisor);
            num = 0;
            sign = 1;
            factor = 1;
            divisor = 1;
        } else if (ch == '*') {
            factor *= num;
            num = 0;
        } else if (ch == '/') {
            divisor *= num;
            num = 0;
        } else if (ch == '(') {
            int j = i + 1;
            int count = 1;

            while (expr[j] != '\0' && count > 0) {
                if (expr[j] == '(') {
                    count++;
                } else if (expr[j] == ')') {
                    count--;
                }

                j++;
            }

            if (count > 0) {
                printf("Invalid expression: unbalanced parentheses\n");
                exit(1);
            }

            num = evaluate_expression(&expr[i+1]);
            i = j - 1;
        } else if (ch == ' ') {
            continue;
        } else {
            printf("Invalid expression: unsupported character '%c'\n", ch);
            exit(1);
        }
    }

    result += sign * factor * (num / divisor);

    return result;
}

int main() {
    char expr[100];

    printf("Enter an arithmetic expression: ");
    fgets(expr, sizeof(expr), stdin);

    int result = evaluate_expression(expr);

    printf("Result: %d\n", result);

    return 0;
}