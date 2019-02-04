#include <stdio.h>

void valid_tri(int theight[2]);

int main(void)
{
    int theight[3];
    
    // Take triangle sides input
    for (int i =0; i<3; i++)
    {
        printf("Enter side %i: ", i+1);
        scanf("%i", &theight[i]);
    }
    // Call validation function
    valid_tri(theight);
    
}

void valid_tri(int theight[3])
{
    // Comparing size of sides
    if (theight[0] + theight[1] <= theight[2])
    {
        printf("Invalid Triangle!\n");
    }
    else
    {
        printf("Valid Triangle.\n");
    }
    
    
}
