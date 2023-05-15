#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

char* readLine();
char** readLines(int *n);
void updateLines(int convertTo, char **lines, int n);

int main(void)
{
    int convertTo, n = 0;
    char **lines;
    scanf("%d", &convertTo);
    getchar();
    switch (convertTo)
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
    updateLines(convertTo, lines, n);
    for (int i = 0; i < n; i++)
    {
        int j = 0;
        while (lines[i][j] != '\0' && lines[i][j] != '!')
        {
            putchar(lines[i][j]);
            j++;
        }

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

void updateLines(int convertTo, char **lines, int n)
{
    for (int i = 0; i < n; i++)
    {
        int units[4][5] = {
            {-3, 0, 3, 6, 9},
            {-3, 0, 3, 6, 9},
            {-3, 0, 3, 6, 9},
            {-3, 0, 3, 6, 9}
        };

        char *find;
        char *unitPointer;
        int currentPwr;

        for (int p = 0; p < 4; p++)
        {
            for (int q = 0; q < 5; q++)
            {
                if (units[p][q] == convertTo)
                {
                    continue;
                }
                switch (p)
                {
                    case 0:
                        switch (q)
                        {
                            case 0:
                                find = "mHz";
                                currentPwr = -3;
                                break;
                            case 1:
                                find = "Hz";
                                currentPwr = 0;
                                break;
                            case 2:
                                find = "kHz";
                                currentPwr = 3;
                                break;
                            case 3:
                                find = "MHz";
                                currentPwr = 6;
                                break;
                            case 4:
                                find = "GHz";
                                currentPwr = 9;
                                break;
                        }
                        break;
                    case 1:
                        switch (q)
                        {
                            case 0:
                                find = "mm";
                                currentPwr = -3;
                                break;
                            case 1:
                                find = "m";
                                currentPwr = 0;
                                break;
                            case 2:
                                find = "km";
                                currentPwr = 3;
                                break;
                            case 3:
                                find = "Mm";
                                currentPwr = 6;
                                break;
                            case 4:
                                find = "Gm";
                                currentPwr = 9;
                                break;
                        }
                        break;
                    case 2:
                        switch (q)
                        {
                            case 0:
                                find = "mg";
                                currentPwr = -3;
                                break;
                            case 1:
                                find = "g";
                                currentPwr = 0;
                                break;
                            case 2:
                                find = "kg";
                                currentPwr = 3;
                                break;
                            case 3:
                                find = "Mg";
                                currentPwr = 6;
                                break;
                            case 4:
                                find = "Gg";
                                currentPwr = 9;
                                break;
                        }
                        break;
                    case 3:
                        switch (q)
                        {
                            case 0:
                                find = "mB";
                                currentPwr = -3;
                                break;
                            case 1:
                                find = "B";
                                currentPwr = 0;
                                break;
                            case 2:
                                find = "kB";
                                currentPwr = 3;
                                break;
                            case 3:
                                find = "MB";
                                currentPwr = 6;
                                break;
                            case 4:
                                find = "GB";
                                currentPwr = 9;
                                break;
                        }
                        break;
                }
                while (1)
                {
                    unitPointer = strstr(lines[i], find);
                    if (unitPointer == NULL)
                    {
                        break;
                    }
                
                    int index = unitPointer - lines[i];

                    if (!(isdigit(lines[i][index - 1])))
                    {
                        break;
                    }                    

                    int j = index;
                    while (j > 0 && lines[i][j - 1] != ' ' && lines[i][j - 1] != '(') // Provjeriti za zagradu
                    {
                        j--;
                    }

                    char number[index - j];
                    strncpy(number, (lines[i] + j), (index - j));
                    double value = atof(number);

                    char *unit;
                    switch (convertTo)
                    {
                        case -3:
                            switch (lines[i][index + 1])
                            {
                                case 'H':
                                    unit = "mHz";
                                    break;
                                case 'm':
                                    unit = "mm";
                                    break;
                                case 'g':
                                    unit = "mg";
                                    break;
                                case 'B':
                                    unit = "mB";
                                    break;
                                default:
                                    switch (lines[i][index])
                                    {
                                        case 'H':
                                            unit = "mHz";
                                            break;
                                        case 'm':
                                            unit = "mm";
                                            break;
                                        case 'g':
                                            unit = "mg";
                                            break;
                                        case 'B':
                                            unit = "mB";
                                            break;
                                    }
                            }
                            break;
                        case 3:
                            switch (lines[i][index + 1])
                            {
                                case 'H':
                                    unit = "kHz";
                                    break;
                                case 'm':
                                    unit = "km";
                                    break;
                                case 'g':
                                    unit = "kg";
                                    break;
                                case 'B':
                                    unit = "kB";
                                    break;
                                default:
                                    switch (lines[i][index])
                                    {
                                        case 'H':
                                            unit = "kHz";
                                            break;
                                        case 'm':
                                            unit = "km";
                                            break;
                                        case 'g':
                                            unit = "kg";
                                            break;
                                        case 'B':
                                            unit = "kB";
                                            break;
                                    }
                            }
                            break;
                        case 6:
                            switch (lines[i][index + 1])
                            {
                                case 'H':
                                    unit = "MHz";
                                    break;
                                case 'm':
                                    unit = "Mm";
                                    break;
                                case 'g':
                                    unit = "Mg";
                                    break;
                                case 'B':
                                    unit = "MB";
                                    break;
                                default:
                                    switch (lines[i][index])
                                    {
                                        case 'H':
                                            unit = "MHz";
                                            break;
                                        case 'm':
                                            unit = "Mm";
                                            break;
                                        case 'g':
                                            unit = "Mg";
                                            break;
                                        case 'B':
                                            unit = "MB";
                                            break;
                                    }
                            }
                            break;
                        case 9:
                            switch (lines[i][index + 1])
                            {
                                case 'H':
                                    unit = "GHz";
                                    break;
                                case 'm':
                                    unit = "Gm";
                                    break;
                                case 'g':
                                    unit = "Gg";
                                    break;
                                case 'B':
                                    unit = "GB";
                                    break;
                                default:
                                    switch (lines[i][index])
                                    {
                                        case 'H':
                                            unit = "GHz";
                                            break;
                                        case 'm':
                                            unit = "Gm";
                                            break;
                                        case 'g':
                                            unit = "Gg";
                                            break;
                                        case 'B':
                                            unit = "GB";
                                            break;
                                    }
                            }
                            break;       
                    }

                    int pwr = currentPwr - (convertTo);
                    value = value * pow(10, pwr);
                    long int whole = value;
                    char converted[100];
                    sprintf(converted, "%li", whole);

                    if (find == "mHz" || find == "kHz" || find == "MHz" || find == "GHz")
                    {
                        unitPointer += 3;
                        index += 3;
                    }
                    else if (find == "m" || find == "g" || find == "B")
                    {
                        unitPointer += 1;
                        index += 1;
                    }
                    else
                    {
                        unitPointer += 2;
                        index += 2;
                    }

                    char *tmp = calloc(j + strlen(converted) + strlen(unit) + strlen(lines[i]) - index, sizeof(char));
                    if (tmp == NULL)
                    {
                        printf("MEM_GRESKA");
                        exit(0);
                    }

                    strncpy(tmp, lines[i], j);
                    strcat(tmp, converted);
                    strcat(tmp, unit);
                    strcat(tmp, unitPointer);
                    free(lines[i]);
                    lines[i] = calloc(strlen(tmp), sizeof(char));
                    if (lines[i] == NULL)
                    {
                        printf("MEM_GRESKA");
                        exit(0);
                    }

                    strcpy(lines[i], tmp);
                    free(tmp);
                }
            }           
        }
    }
}
