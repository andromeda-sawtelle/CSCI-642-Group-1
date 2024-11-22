#include <stdio.h>
#include <string.h>

int main()
{
    char buffer[10];
    char overflowString[40];

    // this casuses an overflow error
    // which corrupts the stack
    strcpy(buffer, overflowString);

    printf("%s\n", buffer);
    return 0;
}