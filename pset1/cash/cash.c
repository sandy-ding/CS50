#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int coin = 0;
    int reminder ;

    //ask change owed
    do
    {
        reminder = round(get_float("Change owed: ") * 100);
    }
    while (reminder < 0);

    //count quarter
    int quarter ;
    if ((quarter = reminder / 25) && quarter > 0)
    {
        coin = + quarter;
        reminder = reminder % 25 ;
    }

    //count dime
    int dime ;
    if ((dime = reminder / 10) && dime > 0)
    {
        coin = coin + dime;
        reminder = reminder % 10 ;
    }

    //count nickel
    int nickel ;
    if ((nickel = reminder / 5) && nickel > 0)
    {
        coin = coin + nickel;
        reminder = reminder % 5 ;
    }

    //count penny
    int penny ;
    if ((penny = reminder / 1) && penny > 0)
    {
        coin = coin + penny;
    }
    printf("%i\n", coin);

}