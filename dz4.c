/*
    Napisati program na programskom jeziku C koji raspoređuje novinske članke i reklame. Program najpre treba da sa standardnog ulaza pročita novinske članke i reklame. Svaki novinski članak je predstavljen realnim brojem u opsegu (0, 1], koji predstavlja procenat prostora koji dati članak zauzima na stranici, i njegovim nazivom (string nepoznate dužine). Svaka reklama je predstavljena samo nazivom (string nepoznate dužine). Novinski članci i reklame su zadati u zasebnim redovima. Najpre se čitaju novinski članci, a potom reklame. Sekcije su razdvojene praznim redom, a kraj unosa je takođe označen praznim redom. Nakon čitanja, program treba da formira novinske stranice tako da se na stranicu uvek dodaje najveći članak koji može da stane, sve dok ima odgovarajućih članaka koji nisu raspoređeni, a zatim prostor dopunjava jednom od neraspoređenih reklama. Ukoliko više novinskih članaka zadovoljava navedeni uslov, dodavati ih po redosledu pojavljivanja na standardnom ulazu. Novu stranicu formirati kada postojeća ne može da se dopuni preostalim člancima. Ukoliko nije unet dovoljan broj reklama, na stranicama dodati generičku poruku. Na kraju rada programa, neophodno je ispisati formirane stranice i neraspoređene reklame. Ukoliko je procentualni udeo stranice koji članak zauzima van navedenog opsega potrebno je ispisati poruku ERROR i korektno završiti program. 
    
    Program napisati prema sledećim stavkama.

    1. Implementirati funkciju koja formira jednostruko ulančanu listu novinskih članaka. Funkcija treba da elemente ulančava u listu u poretku učitavanja.  

    2. Implementirati funkciju koja formira jednostruko ulančanu listu reklama. Funkcija treba da elemente ulančava u listu u poretku učitavanja.  

    3. Implementirati funkciju koja formira i ispisuje stranice novina. 

    4. Implementirati funkciju koja oslobađa svu zauzetu dinamičku memoriju. 
    
    5. Napisati glavni program koji korišćenjem prethodno realizovanih funkcija pročita podatke o novinskim člancima i reklamama, izvrši traženu obradu i ispiše rezultat prema traženom formatu. Na kraju, program dealocira svu korišćenu dinamičku memoriju. 
*/

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
    Article *articles = readArticles();
    Advertisement *advertisements = readAdvertisements();
    writePages(articles, advertisements);
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
            printf("ERROR");
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
    int pageCount = 0;
    float pageSpace = 1;
    while (1) 
    {
        float previous = 0;
        Article *max = NULL;
        for (Article *tmp = articles; tmp != NULL; tmp = tmp->next)
        {
            if (tmp->percentage < pageSpace && tmp->percentage > previous)
            {
                previous = tmp->percentage;
                max = tmp;
            }
        }
        if (pageSpace == 1)
        {
            printf("PAGE %d\n", pageCount);
        }
        printf("ARTICLE:%s", max->article);
        pageSpace -= max->percentage;
        if (articles == max)
        {
            articles = max->next;
            free(max);
        }
        else
        {
            Article *current;
            for (Article *tmp = articles; tmp->next != max->next; tmp = tmp->next)
            {
                current = tmp;
            }
            current->next = max->next;
            free(max);
        }
        if (articles == NULL)
        {
            if (advertisements != NULL)
            {
                printf("ADVERTISEMENT: %s", advertisements->advertisement);
                Advertisement *tmp = advertisements;
                advertisements = tmp->next;
                free(tmp);
            }
            else
            {
                printf("<ADVERTISEMENT_PLACEHOLDER>");
            }
            break;
        }
        float min = articles->percentage;
        for (Article *tmp = articles; tmp != NULL; tmp = tmp->next)
        {
            if (tmp->percentage < min)
            {
                min = tmp->percentage;
            }
        }
        if (min >= pageSpace)
        {
            pageSpace = 1;
            pageCount++;
            if (advertisements != NULL)
            {
                printf("ADVERTISEMENT: %s", advertisements->advertisement);
                Advertisement *tmp = advertisements;
                advertisements = tmp->next;
                free(tmp);
            }
            else
            {
                printf("<ADVERTISEMENT_PLACEHOLDER>");
            }
        }
    }
    if (advertisements != NULL)
    {
        printf("UNUSED ADVERTISEMENT\n");
        for (Advertisement *tmp = advertisements; tmp != NULL; tmp = tmp->next)
        {
            if (tmp->next != NULL)
            {
                printf("%s", tmp->advertisement);
            }
            else
            {
                int i = 0;
                while (tmp->advertisement[i] != '\n')
                {
                    putchar(tmp->advertisement[i++]);
                }
            }
        }
    }
    else
    {
        printf("UNUSED ADVERTISEMENT");
    }
}
