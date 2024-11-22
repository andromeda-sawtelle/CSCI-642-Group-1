#include <stdio.h>
#include <stdlib.h>

#define intSize sizeof(int)

static int whichPrint = 0;

void printIntegers(int *integers, int count)
{
    for (int i = 0; i < count; ++i)
        printf("\t\t%d\n", integers[i]);
    printf("\n");
}

int useAfterFree(int count) 
{
    printf("Use After Free\n");

    // Allocate a buffer on the heap
    int* someInts = calloc(intSize, count);
    for (int i = 0; i < count; i++)
        someInts[i] = 8 * i;

    // Check what's on the heap
    printf("\tClean Print\n");
    printIntegers(someInts, count);

    // Here's our free! Let's stop thinking about
    // what's at this address.
    free(someInts);

    // I know that address and I'm going to
    // manipulate the data to remove canaries.
    someInts[1] = 8;
    someInts[2] = 16;
    someInts[3] = 24;

    // We can even free it again and the compiler
    // has no complaints!
    free(someInts);

    // This is our data (plus a bit more) after a
    // second free.
    printf("\tMalicious Print\n");
    printIntegers(someInts, count + 4);
}

int bufferOverrun(int count, int overrun) 
{
    printf("Buffer Overrun");

    int *someInts = calloc(intSize, count);
    for (int i = 0; i < count; i++)
        someInts[i] = 8 * i;

    printIntegers(someInts, count + overrun);
}

int improperSynchronization() 
{
    // TODO:

}

enum mode {
    UAF, BO, IS, HELP, NONE
};

int validArgs(char *firstArg) 
{
    int validArg = firstArg[0] == '-';
    return validArg;
}

enum mode chooseMode(int argc, char *argv[])
{
    char *firstArg = argv[1];
    if (!validArgs(firstArg))
        return NONE;

    switch (firstArg[1]) {
    case 'u':
    case 'U':
        return UAF;
    case 'b':
    case 'B':
        return BO;
    case 'i':
    case 'I':
        return IS;
    case 'h':
    case 'H':
        return HELP;
    }

}

void help()
{
    printf(
"\
Usage: vulnprog <-u|-b|-i|-h> <count> <count2>\n\
    -u: runs a Use After Free exploit test\n\
    -b: runs a Buffer Overrun exploit test\n\
    -i: runs an Improper Synchronization exploit test\n\
    -h: show this help screen\n\
    count: an integer representing the number of entries to test.\n\
        Defaults to 8.\n\
    count2: in Buffer Overrun and Improper Synchronization mode,\n\
        a second count that is used for the overrun or for the\n\
        second thread depending. Defaults to 4.\n\
"
    );
}

int main(int argc, char *argv[]) 
{
    if (argc == 1) {
        help();
        return 0;
    }

    enum mode exploit = chooseMode(argc, argv);

    if (exploit == HELP) {
        help();
        return 0;
    }

    int count = 8;
    if (argc > 2)
        count = atoi(argv[2]);
    int count2 = 4;
    if (argc > 3)
        count2 = atoi(argv[3]);

    int usedWrong = 0;
    switch (exploit) {
    case UAF:
        useAfterFree(count);
        break;
    case BO:
        bufferOverrun(count, count2);
        break;
    case IS:

        break;
    }

}