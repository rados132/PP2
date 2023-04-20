/*
    Napisati program koji pronalazi i ispisuje kvadratnu podmatricu dimenzija k x k čija je suma elemenata najveća. Ukoliko postoji više takvih podmatrica, potrebno je izabrati onu čiji je par koordinata (vrsta, kolona) gornjeg levog elementa najmanji (parovi se porede tako što se najpre porede vrste, a ako su one jednake, onda kolone). Nije potrebno izdvajati podmatricu u novu matricu kopiranjem elemenata podmatrice.

    Program treba da:

    1)   Učita dimenzije matrice, a zatim u novom redu i matricu celih brojeva. Matrica može biti zadata u više redova.

    2)   Ispiše učitanu matricu. Svaka vrsta matrice treba da bude ispisana u zasebnom redu. Svaki element treba da bude razdvojen tačno jednim blanko znakom.

    3)   Učita dimenziju k kvadratne podmatrice. Ukoliko vrednost k nije u opsegu (0, min(m, n)], gde su m i n dimenzije originalne matrice, treba korektno završiti program.

    4)   Pronađe kvadratnu podmatricu dimenzija k x k originalne matrice, čija je suma elemenata najveća.

    5)   Ispiše podmatricu prema formatu navedenom u stavki 2.
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int m, n;
    scanf("%d%d", &m, &n);
    if (m <= 0 || n <= 0)
    {
        return 0;
    }
    int **matrica = calloc(m, sizeof(int *));
    if (matrica == NULL)
    {
        printf("MEM_GRESKA");
        return 0;
    }
    for (int i = 0; i < m; i++)
    {
        matrica[i] = calloc(n, sizeof(int));
        if (matrica[i] == NULL)
        {   
            for (int j = 0; j < i; j++)
            {
                free(matrica[j]);
            }
            free(matrica);
            printf("MEM_GRESKA");
            return 0;
        }
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &matrica[i][j]);
        }
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d", matrica[i][j]);
            if (j != n - 1)
            {
                putchar(' ');
            }
        }
        if (i != m - 1)
        {
            putchar('\n');
        }
    }
    int k;
    scanf("%d", &k);
    if (k <= 0 || k > m || k > n )
    {
        for (int i = 0; i < m; i++)
        {
            free(matrica[i]);
        }
        free(matrica);
        return 0;
    }
    int s, max_suma = 0, pozicija[] = {0, 0};
    for (int i = 0; i <= m - k; i++)
    {
        for (int j = 0; j <= n - k; j++)
        {
            s = 0;
            for (int p = 0; p < k; p++)
            {
                for (int q = 0; q < k; q++)
                {
                    s += matrica[i + p][j + q];
                }
            }
            if (s > max_suma)   
            {
                max_suma = s;
                pozicija[0] = i;
                pozicija[1] = j;
            }
        }  
    }
    putchar('\n');
    for (int i = pozicija[0]; i < pozicija[0] + k; i++)
    {
        for (int j = pozicija[1]; j < pozicija[1] + k; j++)
        {
            printf("%d", matrica[i][j]);
            if (j != pozicija[1] + k - 1)
            {
                putchar(' ');
            }
        }
        if (i != pozicija[0] + k - 1)
        {
            putchar('\n');
        }
    }   
    for (int i = 0; i < m; i++)
    {
        free(matrica[i]);
    }
    free(matrica);
    return 0;
}
