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
        //print spaces
        for (int j = 0; j < n - 1 - i ; j++)
        {
            printf(" ");
        }
        //print hashes
        for (int k = 0; k < i + 2; k++)
        {
            printf("#");
        }
        //print new line
        printf("\n");
    }
}