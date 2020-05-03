#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include "list.h"

/* struct _count
{
    int good;
    int bad;
};

typedef struct _count Count; */

void initLibrary();
void *loanBooks();
int loanableBooks(list_t *L);

int t_rejected = 0;
int t_acepted = 0;
pthread_mutex_t lock;
list_t *list;

int main()
{
    clock_t start_t = clock();
    clock_t end_t;
    double total_t = 0;
    pthread_t threads[4];
    List_Init(&list);
    printf("Initializing list of available books \n");
    initLibrary();
    for (int i = 0; i < 4; i++)
    {
        pthread_create(&threads[i], NULL, &loanBooks, (void *) (intptr_t) i);
    }

    for (int i = 0; i < 4; i++)
    {

        pthread_join(threads[i], NULL);
    }
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("Simulation done! execution time: %f seconds\n", total_t);
    printf("Total successful loans %d, total failed loans %d \n", t_acepted, t_rejected);
    int available = loanableBooks(&list);
    printf("Number of remaining available books %d \n", available);

    return 0;
}

void initLibrary()
{
    for (int i = 0; i < 10000; i++)
    {

        Book *book = (Book *)malloc(sizeof(Book));
        book->id = i;
        snprintf(book->name, 10, "Book_%d", i);
        book->num_pages = 100;
        book->pub_year = 2020;
        book->loanable = 1;
        book->next = NULL;
        List_Insert(&list, book);
    }
}

void *loanBooks(void *param)
{
    int id = (intptr_t)param;
    long thread_id = (long)pthread_self();
    printf("my id %d, my seed %ld \n", id, thread_id);
    srand((unsigned)thread_id);
    int acepted = 0, rejected = 0;
    for (int i = 0; i < 1000; i++)
    {
        int random = rand() % 10000;
        //
        int loan = update_loanable(&list, random);
        if (loan == 1)
        {
            acepted++;
        }
        else
        {
            rejected++;
        }
    }
    printf("Office %d has finished its workload, successful loans %d, failed loans %d\n", id, acepted, rejected);
    pthread_mutex_lock(&lock);
    t_rejected += rejected;
    t_acepted += acepted;
    pthread_mutex_unlock(&lock);
    return 0;
}

int loanableBooks(list_t *L)
{
    int elements = 0;
    pthread_mutex_lock(&L->lock);
    Book *curr = L->head;
    while (curr)
    {
        if (curr->loanable == 1)
        {
            elements++;
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&L->lock);
    return elements;
}