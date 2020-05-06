#include <stdio.h>
#include <sys/time.h>

int main()
{

    struct timeval ti, tf;
    double tiempo;

    gettimeofday(&ti, NULL);
    gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec) * 1000 + (tf.tv_usec - ti.tv_usec) / 1000.0;
    printf("Has tardado: %g milisegundos\n", tiempo);
}