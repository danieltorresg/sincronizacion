#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

/* start_routine header */
void* contadorFuncion(void *);

/* Global variables */
int max;
pthread_mutex_t lock;

/* Initializing conter */
int contador = 0;

int main(int argc, char *argv[]) { 

    /* get the command's line parameters */
    if (argc != 3){
        printf("Ingrese únicamente los dos parametros: Maximo contador y numero de hilos.\n");
    }
    else {
        /* Declaration of struct timeval variables */
        struct timeval ti, tf;
        double tiempo;

        /* get the command's line parameters */
        max = atoi(argv[1]);
        if (max <= 10000000){

            /* get the command's line parameters */
            int hilos = atoi(argv[2]);

            /* Threads handlers */
            pthread_t hilosArray[hilos - 1];
            
            /* Time starts counting */
            gettimeofday(&ti, NULL);
            for (int i = 0; i < hilos; i++)
            {
                /* Thread creation */
                pthread_create(&hilosArray[i], NULL, &contadorFuncion, NULL);
            }
            for (int i = 0; i < hilos; i++)
            {
                /* Threads joins */
                pthread_join(hilosArray[i], NULL);
            }
            /* get the end time */
            gettimeofday(&tf, NULL);

            /* get the elapset time (end_time - start_time) */
            tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
            
            /* print the results (number threads employed, counter value, elasep time) */
            printf("Valor de contador: %d\nHas tardado: %g milisegundos\n", contador, tiempo);
        }
        else {
            printf("El valor maximo del contador es 10000000\n");
        }
    }
    return 0;
}

/* start_routine definition */
void* contadorFuncion(void * nada){
    for (int i = 0; i < max; i++){
        pthread_mutex_lock(&lock);
        contador ++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}