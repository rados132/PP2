#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 1000

typedef struct node
{
    char **info;
    struct node *next;
}
AddressBook;

char** readRow(FILE *input);
AddressBook* readFile(char *inputFile);
void removeContacts(AddressBook *head, char *displayName);
void writeFile(AddressBook *head);

int main(int argc, char *argv[])
{
    if (argc < 3 || argc > 4)
    {
        printf("ARG_GRESKA");
        exit(0);
    }
    FILE *input = fopen("ulaz.csv", "r");
    char **row = readRow(input);
    fclose(input);
    FILE *output = fopen("output.txt", "w");
    for (int i = 0; i < 37; i++)
    {
        fprintf(output, "%s\n", row[i]);
    }
    fclose(output);
    // AddressBook *addressBook = readFile(argv[1]);
    // writeFile(addressBook);
    // if (argc = 4)
    // {
    //     removeContacts(addressBook, argv[3]);
    // }
    return 0;
}

char** readRow(FILE *input)
{
    char buffer[BUFFER], **row;
    row = malloc(sizeof(char *));
    if (row == NULL)
    {
        printf("MEM_GRESKA");
        exit(0);
    }
    if (fgets(buffer, BUFFER, input) != NULL)
    {
        int charCnt = 0, columnCnt = 0;
        printf("%lu", strlen(buffer));
        for (int i = 0; i < strlen(buffer) - 1; i++, charCnt++)
        {
            if (buffer[i] == ',')
            {
                row = realloc(row, (columnCnt + 1) * sizeof(char *));
                if (row == NULL)
                {
                    printf("MEM_GRESKA");
                    exit(0);
                }
                row[columnCnt] = calloc(charCnt, sizeof(char));
                if (row[columnCnt] == NULL)
                {
                    printf("MEM_GRESKA");
                    exit(0);
                }
                if (i != 0 && buffer[i - 1] == ',')
                {
                    row[columnCnt][0] = '\0';
                }
                else
                { 
                    if ((i - charCnt) != 0)
                    {
                        strncpy(row[columnCnt], (buffer + i - charCnt + 1), charCnt - 1);
                    }
                    else
                    {       
                        strncpy(row[columnCnt], (buffer + i - charCnt), charCnt);
                    }
                }
                charCnt = 0;
                columnCnt++;
            }
        }       
        return row;
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
    if (input == NULL)
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
    char **row;
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

// void removeContacts(AddressBook *head, char *displayName)
// {
//     for (AddressBook *tmp = head; tmp != NULL; tmp = tmp->next)
//     {
        
//     }
    
// }

void writeFile(AddressBook *head)
{
    FILE *output;
    output = fopen("output.txt", "w");
    for (AddressBook *tmp = head; tmp != NULL; tmp = tmp->next)
    {
        for (int i = 0; i < 3; i++)
        {
            printf("%s ", tmp->info[i]);
        }
        putchar('\n');
    }
    fclose(output);
}
