#include <stdio.h>
#include <string.h>

int main()
{
    char buffer[10];
    char overflowString[40];

    // copies a string into too small of a buffer
    // this casuses an overflow error, which causes corruption of the stack
    // malicious actors can use this to perform a stack smashing attack.
    strcpy(buffer, overflowString);

    printf("%s\n", buffer);
    return 0;
}