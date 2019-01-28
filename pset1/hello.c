#include <stdio.h>

int main(void)
{
    char name[10];
    printf("Please enter your name\n");
    scanf("%s", name);
    printf("Hello, %s!\n", name);
}