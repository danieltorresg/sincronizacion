## Daniel Torres González - 1020492000
## Daniel Santa Rendón - 1040050021
# Manejo de estructuras que usan locks #

## Fuentes de consulta ##
1. Material de clase (Videos y diapostivas).
2. Texto guía [**Operating Systems: Three Easy Pieces**](http://pages.cs.wisc.edu/~remzi/OSTEP/). Para desarrollar este laboratorio se recomienda tener a la mano el capítulo [Lock-based Concurrent Data Structures](http://pages.cs.wisc.edu/~remzi/OSTEP/threads-locks-usage.pdf)

## Ejercicios ##

1. Consulte el uso de la función ```gettimeofday``` para medir el tiempo de ejecución de un programa
   * ¿Cómo se utiliza esta función (muestre un ejemplo)? 
   **R//:** El archivo ejemplo se llama EjemploPunto1
   * ¿Cuál es el intervalo de tiempo más corto que se puede medir con esta función?
   **R//:** Después de hacer varias pruebas, el tiempo mínimo calculado por la función fue 0.001 milisegundos, auqnue a veces quedaba en 0.
2. Consulte cuantas CPUs hay disponibles en el sistema que usted está utilizando. (Pista use el comando lscpu)
2. Desarrolle un programa que utilice un contador concurrente simple. Mida cuánto tiempo lleva incrementar el contador muchas veces a medida que aumenta el número de hilos (1, 2, 4, 8 y 16). Para tal fin, siga las instrucciones que aparecen en el directorio [preciso](./preciso). Una vez complete los pasos continue con el tercer punto.
3. Desarrolle una versión del contador aproximado (*sloppy counter*) y mida su desempeño a medida que se varía el número de hilos. En este caso, solo maneje un umbral de S = 1024 variando el número de hilos (1, 2, 4, 8 y 16). Las intrucciones para ello se encuentran en el directorio [aproximado](./aproximado).
4. Grafique los resultados obtenidos de las pruebas recopiladas (en las tablas) para el **número de hilos .vs. el tiempo (en segundos)**, estas siguen la tendencia de la figura **29.5** del libro (la cual se muestra a continuación):

![fig_performance](fig_performance.jpg)

   * ¿Los valores que usted obtuvo siguen una tendencia como la que se muestra en el texto guía (mostrada anteriormente)?
   * ¿Cuántas CPUs hay disponibles en el sistema que usted está utilizando?  
   * ¿Este número afecta de alguna manera sus mediciones?

5. Mejore el archivo [test_aproximate_mejorado_counter.c](./aproximado_mejorado/test_aproximate_mejorado_counter.c) (el cual se encuentra en el directorio [aproximado_mejorado](./aproximado_mejorado)) de tal modo que, además de permitir modificar el numero de hilos y el valor máximo del contador a emplear, permita modificar también el umbral o factor de apromación (S), para esto se puede basar en el ejercicio 3. De este modo los parametros serán:
   * Umbral: ```APPROXIMATION_FACTOR```
   * Valor máximo del contador: ```MAXCNT```
   * Número de hilos que serán lanzados: ```NUMTHREADS```
   
Según lo anterior, la forma de pasar argumentos a la aplicación será la siguiente, una vez esté completamente terminada:  

```
./NOMBRE_EJECUTABLE <APPROXIMATION_FACTOR> <MAXCNT> <NUMTHREADS>
```

Luego, ejecute varias veces la aplicación dejando constante el valor máximo del contador en 10000000 y el número de hilos en 4, pero cambiando el valor del umbral a los siguientes valores: 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 y 1024. ¿La gráfica sigue una tendencia similar a la mostrada en la figura **29.6** del texto guía (la cual se muestra a continuación)?

![fig_S](fig_S.jpg)
