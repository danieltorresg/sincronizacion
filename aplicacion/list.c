#include "list.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define NULL 0

void List_Init(list_t *L)
{
    L->head = NULL;
    pthread_mutex_init(&L->lock, NULL);
}

void List_Insert(list_t *L, Book *book)
{
    // synchronization not needed
    Book *new = (Book *)malloc(sizeof(Book));

    if (new == NULL)
    {
        perror("malloc");
        return;
    }
    new->id = book->id;
    snprintf(book->name, 10, "Book_%d", book->id);
    new->num_pages = book->num_pages;
    new->loanable = book->loanable;
    new->pub_year = book->pub_year;
    // just lock critical section
    pthread_mutex_lock(&L->lock);
    new->next = L->head;
    L->head = new;
    pthread_mutex_unlock(&L->lock);
}

int List_Lookup(list_t *L, int book)
{
    int rv = -1;
    pthread_mutex_lock(&L->lock);
    Book *curr = L->head;
    while (curr)
    {
        //printf("Este es el recorrido %d",curr->id);
        if (curr->id == book)
        {
            rv = 0;
            printf("El estado es: %d\n", curr->loanable);
            break;
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&L->lock);
    return rv; // now both success and failure
}

int update_loanable(list_t *L, int id)
{
    int aux = 0;
    pthread_mutex_lock(&L->lock);
    Book *curr = L->head;
    while (curr)
    {
        if (curr->id == id && curr->loanable == 1)
        {
            curr->loanable = 0;
            aux = 1;
            break;
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&L->lock);
    return aux;
}