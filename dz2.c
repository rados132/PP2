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
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j != n - 1)
            {
                printf("%d ", matrica[i][j]);
            }
            else
            {
                printf("%d", matrica[i][j]);
            }
        }
        if (i != m - 1)
        {
            putchar('\n');
        }
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
            if (j != pozicija[1] + k - 1)
            {
                printf("%d ", matrica[i][j]);
            }
            else
            {
                printf("%d", matrica[i][j]);
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
