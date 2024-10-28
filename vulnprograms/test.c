
void customPutChar(char c)
{
    extern int write(int, const char *, unsigned int);
    (void) write(1, &c, 1);
}

void customPrint(char *str, int strlen)
{
    for (int i = 0; i < strlen; ++i) {
        customPutChar(str[i]);
    }
}

int main(int argc, char **argv)
{
    char *str = "Hello world!\n";
    int strlen = 12;
    
    customPrint(str, strlen);

    return 0;
}
