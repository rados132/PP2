/*
    Napisati program koji pronalazi najveći i najmanji broj poena koji je ostvaren na svakom od domaćih zadataka.

    Program treba da:

    1. Učita dužinu niza, a zatim u novom redu i niz celih brojeva.

    2. Ispiše niz na standardni izlaz.

    3. Formira novi niz koji sadrži najveći broj poena ostvaren na svakom od domaćih zadataka.

    4. Formira novi niz koji sadrži najmanji broj poena ostvaren na svakom od domaćih
    zadataka.

    5. Ispiše rezultujuće nizove na standardni izlaz.
*/

#include <stdio.h>

#define MAX 1000
#define NO_OF_ASSIGNMENTS 5

int main(void)
{
    int n, points[MAX - 1];                      
    scanf("%d", &n);
    n = n * NO_OF_ASSIGNMENTS;                       
    if (n <= 0 || n > MAX)
    {
        return 1;
    }
    int t;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &t);
        if (t >= 0 && t <= 7)
        {
            points[i] = t;
        }
        else
        {
            return 1;
        }
    }
    for (int i = 0; i < n; i++)                 
    {
        if (i != n - 1)
        {
            printf("%d ", points[i]);
        }
        else
        {
            printf("%d\n", points[i]);
        }
    }                                  
    int maxPoints[MAX];
    for (int i = 0; i < NO_OF_ASSIGNMENTS; i++)
    {
        t = points[i];
        for (int j = i + NO_OF_ASSIGNMENTS; j < n; j += NO_OF_ASSIGNMENTS)
        {
            if (points[j] > t)
            {
                t = points[j];
            }
        }
        maxPoints[i] = t;
    }
    int minPoints[MAX];                         
    for (int i = 0; i < NO_OF_ASSIGNMENTS; i++)      
    {
        t = points[i];
        for (int j = i + NO_OF_ASSIGNMENTS; j < n; j += NO_OF_ASSIGNMENTS)
        {
            if (points[j] < t)
            {
                t = points[j];
            }
        }
        minPoints[i] = t;
    }
    for (int i = 0; i < NO_OF_ASSIGNMENTS; i++)
    {
        if (i != NO_OF_ASSIGNMENTS - 1)
        {
            printf("%d ", maxPoints[i]);
        }
        else
        {
            printf("%d\n", maxPoints[i]);
        }
    }
    for (int i = 0; i < NO_OF_ASSIGNMENTS; i++)                      
    {
        if (i != NO_OF_ASSIGNMENTS - 1)
        {
            printf("%d ", minPoints[i]);
        }
        else
        {
            printf("%d\n", minPoints[i]);
        }
    }
    return 0;
}
