[#](#) Organización de Archivos y Control de Concurrencia

## Tabla de contenidos
<details>
<summary>"Clic para navegar: "</summary>

- [Introduccion](#Introduccion)
- [Fundamente y describa las tecnicas](#Fundamente-y-describa-las-tecnicas)
- [Resultados Experimentales](#Resultados-Experimentales)
- [Pruebas de uso y presentación](#Pruebas-de-uso-y-presentación)

</details>

## Introduccion

El objetivo de nuestro proyecto es entender la organización de archivos físico y el manejo de acceso concurrente, y aplicar técnicas de almacenamiento de archivos en Memoria Secundaria.

Los datos que se usaran en este Proyecto serán de Una Base de datos de transacciones de Materias primas. Y nuestro segundo archivo será Una Base de datos de usuarios de un programa de seguro medico social en Estados Unidos.

Se esperará poder visualizar los tiempos de ejecucion de las funciones de Insertar, Buscar y Eliminar acceder a memoria secundaria de acuerdo a cada algoritmo de organizacion de archivos.
## Fundamente y describa las tecnicas


##### Sequential File

El metodo de organizacion de archivos en Isam consiste en inserción, eliminación y búsqueda
El metodo de insercion es
El metodo de eliminacion es
El metodo de busqueda es

##### Extendible Hashing

Usado en base de datos que varían tamaño a través del tiempo. La función hash genera una secuencia de bits, del cual solo se usa un sufijo o prefijo del binario para indexar los registros. Cada bucket tiene una profundidad local que indica cuantos bits se estáan tomando. Esta técnica evita que la base de datos se degrade con el tiempo y minimiza los casos de overflow. Por otro lado, el cambio de tamaño de buckets es una operación cara y no soporta búsquedas por rango.

### Manejo de memoria secundaria

El manejo de la memoria secundaria se puede ver en los buckets en forma de archivo que se guardan en el disco duro al momento de correr el programa. Para la creacion de un objeto que va a realizar cada una de las tecnicas de organizacion es necesario que leamos el archivo que se encuentra en memoria secundaria. . La creación de buckets y su guardado tambien se realiza en memoria secundaria, por lo cual hay carpetas designadas para cada uno de estos. Como prueba del software funcionando apropiadamente, vemos la generacion de nuevos archivos en cada uno de las carpetas designadas.

### Simulacion de Transacciones

Las transacciones fueron simuladas en forma de funciones que realizaban un cierto número de operaciones de inserción y eliminacion utilizando un mismo tipo de técnica de organización y utilizando concurrencia se utilizaron hilos que realizaban estas funciones en simultáneo. Su funcionamiento correcto se comprobo invocándolas sobre un conjunto de archivos ya existentes para ver que se ejecutaran apropiadamente. Se manejo las transacciones con un formato de texto para observar el orden en el que ocurrieron cada una de las operaciones. Se esperaba obtener una planificación serializable al momento de llevar a cabo las transacciones.

## Resultados Experimentales

##Cuadros para ver el desempeño de las tecnicas de Indexacion

### Sequential file

|        	| Insertar 	| Busqueda 	|
|--------	|----------	|----------	|
| 1,000  	|          	|          	|
| 100000 	|          	|          	|
| 100000 	|          	|          	|

    (a) Total de accesos a disco duro(Read + write) Vs. Numeros de tuplas


|        	| Insertar 	| Busqueda 	|
|--------	|----------	|----------	|
| 1,000  	|          	|          	|
| 100000 	|          	|          	|
| 100000 	|          	|          	|

    (a) Tiempo de ejecucion(ml) Vs. Numeros de tuplas

### Hashing Extendible

|        	| Insertar 	| Busqueda 	|
|--------	|----------	|----------	|
| 1,000  	|          	|          	|
| 100000 	|          	|          	|
| 100000 	|          	|          	|

    (a) Total de accesos a disco duro(Read + write) Vs. Numeros de tuplas


|        	| Insertar 	| Busqueda 	|
|--------	|----------	|----------	|
| 1,000  	|          	|          	|
| 100000 	|          	|          	|
| 100000 	|          	|          	|

    (a) Tiempo de ejecucion(ml) Vs. Numeros de tuplas


**Discusión y Análisis**
Vemos por las graficas que en cantidad de accesos el .

También vemos que el que tiene menor cantidad de accesos a disco es .


## Pruebas de uso y presentación

Estos son los screenshots que obtenemos por el uso de nuestra aplicacion:


Este es el link del drive donde esta el video explicado[ Video de funcionalidad](drive.google.com)
