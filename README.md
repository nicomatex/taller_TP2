# Taller de Programacion I [75.42] - TP2

**Nombre: Nicolas Federico Aguerre**

**Padron: 102145**

**Repositorio: https://github.com/nicomatex/taller_TP2**

**Cuatrimestre: 1C 2020**

---

# Indice del informe
1. **[Enfoque General del modelo](#Enfoque)**

2. **[Parseo del archivo mapa](#ParseoMapa)**

3. **[Parseo del archivo de trabajadores](#ParseoTrabajadores)**

4. **[Los recursos](#Recursos)**

5. **[Las colas de recursos](#ColasRecursos)**

6. **[El inventario](#ColasRecursos)**

7. **[Trabajadores](#Trabajadores)**
    * 7.1. [Recolectores (Gatherers)](#Gatherers)
    * 7.2. [Productores (Producers)](#Producers)

8. **[Motor](#Engine)**

---
## 1. Enfoque General del modelo <a name="Enfoque"></a>
Como resultado de lo solicitado por el enunciado, fue evidente la necesidad de tener en el modelo diferentes instancias de una misma clase que difirieran en alguno de sus atributos, pero no en su comportamiento (por ejemplo, todos los recolectores se comportan igual, con la diferencia de que cada uno recolecta de una ```Cola Bloqueante``` diferente). Como resultado, se pensaron dos estrategias diferentes:

+ Realizar un _Factory Pattern_, implementado mediante una clase ``` GathererFactory ```, que mediante metodos como ``` create_lumberjack() ``` o ``` create_miner() ```, creara instancias de ```gatherer``` que ya contuvieran la referencia a la ```Cola Bloqueante``` adecuada. Este metodo sin embargo fue descartado porque agregaba clases y complejidad innecesarios al modelo. 
+ Realizar una _inyeccion de dependencias_ en el constructor de la clase ```gatherer```. Esto es, al momento de instanciar un ```gatherer```, es necesario pasarle a su constructor una referencia a la ``` Cola Bloqueante ``` a la cual debe ir a buscar recursos. 

Este segundo modelo se utilizo en la gran mayoria de las clases que componen el modelo, y es un patron que se repite bastante en la totalidad del trabajo practico.

Por ultimo, se decidio deshabilitar los constructores por copia y movimiento de todas las clases en las cuales dichos constructores no se utilizan, para evitar errores de programacion causados por el uso inadecuado de los mismos.

---
## 2. Parseo del archivo mapa <a name="ParseoMapa"></a>
El parseo del mapa es realizado por una instancia de la clase ```MapParser```. Esta clase contiene referencias a todas las colas de recursos del modelo. Su funcionamiento consiste en leer uno a uno los caracteres del archivo de mapa, y para cada caracter hacer el siguiente procedimiento:

1. Traducir el caracter a un id de recurso, mediante el uso de un ```unordered_map``` que tiene por claves caracteres y por valores el id de recurso asociado a ese caracter.
2. Depositar una nueva copia del recurso con ese id asociado en la cola correspondiente (tambien identificada por el id de recurso, tambien mediante un ```unordered_map``` que tiene por clave el id del recurso y por valor una referencia a la cola correspondiente).

Una vez el parseo esta completo, el parser procede a cerrar las colas de recursos, indicando que ya se termino de parsear el archivo mapa, y por ende que no habra mas recursos disponibles.

---
## 3. Parseo del archivo de trabajadores <a name="ParseoTrabajadores"></a>
El parseo del archivo de trabajadores es hecho por la clase ```ConfigParser```. Esta clase tiene un único método ```get_worker_list``` que devuelve un ```unordered_map``` de la forma <tipo_trabajador:cantidad>. Esto se logra leyendo linea a linea del archivo de trabajadores, y parseando cada linea de la forma ```clave = valor``` de dicho archivo.

---
## 4. Los recursos <a name="Recursos"></a>
En un principio, la clase ```Recurso``` no fue incluida como tal en el modelo (y los recursos eran modelados simplemente con un entero, diferente para cada tipo de recurso). Sin embargo, se decidió que tener dicha clase en el modelo lo haría mas flexible, y facilitaría la extension del mismo si se decidiera agregar algun comportamiento nuevo relacionado a los recursos. 

Para facilitar la integración de esta clase en la misma, se implemento de tal forma que cada recurso tuviera un ```id``` unico por tipos, y que la comparación entre recursos se hiciera mediante sus ids. 

Es la única clase del modelo cuyo constructor por copia esta habilitado, y es usado por el ```MapParser``` a la hora de encolar nuevos recursos en las colas de recursos.

---
## 5. Las colas de recursos <a name="ColasRecursos"></a>
Las colas de recursos, como se menciono antes, estan implementadas utilizando ```Colas Bloqueantes```, en las cuales se encolan instancias de la clase ```Recurso```, y a las cuales los _recolectores_ intentan acceder continuamente para llevar los recursos hacia el inventario. 

Como particularidad implementativa, las ```Colas Bloqueantes``` aqui utilizadas estan hechas de tal forma que, cuando se intenta desencolar una cola que esta vacia y que fue cerrada, la cola devuelve una instancia especial del tipo de dato que contiene llamada ```empty_return```. Este valor es luego recibido por los recolectores, y les indica que la cola fue cerrada y esta vacia. 

---
## 6. El Inventario <a name="Inventario"></a>

El inventario esta implementado también como una especie de "cola bloqueante", que encapsula una condition variable que se utiliza para dormir a los ```productores``` cuando estos intentan retirar recursos del inventario, y estos no estan disponibles, y a su vez para despertarlos y comprobar la disponibilidad de los mismos cada vez que un ```recolector``` deposita un recurso. 

Todas las operaciones criticas del inventario estan resguardadas por un ```mutex``` (es decir, el depositar, el retirar y el cerrar el inventario). 

Se implementa tambien un mecanismo de recetas ```recipes```, que no son mas que ```unordered_map``` de la forma ```<id,cantidad>```, donde cada entrada representa un recurso y la cantidad que se necesita de ese recurso. Cada productor tiene una recipe diferente, y el metodo para retirar recursos del inventario recibe una receta particular del productor solicitante, y devuelve ```true``` en caso de que los recursos esten disponibles, y ```false``` en caso de que no lo esten y el inventario este cerrado.

---
## 7. Trabajadores <a name="Trabajadores"></a>
Todos los trabajadores en el presente trabajo práctico están modelados como _objetos activos_. Esto quiere decir que todos encapsulan su comportamiento como _threads_ dentro del propio objeto trabajador. En particular, esto está implementado mediante una clase abstracta ```Thread```, de la cual todos los trabajadores heredan y de la cual sobreescriben el método ```run```, para implementar su funcion particular (ya sean recolectores o productores).


**7.1. Recolectores (Gatherers)**<a name="Gatherers"></a>

Los recolectores son instanciados con una referencia a la Cola Bloqueante a la cual deben ir a buscar recursos, y al inventario. En cada iteracion de la búsqueda de recursos, se verifica que el recurso obtenido de la cola no sea un ```empty_return```. De ser este el caso, se finaliza la ejecución del thread. Por otro lado, si lo obtenido es un recurso válido, se duerme el thread durante el tiempo indicado en la consigna del trabajo, y luego se procede a depositar el recurso en el inventario.


![Imagen 1](img/1.png?raw=true)

_Imagen 1. Diagrama de clase de los recolectores._

**7.2. Productores (Producers)**<a name="Producers"></a>

Los productores son instanciados con referencias al inventario y a un contenedor en el cual van a depositar los puntos de beneficio que generen, asi como tambien con la receta que utilizan para generar puntos de beneficio. Esta estrategia permite tener una unica clase ```Producer``` con la cual se implementan los tres tipos de productores del modelo. 

Estos productores constantemente intentan retirar los recursos indicados en su receta del inventario, y cuando son exitosos, depositan una cierta cantidad de puntos de beneficio al cabo de un cierto tiempo. Cuando el inventario esta cerrado y no hay recursos suficientes, el hilo de ejecucion de los productores finaliza.

![Imagen 2](img/2.png?raw=true)

_Imagen 2. Diagrama de clase de los productores._

---
## 8. Motor <a name="Engine"></a>

La clase encargada de coordinar el correcto funcionamiento de todas las piezas del modelo es el motor o ```Engine```. El motor es aquel que contiene como atributos todos los bloques del modelo: El inventario, el contenedor de puntos, los vectores de trabajadores, las colas de recursos, los parsers, etc. Esto esta hecho de tal forma que al crear una instancia de la clase ```Engine```, cada uno de los componentes del mismo se alojen en el stack de ejecucion de la funcion que creo dicha instancia, permitiendo aprovechar las ventajas del patron RAII. Mediante una serie de metodos sencillos, el ```Engine``` presenta una interfaz desde la cual se puede poner en marcha cada mecanismo del modelo: desde parsear los archivos, "spawnear" los trabajadores, cerrar el inventario, hasta esperar que la ejecucion de cada trabajador termine, y finalmente imprimir la salida pertinente por pantalla. Se adjuntan a continuacion dos diagramas que muestran la relacion del motor con los distintos componentes.

![Imagen 3](img/3.png?raw=true)

_Imagen 3. Diagrama de clase del engine con los parser._


![Imagen 4](img/4.png?raw=true)
_Imagen 4. Diagrama de clase del engine con el modelo._
