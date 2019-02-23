#include <crypt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function declarations
void bruteTimes(int, char *, char *);
void bruteForce(char *, int, int, char *, char *);

// Define list of alphabets
char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./crack [hash]");
        return(1);
    }

    // Remember user hash
    char *hash = argv[1];

    // Extract salt from user hash
    char *salt = malloc(2);
    for (int i = 0; i < 2; i++)
    {
        salt[i] = argv[1][i];
    }

    // Call for a maximum length of 5, as per specs
    bruteTimes(5, salt, hash);
}

void bruteTimes(int maxLen, char *salt, char *hash)
{
    // Storage for permutations
    char *buffer = malloc(maxLen + 1);

    // Run maxLen times
    for (int i = 0; i < maxLen; i++)
    {
        memset(buffer, 0, maxLen + 1);

        // Call function with storage string, index 0, length i, salt & user hash
        bruteForce(buffer, 0, i, salt, hash);
    }
}

void bruteForce(char *str, int index, int len, char *salt, char *hash)
{
    // Run alphabet list no. of times
    for (int i = 0, size = strlen(alphabet); i < size; i++)
    {
        str[index] = alphabet[i];
    
        // Base case
        if (index == len)
        {
            // Generate and store hash of string
            char *bruteHash = crypt(str, salt);

            // Compare brute generated hash and user hash
            if (strcmp(bruteHash, hash) == 0)
            {
                printf("Success at string: %s", str);
                
                // Exit program
                exit(6);
            }
        }
        // Recursive case
        else
        {
            bruteForce(str, index + 1, len, salt, hash);
        }
    }
}