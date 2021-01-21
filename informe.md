## 	Aspectos teóricos
---

​	En el proceso de la creación de código, se utilizaron varias librerías que son estándar del Lenguaje C++. El cual, todas ellas tuvieron las funciones perfectas para la estructuración de datos, logrando así facilitar el proceso, manejo, gestión, mantenimiento durante la creación del código.

​	Entre ellas, podemos mencionar:

+ `<algorithm>`: Esta librería permite definir y proveer una colección de funciones comunes y diseñadas para el uso de un rango de elementos. Sean vectores o una instancia de contenedores, como lo son las listas, pilas, colas y mapas. Estos algoritmos operan mediante iteradores en los valores (excepto los algoritmos numéricos generalizados), dejando la estructura del rango de elementos intacto, sin afectar al tamaño o la asignación de datos. 
  	Múltiples funciones de esta librería son usadas para diversos propósitos. Como buscar un elemento, ordenarlos, manipular datos u otro mas. En este caso, se uso para implementar la función `find()` que permite buscar elementos dentro del contenedor.

+ `<Bitset>`: Define un tipo de dato llamado Bitset. Una forma especial de conjunto capaces de contener valores binarios que se denomina en un conjunto de bit. Esto quiere decir que esta representado mediante una secuencia de tamaño constante de N bits y contiene dos únicos valores: 0 (inactivo) y 1 (activo).

  ​	Gracias a esta librería, el acceso a todos los bits pueden ser de manera individual debido a que Bitset emula un vector.

+ `<list>`: Librería que genera una lista doblemente enlazada, es decir, que se puede acceder a sus datos de manera bidireccional en su estructura secuencial. Una lista es una secuencia de contenedores que permiten la manipulación de datos a un tiempo constante y una iteración de la lista en ambas direcciones.


+ `<utility>`: provee un tipo de dato estructurado llamado Par. El cual permite asignar dos tipos de datos diferentes en un emulador de vector de dos contendedores. Hay que definir quien sera el primer o el segundo elemento del para para acceder a uno de ambos datos.

+ `<cmath>`: La librería de cmath tiene una colección de funciones que computan operaciones y transformaciones matemáticas comunes. Entre ellas podemos mencionar las funciones trigonométricas, hiperbólicas, exponenciales, logarítmicas, potencias, etc. Gracias a esta librería, se pudo incluir la operación logarítmica con base 10 para que el programa pudiera funcionar.
	La formula para cambiar la base es:

$$
log(a) = log10(a) / log10(b)
$$

+ `<iomanip>`: Muy útil cuando se quiere obtener salida den un diseño estructurado y adecuado. Esto se debe a que iomanip tiene funciones utilizadas para manipular el ouput de un programa de C++

  

  ## Procedimiento del programa

----

​	**Para que el programa pueda funcionar, necesita dos archivos en la misma carpeta donde se encuentra el ejecutable**, que serán esenciales para la ejecución del mismo. **El primero, `config.in`**, el cuando indicara la configuración del programa; es decir,  qué tipo de emplazamiento a utilizar, el método de la política de reemplazo, el tamaño máximo de bloque y el numero de linea de bloques. **El otro archivo, `traz.in`**, indica el trazado que hará el programa para ver si en la memoria cache existe un **hit** o un **miss**. Una vez hemos verificado que existan y se encuentren en la misma carpeta, se procede a la ejecución del programa.

​	Durante el proceso, los datos del archivo `traz.in` son leídos y almacenado dentro de una lista. En esta lista indica la secuencia de direcciones del bloque y el ciclo dura hasta llegar al final del archivo.

​	Pasando al siguiente paso, ya con el trazado de `traz.in` y la configuración de `conf.in` obtenidos, se procede a llamar el procedimiento requerido para obtener los resultados. Los datos a pasar en el proceso son la lista de direcciones y el numero de bloques de la cache

## 	Política de Remplazo LRU

----

​	Para la función que representa la política de reemplazo LRU se utiliza dos listas e iteradores para cada una, donde cada una de las listas sera nuestro emulador de la memoria cache y la otra es utilizada como auxiliar para conocer el orden de uso de un elemento de la cache. El primero de la lista es el menos usado mientras que el ultimo es el mas reciente

​	Se define como variables el numero de bits que tras el índice y la etiqueta de las direcciones de bloque . Así mismo, se inicializan los contadores para saber le numero de aciertos y falos en a cache. En lo siguiente, se abre un ciclo donde un iterador pasa por todos os elementos dentro de la lista de direcciones. Para cada iteración, se define el valor binario de la dirección de bloque actual, usando el tipo de dato Bitset.

​	En el siguiente paso, otro ciclo sera ejecutado donde un segundo iterador pasa por todos los elementos de la lista auxiliar pasa por todos los elementos de la lista auxiliar o para cuando se active la bandera para casos de un acierto. En cada iteración del segundo ciclo se realiza una comparación de datos entre ambos iteradores. Si ambos datos son iguales quiere decir que la dirección de bloque actual contiene datos, a lo que nos lleva a un *acierto* y activaría la bandera para terminar el ciclo. En el caso de que la bandera no llegue a activarse, el ciclo termina al llegar al final de la lista auxiliar.

​	Volviendo a la función de la bandera. Si fue activada significa que hubo un acierto en la cache y la dirección de bloque de memoria. El programa se encargará de buscar y eliminar la dirección de bloque de memoria dentro de la lista auxiliar y añadirla al final. Esto indicará que ha sido la ultima en usarse.

​	Al terminar el proceso de acierto, procede a imprimir en el archivo la información de acierto en la dirección actual, usando el formato generado y se agrega uno al contador de aciertos. Por contrario, si la bandera de acierto no fue activada, esto nos lleva al caso de un *fallo*, siendo el siguiente proceso a ejecutar:

+ Revisa la capacidad máxima de datos. Si la memoria cache no está en su capacidad máxima, se agrega la dirección del bloque al final de la lista cache.
+ Caso contrario,  se utiliza el primer elemento de la lista auxiliar (siendo la menos reciente en ser usada) para buscarlo dentro de la lista cache. La función de buscar retorna un iterador que apunta a la primera instancia del elemento que fue buscado en la lista Cache, llevando esto a reemplazar el dato buscado con la dirección de bloque entrante.

​	Para ambos casos basado en la capacidad, se agrega la dirección de bloque actual dentro de la lista auxiliar. Aumenta uno al contador de aciertos y se imprime en el archivo la información de fallo en la dirección actual. 

​	Finaliza imprimiendo en el archivo la tasa de aciertos y la tasa de fallos obtenida.

