## Daniel Torres González - 1020492000
## Daniel Santa Rendón - 1040050021
# Listas enlazadas concurrentes #

## Antes de empezar ## 

Se recomienda que lea, entienda y codifique el código de las listas enlazadas concurrentes (sección [Lock-based Concurrent Data Structures](http://pages.cs.wisc.edu/~remzi/OSTEP/threads-locks-usage.pdf) del texto guía). Luego, lea el problema y, a partir de lo que se solicita, empiece a modificar el código ejemplo del libro.

## Aplicación - biblioteca ##

La empresa **ACME**, en la cual usted labora, ha ganado una licitación para el desarrollo de un software para la gestión de material bibliográfico en una biblioteca. 

![biblioteca](biblioteca.jpg)

En el momento se encuentran haciendo las pruebas de la funcionalidad de préstamo de libros. La idea es permitir que hayan 4 puestos de atención de préstamo de material que funcionen de manera simultánea sin que los datos de información del inventario se corrompan. 

La información que se va a almacenar por cada libro será:
1. **id**: Identificador del libro.
2. **name**: Nombre del libro.
3. **num_pages**: Número de páginas del libro.
4. **pub_year**: Año de publicación.

Se le ha encomendado a usted que desarrolle un programa que **simule** el funcionamiento concurrente de los préstamos de 
la biblioteca. Para la prueba se deben llevar a cabo las siguientes etapas:

1. **Inicialización de la lista con la información de los libros**: Para las pruebas se crea una lista de 10000 libros en la cual los campos **num_pages** y **pub_year** serán los mismos (por ejemplo 100 y "2020"); sin embargo, **id** (entre "0" y "9999") y el **name** (desde "book_0" hasta "book_999") van a variar. 
2. **Simulación de los prestamos**: Para el préstamo se van a simular 4 oficinas de atención. Cada una de las cuales podrá acceder a la lista de libros creada en la etapa 1; sin embargo, solo se van a manejar 1000 préstamos por oficina. Para tal fin, cada vez que se vaya a simular un préstamo se genera un número aleatorio para el **id** del libro (para lo cual se recomienda que usar el generador de números aleatorios de C y no olvide inicializar la semilla aleatoria cada estación de préstamo). Si el **id** generado está disponible dentro de la lista de libros, se procede a realizar el préstamo y se actualiza la lista, si no el libro no se encuentra dentro de la lista, significa que el ejemplar ya fue prestado. En todo caso, la oficina deberá llevar un registro de cuántos préstamos fueron exitosos y cuántos fallaron (para propósitos de test) y mostrarlo en pantalla al finalizar su ejecución.
3. **Despligue de resultados**: Finalmente, el programa deberá desplegar, el número total de préstamos realizados con éxito, el número total de préstamos que fallaron y el número de libros disponibles.
4. **Medición del tiempo de ejecución de la aplicación**: Un vez ya se encuentre todo lo anterior listo proceda a medir el tiempo llevado a cabo para los préstamos.

A continucación se muestra un posible ejemplo de una salida en la cual se tiene la ejecución de una simulación:

```
Initializing list of available books
my id 0, my seed 2058611624 
my id 1, my seed 1662376139 
my id 2, my seed 235467922 
my id 3, my seed 788003183 
Office 2 has finished its workload, successful loans 866, failed loans 134
Office 0 has finished its workload, successful loans 790, failed loans 210
Office 3 has finished its workload, successful loans 887, failed loans 113
Office 1 has finished its workload, successful loans 759, failed loans 241
Simulation done! execution time: 341.08 ms
Total successful loans 3302, total failed loans 698
Number of remaining available books 6698
```

**Recomendaciones importantes:**
- Desarrolle un hilo por que simule el funcionamiento de cada oficina de atención.
- No olvide verificar que la funciones de la librería estándar que utiliza en cada función hilo sean *Thread Safe*.
- Tenga en cuenta que en la implementación pueden ocurrir varias condiciones de carrera (*race conditions*), implemente los mecanimos de sincronización adecuados para garantizar que la simulación siempre se ejecute de manera correta.

 





