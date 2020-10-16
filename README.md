# Organización de Archivos y Control de Concurrencia

## Integrantes

| Nombre y Apellidos |
|---|
|Diego Enciso Lozano |
|Luis Jauregui Vera	 |
|Jonathan Hoyos      |


## Tabla de contenido
<details>
<summary>"Clic para navegar: "</summary>

- [Introducción](#Introducción)
- [Fundamentos y descripción de las técnicas](#Fundamentos-y-descripción-de-las-técnicas)
- [Resultados experimentales](#Resultados-experimentales)
- [Pruebas de uso y presentación](#Pruebas-de-uso-y-presentación)

</details>

## Introducción

El objetivo de este proyecto es implementar 2 técnicas de organización de archivos físicos en memoria secundaria: **Sequential File** y **Extendible Hashing**.
Para ello, se tiene en cuenta el manejo de acceso concurrente. Además, se hace énfasis en el análisis
de la complejidad de tiempo en cada técnica u algoritmo utilizado

Los datos que son utilizados en este proyecto son 2 colecciones de datos las cuales contienen:
a. Registros de ventas en diferentes regiones y países del mundo.
b. Registros de un programa de seguro médico social en Estados Unidos.

Este informe cuenta con las comparaciones de los tiempos de ejecución de los procesos de **Inserción**, **Búsqueda** y **Eliminación**. Además, se toma en cuenta cada acceso a memoria secundaria.

## Fundamentos y descripción de las técnicas

### Sequential File

Esta técnica hace uso de dos archivos, uno para almacenar los datos, los cuales están 
ordenados de manera lógica por punteros en memoria secundaria y el otro para los 
nuevos registros a insertar, éste último funciona como un archivo temporal y también se encuentra ordenado por punteros en memoria secundaria. Los datos no necesariamente 
deben ser escritos en los archivos de manera ordenada, ya que con los punteros y el 
orden lógico se pueden realizar búsquedas binarias con una complejidad logarítmica.

##### Inserción
>Para esta operación, se localiza la posición lógica en la cual será insertado el registro y para ello, se hace uso de la búsqueda binaria. Además, se hace uso de 2 campos adicionales por registro, los cuales almacenarán las posiciones del siguiente y anterior registro. Esta operación puede llegar a realizar logn lecturas en memoria secundaria (n: cantidad de registros) para localizar la posición y para escribir en disco realiza 1 acceso. 
Complejidad: O(logn) + O(1)

##### Búsqueda
>Para esta operación, se implementó un recorrido binario a través del archivo, el cual retornará la posición en la que debe ser insertado un registro o también puede retornar un registro dado una llave de búsqueda. Este recorrido puede llegar a realizar logn accesos a memoria secundaria, siendo n: cantidad de registros. 
Complejidad: O(logn)

##### Eliminación
>Para esta operación, se recibe una posición específica del registro a eliminar. Para una implementación eficiente, se hace uso del segundo campo adicional mencionado en la operación de inserción. Esto tiene como finalidad, poder acceder al registro anterior con una complejidad constante y de esta manera actualizar los punteros que almacenan las posiciones del siguiente y anterior registro de manera eficiente. De lo contrario, se tendría que iterar hasta una posición anterior a la posición recibida como parámetro para poder actualizar los punteros. Esto, transforma logn accesos a 1 acceso para ubicar el registro previo.
Complejidad: O(1)

### Extendible Hashing

Usado en base de datos que varían tamaño a través del tiempo. La función hash genera una secuencia de bits, del cual solo se usa un sufijo o prefijo del binario para indexar los registros. Cada bucket tiene una profundidad local que indica cuantos bits se estáan tomando. Esta técnica evita que la base de datos se degrade con el tiempo y minimiza los casos de overflow. Por otro lado, el cambio de tamaño de buckets es una operación cara y no soporta búsquedas por rango.

##### Inserción
>

##### Búsqueda
>

##### Eliminación
>


### Simulacion de Transacciones

Las transacciones fueron simuladas en forma de funciones que realizaban un cierto número de operaciones de inserción y eliminacion utilizando un mismo tipo de técnica de organización y utilizando concurrencia se utilizaron hilos que realizaban estas funciones en simultáneo. Su funcionamiento correcto se comprobo invocándolas sobre un conjunto de archivos ya existentes para ver que se ejecutaran apropiadamente. Se manejo las transacciones con un formato de texto para observar el orden en el que ocurrieron cada una de las operaciones. Se esperaba obtener una planificación serializable al momento de llevar a cabo las transacciones.

## Resultados experimentales

Cuadros para ver el desempeño de las técnicas de indexación:

### Sequential File

    n: cantidad de registros
 ##### Total de accesos a disco duro (read & write)
 - Inserción
    **Al inicio:**  log n(r) + 1(w)
    **Al final :**  log n(r) + 1(w) + 2(r&w punteros del anterior registro)
    **Otra pos :**  log n(r) + 1(w) + 2(r&w punteros del anterior registro)

    | Mejor Caso |  Caso Promedio  |    Peor Caso    |
    |------------|-----------------|-----------------|
    |    O(1) 	 | O(log n) + O(1) | O(log n) + O(1) |

 - Búsqueda
    **Al inicio:**  log n(r)
    **Al final :**  log n(r)
    **Otra pos :**  log n(r)

    | Mejor Caso |  Caso Promedio  |    Peor Caso    |
    |------------|-----------------|-----------------|
    |    O(1) 	 |    O(log n)     |    O(log n)     |

- Eliminación
    **Al inicio:**  2(r&w) + 2(r&w header freelist)
    **Al final :**  2(r&w) + 2(r&w punteros del anterior registro)
    **Otra pos :**  2(r&w) + 2(r&w punteros del anterior registro) + 2(r&w punteros del siguiente registro)

    | Mejor Caso |  Caso Promedio  |    Peor Caso    |
    |------------|-----------------|-----------------|
    |    O(1) 	 |       O(1)      |       O(1)      |


 ##### Tiempos de ejecución

- Tiempos de cada test

    | Test   | Input  	 |  Tiempo (ms) |
    |------  |--------   |--------------|
    |  1     | 100       | 0.00001 	    |
    |  2     | 500 	     | 0.00018 		|
    |  3     | 1000 	 | 0.00075 		|
    |  4     | 5000 	 | 0.02192 		|
    |  5     | 10000 	 | 0.08931 		|

### Extendible Hashing 

 ##### Total de accesos a disco duro (read & write)
 - Inserción

 - Búsqueda

- Eliminación

 ##### Tiempos de ejecución

- Tiempos de cada test

**Discusión y Análisis**
En Sequential File se puede observar que el caso promedio para la inserción y búsqueda es O(log n), siendo n la cantidad de registros a iterar, mientras que para la eliminación el caso promedio es constante O(1).


## Pruebas de uso y presentación
Link del video de funcionalidad.[ Video de funcionalidad](https://drive.google.com/drive/folders/1Ktgyf7EzZLjxL8LYm-349A9HuZRKPcGi?usp=sharing)
