#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include "conuter.h"

#define THRESHOLD 1024

/* structs */
// code here (if you required it)...

/* start_routine header */
void *contadorFuncion(void *c);

/* Global variables */
int max = 0;
int hilo = 0;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Recuerde ingresar los dos parametros (Maximo contador y numero de hilos).\n");
    }
    else
    {

        /* Declaration of struct timeval variables */
        struct timeval ti, tf;
        double tiempo;
        counter_t c;
        init(&c, THRESHOLD);

        /* get the command's line parameters */
        max = atoi(argv[1]);
        if (max <= 10000000)
        {
            /* get the command's line parameters */
            int hilos = atoi(argv[2]);

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
void *contadorFuncion(void *c)
{

    while (get(c) < max)
    {
        update(c, hilo, 1);    
    }
    
    return NULL;
}