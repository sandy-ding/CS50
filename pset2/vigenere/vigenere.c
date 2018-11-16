#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //only accept two command lines
    if (argc != 2)
    {
        printf("ERROR");
        return 1;
    }

    //store key
    string k = argv[1];

    //make sure key is alpha
    for (int i = 0, n = strlen(k); i < n; i++)
    {
        if (!isalpha(k[i]))
        {
            printf("ERROR");
            return 1;
        }
    }

    int m = strlen(k);
    string p = get_string("plaintext:");
    printf("ciphertext:");
    int j = 0;

    for (int i = 0, n = strlen(p); i < n; i++)
    {
        //use key when plaintext is alpha
        if (isalpha(p[i]))
        {
            //if plaintext is upper
            if (isupper(p[i]))
            {
                //if key is upper
                if (isupper(k[j % m]))
                {
                    p[i] = 65 + (p[i] - 65 + k[j % m] - 65) % 26;
                    printf("%c", p[i]);
                }
                //if key is lower
                if (islower(k[j % m]))
                {
                    p[i] = 65 + (p[i] - 65 + k[j % m] - 97) % 26;
                    printf("%c", p[i]);
                }
            }

            //if plaintext is lower
            else if (islower(p[i]))
            {
                //if key is upper
                if (isupper(k[j % m]))
                {
                    p[i] = 97 + (p[i] - 97 + k[j % m] - 65) % 26;
                    printf("%c", p[i]);
                }
                //if key is lower
                if (islower(k[j % m]))
                {
                    p[i] = 97 + (p[i] - 97 + k[j % m] - 97) % 26;
                    printf("%c", p[i]);
                }
            }
            j++;
        }
        //when plaintext is not alpha
        else
        {
            printf("%c", p[i]);
        }
    }
    printf("\n");
}