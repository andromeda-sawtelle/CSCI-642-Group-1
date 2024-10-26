#include <stdio.h>

#define intSize sizeof(int)

int main() 
{
    bool usedWrong = false;
    usedWrong = useAfterFree();
}

bool useAfterFree() 
{
    const int count = 8;
    int *someInts = (int *) calloc(count, intSize);
    *someInts = [0, 8, 16, 24, 32, 40, 48, 56];

    printIntegers() 
}

void printIntegers(int *integers, int count)
{    
    for (int i = 0; i < count; ++i) {
        printf("%d\n", integers[i]);
    }
}
