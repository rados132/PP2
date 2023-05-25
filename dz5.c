#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct node
{
    char *info;
    struct node *next;
}
AddressBook;

char* readRow(FILE *input);
AddressBook* readFile(char *inputFile);
void removeContacts(AddressBook *head, char *displayName);

int main(int argc, char *argv[])
{
    if (argc < 3 || argc > 4)
    {
        printf("ARG_GRESKA");
        exit(0);
    }
    AddressBook *addressBook = readFile(argv[1]);
    if (argc = 4)
    {
        removeContacts(addressBook, argv[3]);
    }
    return 0;
}

char* readRow(FILE *input)
{
    char buffer[MAX], *row;
    if (fgets(buffer, MAX, input) != NULL)
    {
        row = calloc(strlen(buffer), sizeof(char));
        if (row == NULL)
        {
            printf("MEM_GRESKA");
            exit(0);
        }
        strcpy(row, buffer);
        return buffer;
    }
    else
    {
        return NULL;
    }
}

AddressBook* readFile(char *inputFile)
{
    FILE *input;
    input = fopen(inputFile, "r");
    if (input = NULL)
    {
        printf("DAT_GRESKA");
        exit(0);
    }
    AddressBook *head, *current, *tmp;
    head = malloc(sizeof(AddressBook));
    if (head == NULL)
    {
        printf("MEM_GRESKA");
        exit(0);
    }
    head->next = NULL;
    current = head;
    char *row;
    int contactsCnt = 0;
    while (row = readRow(input), row != NULL)
    {
        if ((contactsCnt++) == 0)
        {
            current->info = row;
        }
        else
        {
            tmp = malloc(sizeof(AddressBook));
            if (tmp == NULL)
            {
                printf("MEM_GRESKA");
                exit(0);
            }
            tmp->info = row;
            tmp->next = NULL;
            current->next = tmp;
            current = tmp;
        }
    }
    fclose(input);
    return head;
}

void removeContacts(AddressBook *head, char *displayName)
{
    
}
