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


**Descripcion de las técnicas de indexación de archivos**


El metodo de organizacion de archivos en Isam consiste en inserción, eliminación y búsqueda
El metodo de insercion es
El metodo de eliminacion es
El metodo de busqueda es

El metodo de organizacion de archivos en Extendible hashing consiste en inserción, eliminación y búsqueda
El metodo de insercion es
El metodo de eliminacion es
El metodo de busqueda es

**Descripcion de la simulación de transacciones**

Y el uso de hilos

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
