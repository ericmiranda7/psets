#include <stdio.h>

int main(void)
{
    int height;
    
    do {
        printf("Enter pyramid heights: \n");
        scanf("%i", &height);
    }
    while (height < 1 || height > 8);
    
    for (int lines = 0; lines < height; lines++) {
        for (int spaces = height - 1; spaces - lines > 0; spaces--) {
            printf(" ");
        }
        for (int hash = 0; lines - hash >= 0; hash ++) {
                printf("#");
            }
        printf("\n");
    }

}