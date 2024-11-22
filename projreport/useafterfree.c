int useAfterFree(int count) {
    // Allocate a buffer on the heap
    int* someInts = calloc(intSize, count);
    for (int i = 0; i < count; i++)
        someInts[i] = 8 * i;

    // Check what's on the heap
    for (int i = 0; i < count; ++i)
        printf("\t\t%d\n", someInts[i]);
    printf("\n");

    // Free the buffer
    free(someInts);

    // This is our data after freeing
    for (int i = 0; i < count; ++i)
        printf("\t\t%d\n", someInts[i]);
    printf("\n");
}