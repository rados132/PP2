#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
 
typedef struct article
{
    float percentage;
    char article[MAX];
    struct article *next;
}
Article;

typedef struct advertisement
{
    char advertisement[MAX];
    struct advertisement *next;
}
Advertisement;

Article* readArticles();
Advertisement* readAdvertisements();
void freeArticles(Article *head);
void freeAdvertisements(Advertisement *head);
void writePages(Article *articles, Advertisement *advertisements);

int main(void)
{
    //stdin = fopen("input.txt", "r");

    Article *articles;
    Advertisement *advertisements;
    articles = readArticles();
    advertisements = readAdvertisements();

    for (Article *tmp = articles; tmp != NULL; tmp = tmp->next)
    {
        printf("%.2f %s", tmp->percentage, tmp->article);
    }

    for (Advertisement *tmp = advertisements; tmp != NULL; tmp = tmp->next)
    {
        printf("%s", tmp->advertisement);
    }

    writePages(articles, advertisements);

    freeArticles(articles);
    freeAdvertisements(advertisements);
    return 0;
}

void freeArticles(Article *head)
{
    Article *current;
    while (head != NULL)
    {
        current = head;
        head = current->next;
        free(current);
    }
}

void freeAdvertisements(Advertisement *head)
{
    Advertisement *current;
    while (head != NULL)
    {
        current = head;
        head = current->next;
        free(current);
    }
}

Article* readArticles()
{
    Article *head = NULL, *current = NULL, *tmp = NULL;
    float percentage;
    int i = 0;
    while (scanf("%f", &percentage))
    {
        if (percentage <= 0 || percentage > 1)
        {
            freeArticles(head);
            exit(0);
        }
        if ((i++) == 0)
        {
            head = malloc(sizeof(Article));
            if (head == NULL)
            {
                printf("MEM_GRESKA");
                exit(0);
            }
            current = head;
            current->next = NULL;
            current->percentage = percentage;
            fgets(current->article, MAX, stdin);
        }
        else
        {
            tmp = malloc(sizeof(Article));
            if (tmp == NULL)
            {
                printf("MEM_GRESKA");
                exit(0);
            }
            tmp->next = NULL;
            current->next = tmp;
            current = tmp;
            current->percentage = percentage;
            fgets(current->article, MAX, stdin);
        }
    }
    return head;
}

Advertisement* readAdvertisements()
{
    Advertisement *head = NULL, *current = NULL, *tmp = NULL;
    char buffer[MAX];
    int i = 0;
    while (1)
    {
        if ((i++) == 0)
        {
            head = malloc(sizeof(Advertisement));
            if (head == NULL)
            {
                printf("MEM_GRESKA");
                exit(0);
            }
            current = head;
            current->next = NULL;
            if (fgets(buffer, MAX, stdin) == NULL)
            {
                break;
            }
            if (buffer[0] == '\n')
            {
                break;
            }
            strcpy(current->advertisement, buffer);
        }
        else
        {
            if (fgets(buffer, MAX, stdin) == NULL)
            {
                break;
            }
            if (buffer[0] == '\n')
            {
                break;
            }
            tmp = malloc(sizeof(Advertisement));
            if (tmp == NULL)
            {
                printf("MEM_GRESKA");
                exit(0);
            }
            tmp->next = NULL;
            current->next = tmp;
            current = tmp;
            strcpy(current->advertisement, buffer);
        }
    }
    return head;
}

void writePages(Article *articles, Advertisement *advertisements)
{
    int i = 0;
    while ((i++) == 0)
    {
        int pageCount = 0, pageSpace = 1;
        float previous = 0;
        Article *max = NULL;
        for (Article *tmp = articles; tmp != NULL; tmp = tmp->next)
        {
            if (tmp->percentage > previous)
            {
                max = tmp;
            }
        }
        putchar('\n');
        printf("%f", max->percentage);
    }
}
