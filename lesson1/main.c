#include <stdio.h>
#include <string.h>
#include "inc/print.h"
#include "inc/calc.h"
void main()
{
    char my_string[100];
    int num1, num2;
    fgets(my_string, sizeof(my_string), stdin);
    my_string[strcspn(my_string, "\n")] = '\0';
    scanf("%d %d", &num1, &num2);
    hello(my_string);
    printf("Result %d + %d = %d\n", num1, num2, sum(num1, num2));
    printf("Result %d - %d = %d\n", num1, num2, sub(num1, num2));
    printf("Result %d * %d = %d\n", num1, num2, mul(num1, num2));
    if (div(num1, num2) == -1)
    {
        printf("Invalid argument was passed, cannot execute division");
    }
    else
        printf("Result %d / %d = %d\n", num1, num2, div(num1, num2));
}