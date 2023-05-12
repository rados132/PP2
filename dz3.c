#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readLine();
char** readLines(int *n);

int main(void)
{
    int pwr;
    char *line;
    scanf("%d", &pwr);
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
    // line = readLine();
    // printf("%s", line);
    free(line);
    return 0;
}

char *readLine()
{
    char c, *line;
    line = malloc(sizeof(char));
    if (line == NULL)
    {
        printf("MEM_GRESKA");
        exit(0);
    }
    int i = 0;
    getchar();
    while ((c = getchar()) != '\n')
    {
        line[i++] = c;
        line = realloc(line, (i + 1) * sizeof(char));
    }
    line[i] = '\0';
    return line;
}
