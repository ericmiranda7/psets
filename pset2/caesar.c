#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    // Validate Input
    if (argc == 2)
    {
        for (int i = 0; i < strlen(argv[1]); i ++)
        {
            if (atoi(&argv[1][i]) == 0)
            {
                printf("Valid usage: ./caesar [key]\n");
                return 1;
            }
        }
    }
    else
    {
        printf("Valid usage: ./caesar [key]\n");
        return 1;
    }
    // Initialise arrays
    int key = atoi(argv[1]);
    int pbin[100];
    char ptext[100];
    printf("Enter plaintext: ");
    gets(ptext);
    printf("Ciphertext: ");

    // Add key to plaintext
    for (int i = 0; i < strlen(ptext); i++)
    {
        for (int j = 0; j < strlen(ptext); j++)
        {
            if (ptext[j] >= 'A' && ptext[j] <= 'Z')
            {
                pbin[j] = ((int) ptext[j] + key - 'A') % 26 + 'A';
            }
            else if (ptext[j] >= 'a' && ptext[j] <= 'z')
            {
                pbin[j] = ((int) ptext[j] + key - 'a') % 26 + 'a';
            }
            // Store non alphabets as same
            else
            {
                pbin[j] = (int) ptext[i];
            }    
        }
        // Print ciphertext
        printf("%c", (char)pbin[i]);
    }
    printf("\n");
}   

