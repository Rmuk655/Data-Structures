#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char str[100];
    fgets(str, sizeof(str), stdin); // Read a string from standard input
    for (int i = 0; i < strlen(str) - 1; i++)
    {
        printf("%c\n", *(str + i));
    }
    return 0;
}