#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long ccnumber = get_long("Number: ");
    long ccnumcopy = ccnumber;
    int mul_sum = 0, alt_sum = 0, temp;
    int num_digits = 0;

    while (ccnumcopy != 0)
    {
        alt_sum += ccnumcopy % 10;
        ccnumcopy = ccnumcopy / 10;
        num_digits += 1;
        if (ccnumcopy == 0)
        {
            break;
        }
        
        temp = 2 * (ccnumcopy % 10);
        if (temp > 9)
        {
            temp = (1 + temp % 10);
        }
        
        mul_sum += temp;
        ccnumcopy = ccnumcopy / 10;
        num_digits += 1;
    }
    
    int total_sum = mul_sum + alt_sum;
    if (total_sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        ccnumcopy = ccnumber;
        while (ccnumcopy / 10 > 10)
        {
            ccnumcopy = ccnumcopy / 10;
        }

        if ((ccnumcopy >= 51 && ccnumcopy <= 55) && num_digits == 16)
        {
            printf("MASTERCARD\n");
        }
        else if ((ccnumcopy == 34 || ccnumcopy == 37) && num_digits == 15)
        {
            printf("AMEX\n");
        }
        else
        {
            ccnumcopy = ccnumcopy / 10;
            if (ccnumcopy == 4 && (num_digits == 13 || num_digits == 16))
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }
}