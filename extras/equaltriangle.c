#include <stdio.h>

void valid_tri(int theight[2]);

int main(void)
{
    int theight[3];
    
    for (int i =0; i<3; i++)
    {
        printf("Enter side %i: ", i+1);
        scanf("%i", &theight[i]);
        printf("%i", theight[i]);
    }
    valid_tri(theight);
    
}

void valid_tri(int theight[3])
{
    if (theight[0] + theight[1] <= theight[2])
    {
        printf("Invalid Triangle!");
    }
    else
    {
        printf("Valid Triangle.");
    }
    
    
}
