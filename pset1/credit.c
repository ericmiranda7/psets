#include <stdio.h>
#include <math.h>

int luhn(long);

int main(void)
{
    long ccn, chk;
    int count = 0;

    for (;;) {
        // Take input
        printf("Type in your credit card number WITHOUT hyphen: ");
        scanf("%ld", &ccn);
        chk = ccn;

        // Count digits
        while (chk > 0) {
            chk /= 10;
            count++;
        }

        // Evaluate card type
        if (luhn(ccn) == 1) {
            if (count == 15) {
                printf("Amex\n");
                break;
            }
            else if (count == 13 || count == 16) {
                long b = ccn / (pow(10, (count-1)));
                if (b == 4) {
                    printf("Visa\n");
                    break;
                }
                else {
                    printf("MasterCard\n");
                    break;
                }
            }
        }
        else {
            printf("Invalid !\n");
        }

    }
}

// Luhn's algorithim function
int luhn(long ccn) 
{
    long mult = 0, alt = 0;
    int v;

    for (long i = 100; (ccn / i) >= 0; i*=100) {
        long calc = (ccn % i)/(i/10)*2;

        // Add digits of product of alternate digits multiplied by 2
        if (calc / 10 == 0) {
            mult = mult + calc;
        }
        else {
            mult = mult + (calc/10) + (calc%10);
        }

        // Add other digits
        alt = alt + (ccn % (i/10))/(i/100);

        if (ccn / i == 0) {
            break;
        }
    }

    // Sum
    long result = mult + alt;

    // Return 1 for valid or 0 for invalid
    if ((result % 10) == 0) {
        return v = 1;
    }
    else {
        return v = 0;
    } 

}