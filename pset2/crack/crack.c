#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define _XOPEN_SOURCE
#include <unistd.h>

int main(void)
{
    char salt[2] = {5,0};
    string p = get_string(crypt('A',salt));
    printf("%s\n",p);
}