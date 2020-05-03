#include <cs50.h>
#include <stdio.h>

void print_string_n(string str, int n)
{
    for (int i = 0; i < n; i += 1)
    {
        printf("%s", str);
    }
}

int main(void)
{
    int height;
    while (true)
    {
        height = get_int("Height: ");
        if (height > 0 && height < 9)
        {
            break;
        }
    }
    
    for (int i = 0; i < height; i += 1)
    {
        print_string_n(" ", height - i - 1);
        print_string_n("#", i + 1);
        printf("  ");
        print_string_n("#", i + 1);
        printf("\n");
    }
}