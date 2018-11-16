#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 0 || n > 23);

    //draw the half-pyramid
    for (int i = 0; i < n ; i++)
    {
        //print left spaces
        for (int j = 0; j < n - 1 - i ; j++)
        {
            printf(" ");
        }
        //print left hashes
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        //print new line
        printf("  ");
        //print right hashes
        for (int j = 0; j < i + 1 ; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}