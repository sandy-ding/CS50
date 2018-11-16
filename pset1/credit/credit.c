#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    long long credit;
    int digit[16] ;
    int multi[8];
    int sum = 0;

    //ask credit number
    do
    {
        credit = get_long_long("Number: ");
    }
    while (credit <= 0);

    //get every digit
    for (int i = 0 ; i < 16 ; i++)
    {
        long long n = pow(10, i + 1);
        long long m = pow(10, i);
        digit[i] = credit % n / m;
    }

    //multiply and add number
    for (int i = 0 ; i < 8 ; i++)
    {
        multi[i] = 2 * digit[2 * i + 1];
        sum = sum + multi[i] / 10 + multi[i] % 10;
        sum = sum + digit[2 * i];
    }

    //verify card
    if (sum % 10 == 0)
    {
        if (digit[15] == 0 && digit[14] == 3 && (digit[13] == 4 || digit[13] == 7))
        {
            printf("AMEX\n");
        }
        else if (digit[15] == 5 && (digit[14] == 1 || digit[14] == 2 || digit[14] == 3 || digit[14] == 4 || digit[14] == 5))
        {
            printf("MASTERCARD\n");
        }
        else if ((digit[15] == 0 && digit[14] == 0 && digit[13] == 0 && digit[12] == 4) || (digit[15] == 4))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }


}