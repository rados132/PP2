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

AddressBook* readFile(char *inputFile);
char** readRow(FILE *input);
void removeContacts(AddressBook *head, char *displayName);
void writeFile(AddressBook *head, char *outFile);
void freeMemory(AddressBook *head);

int main(int argc, char *argv[])
{
    if (argc < 3 || argc > 4)
    {
        printf("ARG_GRESKA");
        exit(0);
    }
    AddressBook *addressBook = readFile(argv[1]);
    if (argc == 4)
    {
        removeContacts(addressBook, argv[3]);
    }
    writeFile(addressBook, argv[2]);
    freeMemory(addressBook);
    return 0;
}

char** readRow(FILE *input)
{
    char buffer[BUFFER], **row;
    row = malloc(sizeof(char *));
    if (row == NULL)
    {
        printf("MEM_GRESKA");
        fclose(input);
        exit(0);
    }
    if (fgets(buffer, BUFFER, input) != NULL)
    {
        int charCnt = 0, columnCnt = 0;
        for (int i = 0; i < strlen(buffer) - 1; i++, charCnt++)
        {
            if (buffer[i] == ',')
            {
                row = realloc(row, (columnCnt + 1) * sizeof(char *));
                if (row == NULL)
                {
                    printf("MEM_GRESKA");
                    fclose(input);
                    exit(0);
                }
                row[columnCnt] = calloc(charCnt, sizeof(char));
                if (row[columnCnt] == NULL)
                {
                    printf("MEM_GRESKA");
                    fclose(input);
                    for (int j = 0; j < columnCnt; j++)
                    {
                        free(row[j]);
                    }
                    free(row);
                    exit(0);
                }
                if (i != 0 && buffer[i - 1] == ',')
                {
                    free(row[columnCnt]);
                    row[columnCnt] = NULL;
                }
                else
                { 
                    if ((i - charCnt) != 0)
                    {
                        if (buffer[i - charCnt + 1] == '"')
                        {
                            while (buffer[++i] != ',')
                            {
                                charCnt++;
                            }
                            row[columnCnt] = realloc(row[columnCnt], (charCnt + 1) * sizeof(char));
                            if (row[columnCnt] == NULL)
                            {
                                printf("MEM_GRESKA");
                                fclose(input);
                                exit(0);
                            }
                            strncpy(row[columnCnt], (buffer + i - charCnt + 1), charCnt - 2);
                        }
                        else
                        {
                            strncpy(row[columnCnt], (buffer + i - charCnt + 1), charCnt - 1);
                        }
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
        free(row);
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
    char **firstRow = readRow(input);
    if (firstRow == NULL)
    {
        fclose(input);
        return NULL;
    }
    else
    {
        for (int i = 0; firstRow[i] != NULL; i++)
        {
            free(firstRow[i]);
        }
        free(firstRow);
    }
    AddressBook *head, *current, *tmp;
    head = malloc(sizeof(AddressBook));
    if (head == NULL)
    {
        printf("MEM_GRESKA");
        fclose(input);
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
                fclose(input);
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
    AddressBook *tmp = head, *previous = NULL;
    while (tmp != NULL)
    {
        if (tmp == head && strstr(tmp->info[2], displayName) != NULL)
        {
            head = head->next;
            for (int i = 0; i < 38; i++)
            {
                free(tmp->info[i]);
            }
            free(tmp->info);
            free(tmp);
            tmp = head;
            previous = head;
        }
        else if (strstr(tmp->info[2], displayName) != NULL)
        {
            previous->next = tmp->next;
            for (int i = 0; i < 38; i++)
            {
                free(tmp->info[i]);
            }
            free(tmp->info);
            free(tmp);
            tmp = previous->next;
            
        }
        else
        {
            previous = tmp;
            tmp = tmp->next;
        }
    }      
}

void writeFile(AddressBook *head, char *outFile)
{
    FILE *output;
    output = fopen(outFile, "w");
    if (head == NULL)
    {
        fclose(output);
        return;
    }
    for (AddressBook *tmp = head; tmp != NULL; tmp = tmp->next)
    {
        fprintf(output, "dn: cn=%s,mail=%s\n", tmp->info[2], tmp->info[4]);
        fprintf(output, "objectclass: top\nobjectclass: person\nobjectclass: organizationalPerson\nobjectclass: inetOrgPerson\nobjectclass: mozillaAbPersonAlpha\n");
        if (tmp->info[0] != NULL)
        {
            fprintf(output, "givenName: %s\n", tmp->info[0]);
        }
        if (tmp->info[1] != NULL)
        {
            fprintf(output, "sn: %s\n", tmp->info[1]);
        }
        if (tmp->info[2] != NULL)
        {
            fprintf(output, "cn: %s\n", tmp->info[2]);
        }
        if (tmp->info[3] != NULL)
        {
            fprintf(output, "mozillaNickname: %s\n", tmp->info[3]);
        }
        if (tmp->info[4] != NULL)
        {
            fprintf(output, "mail: %s\n", tmp->info[4]);
        }
        if (tmp->info[5] != NULL)
        {
            fprintf(output, "mozillaSecondEmail: %s\n", tmp->info[5]);
        }

        fprintf(output, "modifytimestamp: 0\n");

        if (tmp->info[7] != NULL)
        {
            fprintf(output, "telephoneNumber: %s\n", tmp->info[7]);
        }
        if (tmp->info[8] != NULL)
        {
            fprintf(output, "homePhone: %s\n", tmp->info[8]);
        }
        if (tmp->info[9] != NULL)
        {
            fprintf(output, "facsimiletelephonenumber: %s\n", tmp->info[9]);
        }
        if (tmp->info[10] != NULL)
        {
            fprintf(output, "pager: %s\n", tmp->info[10]);
        }
        if (tmp->info[11] != NULL)
        {
            fprintf(output, "mobile: %s\n", tmp->info[11]);
        }
        if (tmp->info[12] != NULL)
        {
            fprintf(output, "mozillaHomeStreet: %s\n", tmp->info[12]);
        }
        if (tmp->info[14] != NULL)
        {
            fprintf(output, "mozillaHomeLocalityName: %s\n", tmp->info[14]);
        }
        if (tmp->info[15] != NULL)
        {
            fprintf(output, "mozillaHomeState: %s\n", tmp->info[15]);
        }
        if (tmp->info[16] != NULL)
        {
            fprintf(output, "mozillaHomePostalCode: %s\n", tmp->info[16]);
        }
        if (tmp->info[17] != NULL)
        {
            fprintf(output, "mozillaHomeCountryName: %s\n", tmp->info[17]);
        }
        if (tmp->info[18] != NULL)
        {
            fprintf(output, "street: %s\n", tmp->info[18]);
        }
        if (tmp->info[20] != NULL)
        {
            fprintf(output, "l: %s\n", tmp->info[20]);
        }
        if (tmp->info[21] != NULL)
        {
            fprintf(output, "st: %s\n", tmp->info[21]);
        }
        if (tmp->info[22] != NULL)
        {
            fprintf(output, "postalCode: %s\n", tmp->info[22]);
        }
        if (tmp->info[23] != NULL)
        {
            fprintf(output, "c: %s\n", tmp->info[23]);
        }
        if (tmp->info[24] != NULL)
        {
            fprintf(output, "title: %s\n", tmp->info[24]);
        }
        if (tmp->info[25] != NULL)
        {
            fprintf(output, "ou: %s\n", tmp->info[25]);
        }
        if (tmp->info[26] != NULL)
        {
            fprintf(output, "o: %s\n", tmp->info[26]);
        }
        if (tmp->info[27] != NULL)
        {
            fprintf(output, "mozillaWorkUrl: %s\n", tmp->info[27]);
        }
        if (tmp->info[28] != NULL)
        {
            fprintf(output, "mozillaHomeUrl: %s\n", tmp->info[28]);
        }
        if (tmp->info[36] != NULL)
        {
            fprintf(output, "description: %s\n", tmp->info[36]);
        }
        if (tmp->next != NULL)
        {
            fprintf(output, "\n");
        }       
    }
    fclose(output);
}

void freeMemory(AddressBook *head)
{
    AddressBook *tmp = NULL;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        for (int i = 0; i < 38; i++)
        {
            free(tmp->info[i]);
        }
        free(tmp->info);
        free(tmp);
    }
}
