#include <stdio.h>
#include <math.h>

int main(void)
{
    float money;
    int doll, cents, count;
    printf("How much change is owed ?: ");
    scanf("%f", &money);
    doll = (int)money;
    cents = round((money - doll)*100);

    if (doll > 0)
    {
        count = doll*4;
    }

    do {
        if (cents >= 25)
        {
            cents = cents - 25;
            count++;
        }
        else if (cents >= 10)
        {
            cents = cents - 10;
            count++;
        }
        else if (cents >= 5)
        {
            cents = cents - 5;
            count++;
        }
        else if (cents >= 1)
        {
            cents = cents - 1;
            count++;
        }
    } while (cents > 0);
    printf("No. of coins is: %i\n", count);
}