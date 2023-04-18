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
    int **matrica = malloc(m * sizeof(int *));
    if (matrica == NULL)
    {
        printf("GRESKA");
        return 0;
    }
    for (int i = 0; i < m; i++)
    {
        matrica[i] = malloc(n * sizeof(int));
        if (matrica[i] == NULL)
        {
            printf("GRESKA");
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
            if (j != n - 1)
            {
                printf("%d ", matrica[i][j]);
            }
            else
            {
                printf("%d\n", matrica[i][j]);
            }
        }
    }
    for (int i = 0; i < m; i++)
    {
        free(matrica[i]);
    }
    free(matrica);
    return 0;
}
