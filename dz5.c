#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct node
{
    char **contact;
    struct node *next;
}
AddressBook;

char** readLine(FILE *input);
AddressBook* readFile(char *inputFile);

int main(int argc, char *argv[])
{
    if (argc < 3 || argc > 4)
    {
        printf("ARG_GRESKA");
        exit(0);
    }
    if (argc = 4)
    {
        char *displayName = argv[3];
    }
    char *inputFile = argv[1];
    char *outputFile = argv[2];

    return 0;
}

char** readLine(FILE *input)
{
    char buffer[MAX];
    fgets(buffer, MAX, input);
    
}

AddressBook* readFile(char *inputFile)
{
    FILE *input;
    input = fopen(inputFile, "r");

    fclose(input);
}
