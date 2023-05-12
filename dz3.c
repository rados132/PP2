#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readLine();
char** readLines(int *n);

int main(void)
{
    //stdin = fopen("input.txt", "r");
    int pwr, n = 0;
    char **lines;
    scanf("%d", &pwr);
    getchar();
    switch (pwr)
    {
        case -3:
            break;

        case 3:
            break;

        case 6:
            break;

        case 9:
            break;

        default:
            printf("GRESKA");
            return 0;
    }
    lines = readLines(&n);
    for (int i = 0; i < n; i++)
    {
        printf("%s", lines[i]);
        if (i != n - 1)
        {
            putchar('\n');
        }
    }
    for (int i = 0; i <= n; i++)
    {
        free(lines[i]);
    }
    free(lines);
    return 0;
}

char* readLine()
{
    char *line, buffer[100];
    int len;
    if (fgets(buffer, 100, stdin) != NULL)
    {
        len = strlen(buffer);
        if (buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }
        line = malloc(len * sizeof(char));
        if (line == NULL)
        {
            printf("MEM_GRESKA");
            exit(0);
        }
        strcpy(line, buffer);
        return line;
    }
    else
    {
        return NULL;
    }
}

char** readLines(int *n)
{
    char **lines;
    lines = malloc(sizeof(char *));
    if (lines == NULL)
    {
        printf("MEM_GRESKA");
        exit(0);
    }
    int i = 0;
    char *tmp;
    while (1)
    {
        tmp = readLine();
        if (tmp == NULL)
        {
            break;
        }
        lines[i++] = tmp;
        lines = realloc(lines, (i + 1) * sizeof(char *));
        if (lines == NULL)
        {
            printf("MEM_GRESKA");
            for (int i = 0; i <= *n; i++)
            {
                free(lines[i]);
            }
            free(lines);
            exit(0);
        }
        (*n)++;
    }
    return lines;
}
