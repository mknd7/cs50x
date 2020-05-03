#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float change;
    do
    {
        change = get_float("Change owed: ");
    }
    while (change <= 0);
    
    int cents = round(change * 100);
    
    int coins = cents / 25;
    cents = cents % 25;
    coins += cents / 10;
    cents = cents % 10;
    coins += cents / 5;
    cents = cents % 5;
    coins += cents;
    
    printf("%i\n", coins);
}