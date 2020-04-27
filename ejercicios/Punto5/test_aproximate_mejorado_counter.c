#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "counter.h"

/* start_routine header */
void* contadorFuncion(void *c);

/* Global variables */
int hilo = 0;
int max, hilos, THRESHOLD;

int main(int argc, char *argv[])
{

    /* get the command's line parameters */
    if (argc != 4)
    {
        printf("Recuerde ingresar todos parametros (Umbral, Maximo contador y numero de hilos).\n");
    }
    else
    {
        /* Declaration of struct timeval variables */
        struct timeval ti, tf;
        double tiempo;
        counter_t c;

        /* get the command's line parameters */
        THRESHOLD = atoi(argv[1]);

        /* Initializing conter */
        init(&c, THRESHOLD);

        /* get the command's line parameters */
        max = atoi(argv[2]);
        if (max <= 10000000)
        {
            /* get the command's line parameters */
            hilos = atoi(argv[3]);

            /* Threads handlers */
            pthread_t hilosArray[hilos - 1];

            /* Time starts counting */
            gettimeofday(&ti, NULL);
            for (int i = 0; i < hilos; i++)
            {
                /* Thread creation */
                pthread_create(&hilosArray[i], NULL, &contadorFuncion, &c);
                hilo++;
            }
            for (int i = 0; i < hilos; i++)
            {
                /* Threads joins */
                pthread_join(hilosArray[i], NULL);
            }
            /* get the end time */
            gettimeofday(&tf, NULL);

            /* get the elapset time (end_time - start_time) */
            tiempo = (tf.tv_sec - ti.tv_sec) * 1000 + (tf.tv_usec - ti.tv_usec) / 1000.0;

            /* print the results (number threads employed, counter value, elasep time) */
            printf("Has tardado: %g milisegundos\n",  tiempo);
            printf("El contador es: %d\n", get(&c));
        }
        else
        {
            printf("El valor maximo del contador es 10000000\n");
        }
    }
    return 0;
}

/* start_routine definition */
void* contadorFuncion(void *c){
    int value = get(c);
    while (value < max){
        update(c, hilo, 1);
        value = get(c);
    }
    return NULL;
}