#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //only accept two command line
    if (argc != 2)
    {
        printf("ERROR");
        return 1;
    }

    //turn string into int
    int k = atoi(argv[1]);

    string p = get_string("plaintext:");
    printf("ciphertext:");

    for (int i = 0, n = strlen(p); i < n; i++)
    {
        //use key when is alpha
        if (isalpha(p[i]))
        {
            if (isupper(p[i]))
            {
                p[i] = 65 + (p[i] - 65 + k) % 26;
                printf("%c", p[i]);
            }
            else  if (islower(p[i]))
            {
                p[i] = 97 + (p[i] - 97 + k) % 26;
                printf("%c", p[i]);
            }
        }
        else
        {
            printf("%c", p[i]);
        }
    }
    printf("\n");
}