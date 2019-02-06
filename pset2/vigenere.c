#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void error(void);

int main(int argc, char *argv[])
{
    // Validate input
    if (argc == 2)
    {
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (!isalpha(argv[1][i]))
            {
                error();
            }
        }
    }
    else
    {
        error();
    }
    
    char ptext[100];
    int key[100], ciphertext[100];
    printf("Enter plaintext: ");
    gets(ptext);
    printf("\n");

    // Make key start from 0
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        key[i] = tolower(argv[1][i]) - 'a';
    }

    // Iterate through plaintext and convert to ciphertext
    for (int i = 0, sl = strlen(argv[1]), count = 0; i < strlen(ptext); i++)
    {
        if (ptext[i] >= 'A' && ptext[i] <= 'Z')
        {
            ciphertext[i] = (int)ptext[i] - 'A' + key[count%sl] % 26 + 'A';
            count++;
        }
        else if (ptext[i] >= 'a' && ptext[i] <= 'z')
        {
            ciphertext[i] = (int)ptext[i] - 'a' + key[count%sl] % 26 + 'a';
            count++;
        }
        // Using count as a method to 'reset' after space
        else
        {
            ciphertext[i] = ptext[i];
            count = 0;
        }
        printf("%c", (char)ciphertext[i]);
    }
}

// Display error function
void error(void)
{
    printf("Valid usage: ./vigenere [string key]\n");
    exit(3);
}