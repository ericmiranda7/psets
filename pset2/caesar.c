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
    int key = atoi(argv[1]), pbin[100];
    char ptext[100];
    printf("Enter plaintext: ");
    gets(ptext);
    printf("Ciphertext: ");

    // Loop for adding key to plaintext
    for (int i = 0; i < strlen(ptext); i++)
    {
        // Check if upper case
        if (ptext[i] >= 'A' && ptext[i] <= 'Z')
        {
            pbin[i] = ((int) ptext[i] + key - 'A') % 26 + 'A';
        }
        // Check if lower case
        else if (ptext[i] >= 'a' && ptext[i] <= 'z')
        {
            pbin[i] = ((int) ptext[i] + key - 'a') % 26 + 'a';
        }
        // Store non alphabets as same
        else
        {
            pbin[i] = (int) ptext[i];
        }    
        // Print ciphertext
        printf("%c", (char)pbin[i]);
    }
    printf("\n");
}   

