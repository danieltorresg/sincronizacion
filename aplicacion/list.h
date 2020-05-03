#include <pthread.h>

typedef struct __book{
    int id;
    char name[10];
    int num_pages;
    int pub_year;
    int loanable;
    struct __book *next;
    
}Book;

typedef struct __list_t {
    Book *head;
    pthread_mutex_t lock;
} list_t;

int update_loanable(list_t *L, int id);
void List_Init(list_t *L);
int List_Lookup(list_t *L, int key);
void List_Insert(list_t *L, Book *key);