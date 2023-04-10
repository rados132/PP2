/*
    Napisati program koji pronalazi najveći i najmanji broj poena koji je ostvaren na svakom od domaćih zadataka.
    Program treba da:
    1) Učita dužinu niza, a zatim u novom redu i niz celih brojeva.
    2) Ispiše niz na standardni izlaz.
    3) Formira novi niz koji sadrži najveći broj poena ostvaren na svakom od domaćih zadataka.
    4) Formira novi niz koji sadrži najmanji broj poena ostvaren na svakom od domaćih
    zadataka.
    5) Ispiše rezultujuće nizove na standardni izlaz.
*/

#include <stdio.h>
#define MAX 1000
#define BROJ_DOMACIH 5

int main(void)
{
    int n, poeni[MAX - 1];                      // 1)
    scanf("%d", &n);
    n = n * BROJ_DOMACIH;                       // Broj elemenata niza (za svakog studenta *broj domacih)
    if (n <= 0 || n > MAX)
    {
        return 1;
    }
    int el;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &el);
        if (el >= 0 && el <= 7)
        {
            poeni[i] = el;
        }
        else
        {
            return 1;
        }
    }
    for (int i = 0; i < n; i++)                 // 2)
    {
        if (i != n - 1)
        {
            printf("%d ", poeni[i]);
        }
        else
        {
            printf("%d\n", poeni[i]);
        }
    }
    int t;                                      // 3)
    int max_poeni[MAX];
    for (int i = 0; i < BROJ_DOMACIH; i++)
    {
        t = poeni[i];
        for (int j = i + BROJ_DOMACIH; j < n; j += BROJ_DOMACIH)
        {
            if (poeni[j] > t)
            {
                t = poeni[j];
            }
        }
        max_poeni[i] = t;
    }
    int min_poeni[MAX];                         // 4)
    for (int i = 0; i < BROJ_DOMACIH; i++)      
    {
        t = poeni[i];
        for (int j = i + BROJ_DOMACIH; j < n; j += BROJ_DOMACIH)
        {
            if (poeni[j] < t)
            {
                t = poeni[j];
            }
        }
        min_poeni[i] = t;
    }
    for (int i = 0; i < BROJ_DOMACIH; i++)      // 5)
    {
        if (i != BROJ_DOMACIH - 1)
        {
            printf("%d ", max_poeni[i]);
        }
        else
        {
            printf("%d\n", max_poeni[i]);
        }
    }
    for (int i = 0; i < BROJ_DOMACIH; i++)                      
    {
        if (i != BROJ_DOMACIH - 1)
        {
            printf("%d ", min_poeni[i]);
        }
        else
        {
            printf("%d\n", min_poeni[i]);
        }
    }
    return 0;
}
