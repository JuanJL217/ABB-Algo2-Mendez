<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA ABB

## Alumno: Juan Ernesto Juarez Lezama - 110418 - jjuarez@gmail.com

- Para compilar:

```bash
gcc -g tp_abb.c src/abb.c src/csv.c src/split.c -o tp_abb
```

- Para ejecutar:

```bash
./tp_abb pokedex.csv
```

- Para ejecutar con valgrind:
```bash
valgrind ./tp_abb pokedex.csv
```

---

##  Funcionamiento

Explicación de cómo funcionan las estructuras desarrolladas en el TP y el funcionamiento general del mismo.

Aclarar en esta parte todas las decisiones que se tomaron al realizar el TP, cosas que no se aclaren en el enunciado, fragmentos de código que necesiten explicación extra, etc.

Incluír **EN TODOS LOS TPS** los diagramas relevantes al problema (mayormente diagramas de memoria para explicar las estructuras, pero se pueden utilizar otros diagramas si es necesario).

### Por ejemplo:

El programa funciona abriendo el archivo pasado como parámetro y leyendolo línea por línea. Por cada línea crea un registro e intenta agregarlo al vector. La función de lectura intenta leer todo el archivo o hasta encontrar el primer error. Devuelve un vector con todos los registros creados.

<div align="center">
<img width="70%" src="img/diagrama1.svg">
</div>

En el archivo `sarasa.c` la función `funcion1` utiliza `realloc` para agrandar la zona de memoria utilizada para conquistar el mundo. El resultado de `realloc` lo guardo en una variable auxiliar para no perder el puntero original en caso de error:

```c
int *vector = realloc(vector_original, (n+1)*sizeof(int));

if(vector == NULL)
    return -1;
vector_original = vector;
```


<div align="center">
<img width="70%" src="img/diagrama2.svg">
</div>

---

## Respuestas a las preguntas teóricas

-   Explique teóricamente (y utilizando gráficos) qué es una árbol, árbol
    binario y árbol binario de búsqueda. Explique cómo funcionan, cuáles son sus
    operaciones básicas (incluyendo el análisis de complejidad de cada una de
    ellas) y por qué es importante la distinción de cada uno de estos diferentes
    tipos de árboles. Ayúdese con diagramas para explicar.

### Operaciones básicas: insertar, obtener y eliminar

## Árbol
También conocido como Árbol N-ario, este árbol tiene la propiedad de que puede tener hsata `n` hijos. Puede ser 2, 3, 4, 5 ... No hay limites para la cantidad de hijos que puede tener cada padre (nosotros le damos la cantidad `n`), y no sabe qué cosa es menor o mayor.
Mi criterio de ordenamiento será un recorrido por niveles.

Insertar: Al ser un recorrido por niveles, cuando queremos agregar un elemento, debemos recorrer los nodos hasta encontrar el primer NULL, esto lo convierten en `O(n)`

<div align="center">
<img width="70%" src="img/arbol_general_insertar.png">
</div>

Obtener:

<div align="center">
<img width="70%" src="img/arbol_general_obtener.png">
</div>

Eliminar:

<div align="center">
<img width="70%" src="img/arbol_general_eliminar.png">
</div>

## Arbol Binario
A diferencia del Árbol N-ario, este árbol tiene la distinción de que como máximo, cada padre puede tener 2 hijos, pero tampoco conoce qué es menor o mayor.
Mi criterio de ordenamiento será un recorrido por niveles.

Insertar:

<div align="center">
<img width="70%" src="img/arbol_binario_insertar.png">
</div>

Obtener:

<div align="center">
<img width="70%" src="img/arbol_binario_obtener.png">
</div>

Eliminar:

<div align="center">
<img width="70%" src="img/arbol_binario_eliminarpng">
</div>


## Árbol Binario de Busqueda
Árbol Binario de Busqueda, tendrá la distinción de qué cosa es menor, igual o mayor. Como convención, lo menor irá a la izquierda, y lo mayor a la derecha.
Tendré 2 criterios de ordenamiento: Uno sin AVl y el otro con ALV.

`Insertar sin AVL`: El peor de los casos es que se inserte de tal manera que parezca una lista, entonces será `O(n)`.
`Insertar con ALV`: Al tener un manejo de como acomodar las ramas para que haya un orden con mejor optimización, al ser que vamos a movernos por rama, o sea, elegir una de dos opciones, eso es un O(log(n)).

<div align="center">
<img width="70%" src="img/arbol_binario_de_busqueda_insertar.png">
</div>

`Obtener sin AVL`: Al igual que insertar, el hecho de que puede quedar como una lista, y que busquemos el nodo del extremo, esta función se convierte en `O(n)`.
`Obtener con AVL`: Buscará moviendose entre las ramas, por ende es `O(log(n))`.

<div align="center">
<img width="70%" src="img/arbol_binario_de_busqueda_obtener.png">
</div>

`Eliminar sin ALV`: Misma lógica, el peor caso es que borre el nodo del extremo, o también borrar un nodo con 2 hijos y que el nodo de su predecor inorden esté lejos, esto es `O(n)`.
`Eliminar con ALV`; Suponiendo que queremos eliminar un nodo que tiene 2 hijos, no puede suceder que el predecesor inorden este lejos, ya que no sería ALV, por ende, esto es `O(log(n))`.

<div align="center">
<img width="70%" src="img/arbol_binario_de_busqueda_eliminar.png">
</div>

## ¿Por qué es importante la distintición entre estos tipos de árboles?
Es importante diferenciar estos 3 tipos de árboles por 2 razones: La primera sería para identificar 

-   Explique la implementación de ABB realizada y las decisiones de diseño
    tomadas (por ejemplo, si tal o cuál funciones fue planteada de forma
    recursiva, iterativa o mixta y por qué, que dificultades encontró al manejar
    los nodos y punteros, reservar y liberar memoria, etc).

## Diseño
Cómo ya sabemos, en nuestra implementación usaremos 2 estructuras: `abb_t` es la estructura principal de nuestro TDA y `nodo_t` que es la estructura de cada nodo que guardará información

```c
	typedef struct nodo {
		void *elemento;
		struct nodo *izq;
		struct nodo *der;
	} nodo_t;

	typedef struct abb {
		size_t nodos;
		nodo_t *raiz;
		int (*comparador)(void*, void*);
	}abb_t;
```

Tanto para las funciones de insertar, obtener y quitar, vamos a tener una función en común, que es la función de buscar un nodo. Al ser un Árbol Binario de Busqueda, vamos a tener que hacer comparaciones para llegar a un nodo, o llegar a ninguno (si es que tal elemento no se encuentra en el abb). Para esto, usé una función recursiva.
```c
	nodo_t **buscar_nodo(abb_t* abb, nodo_t** nodo_actual, void* elemento)
	{
		if (!*nodo_actual || abb->comparador(elemento, (*nodo_actual)->elemento) == 0) {
			return nodo_actual;
		} else if (abb->comparador(elemento, (*nodo_actual)->elemento) < 0) {
			return buscar_nodo(abb, &(*nodo_actual)->izq, elemento);
		} else {
			return buscar_nodo(abb, &(*nodo_actual)->der, elemento);
		}
	}
```
Cómo se puede ver, la función retorna un `nodo_t**`, pero, ¿por qué doble puntero y no uno solo? Bueno, la respuesta es para optimizar código. La explicación es la siguiente: Si nosotros hacemos una función que retorne un `nodo_t*`, significa que estamos retornando un puntero a nodo, o sea, la dirección de memoria del nodo, cosa que está bien, si buscamos un nodo que contenga un elemento `x`, entonces una función que retorna `nodo_t*` hace ese trabajo, pero qué pasa con esto, para la función `obtener` viene de maravilla, porque si se encuentra, retorna el nodo, si no, retorna `NULL` En la función de `insertar`, sucede algo casi parecido pero con modificaciones, pero la idea principal para usar esté codigo es cuando queremos `quitar` un elemento, porque aparte de encontrar el nodo, debemos buscar el padre de ese nodo, y como nuestro abb solo tiene una dirección, no podemos saber quién es su padre, y tendriamos que volver a iterar hasta un nodo antes, entonces, primero intenté solucionar el mayor problema y con esa solución, solucionar las otras más pequeñas y es por eso que usé una función que retorne `nodo_t**`, porque gracias a esto, no necesito buscar el nodo padre, ya que yo estoy dentro del nodo padre, y tengo la dirección de memoria del puntero que apunta al hijo, por ende, tengo la dirección de memoria de mi hijo estando dentro del padre sin apuntar al padre.

<div align="center">
<img width="70%" src="img/puntero_nodo.png">
</div>

Con este movimiento, no tengo que estar dando más `if`, porque puede darse el caso de que elimine un nodo raiz, entonces se debe hacer verificaciones extras, pero con mi implementación, ya maneja esos casos internamente. Un ejemplo: Si quiero eliminar el único nodo que tiene un abb, sería la raiz, entonces, si elimino usando una función que retorna `nodo_t*`, cuando verifique que el nodo es una hoja, aparte de eso, debe verificar si es una raiz o no, en cambio, como yo uso retorno un `nodo_t**`, observar que yo le paso la direccióñ de memoria de la raiz.  

```c
    nodo_t **puntero_entre_padre_e_hijo = buscar_nodo(abb, &(abb->raiz), buscado);
```

Cuando entra en la función de busqueda, y el elemento que busca, es el mismo que la raíz, retorna lo mismo que ingresé (la dirección de memoria de la raíz), entonces cuando entra en la función de `borrar_nodo_hoja`, significa que está haciendo un `raiz = NULL`, y así es como reduje verificaciones extras.

## Recorridos:
-Preorden  
-Inorden  
-Postorden  

Me centraré en un solo recorrido, ya que toda la lógica de funcionamiento se repite para los otros 2 recorridos (exceptuando las posiciones de qué nodo visita primero).  

En este caso, me centraré en el recorrido postorden, es el recorrido que una vez que visite al hijo izquierdo y al hijo derecho, se puede recién visitar a sí mismo. El código es el siguiente:

```c
	bool recorrido_postorden(nodo_t *nodo_actual, bool (*f)(void *, void *),
				void *ctx, size_t *contador, size_t tope)
	{
		if (!nodo_actual)
			return true;
		if (!recorrido_postorden(nodo_actual->izq, f, ctx, contador, tope) ||
			!recorrido_postorden(nodo_actual->der, f, ctx, contador, tope))
			return false;
		if (*contador == tope || !f(nodo_actual->elemento, ctx))
			return false;
		(*contador)++;
		return true;
	}
```

Si bien la función `abb_iterar_postorden` debe retornar un `size_t`, la función recurisiva hubiese podido ser una función que también retorne un `size_t`, pero decidí que mejor sea una función boleana. Lo que gano con esto, es verificar el estado actual de mi hijo, si su resultado fue un `true` o un `false`. Si alguno dio `false`, entonces es como decir: "Bueno, mi hijo me tiró false, entonces no puedo visitarme a mí mismo, también retorno false", entonces es un efecto en cadena de `return false`. Con esto gano que, al ser una función recursiva booleada, la función me tire un estado, dependiendo de ese estado, significa que en algún punto de la iteración dio `false`, entonces retorno el `contador+1`, pero si la función dio true, significa que iteró todo sin problemas, entonces, puedo decir con certeca que retorno la cantidad de elementos en el abb: `abb->nodos`.

```c
	size_t cantidad_iterados = 0;
	return !recorrido_postorden(abb->raiz, f, ctx, &cantidad_iterados, abb->nodos) ? cantidad_iterados+1 : abb->nodos;
```

Terminamos con el recorrido y verificaciones para la función iterativa, pero, podemos observar que hay un parametro más en nuestra función, que es: `size_t tope`. La razón de esto es porque quiero reutilizar esta misma función recursiva de iteración en `abb_vectorizar_postorden` (misma lógica para los otros recorridos). Podemos ver que ambas funciones hacen algo similiar, que es recorrer el arbol, con la diferencia de que en `abb_iterar_postorden` debemos mandar una función que haga algo con cada elemento, pero en la función `abb_vectorizar_postorden`, debe poner cada elemento en cada posición del vector, hasta alcanzar todo el tamaño que nos dan, entonces de ahí viene el porqué de ese parametro, con eso ganamos que cuando llegue a esa posicion (el contador), salga de la función.
```c
	if (*contador == tope || !f(nodo_actual->elemento, ctx))
		return false;
```

Ahora bien, aquí viene otra razón de por qué también reutilizé la función recursiva, y es que, en vez de crear otra función auxiliar que ponga cada elemento en dicho vector, mejor reutilizar el parametro `bool (*f)(void *, void *), void *ctx`: Lo que hago es, darle la dirección de memoria del vector en `ctx`, y una función que haga algo con ese vector em `f`.

```c
	bool asignar_elementos_en_vector(void *elemento, void *vector)
	{
		void ***puntero_a_vector = (void ***)vector;
		**puntero_a_vector = elemento;
		(*puntero_a_vector)++;
		return true;
	}
```

Lo que hace esta función, mejor dicho, la variable `puntero_a_vector` es tener la dirección del bloque en cada momento de la iteración, pudiendo así asignarle valores a cada bloque y poder moverme al siguiente bloque. Para entender todo eso, prefiero explicar como se comportan los punteros desde el momento que inicializo un vector, hasta cuando le asigno elementos (No hago distinción de stack y heap, solo me centraré en la manipulación de punteros)

1) Inicializamos el vector (para esto ya debemos tener el abb con sus respectivos elementos).

<div align="center">
<img width="70%" src="img/inicializar_vector.png">
</div>

2) Entender cómo funciona el parametro `void** vector` en `abb_vectorizar_postorden`.  
Cuando nosotros asignamos el vector como parametro de la función de vectorizacion: `(void **)&vector`, lo que sucede es que dentro de dicha función, vamos a tener un puntero que apunta a la dirección de memoria del vector.

<div align="center">
<img width="70%" src="img/parametro_vector_en_vectorizar.png">
</div>

3) El porqué mandamos `&vector` en la función recursivdad `recorrido_postorden`.
Ya que entendemos cómo manejar punteros dobles, también podemos manejar punteros triples. En este caso, apuntaremos al puntero que apunta al vector, ¿por qué?, porque de esta manera, aparte de demostrar el manejo de punteros, podemos hacer más fácil la manipulación de los bloques.

<div align="center">
<img width="70%" src="img/vector_en_la_recursividad.png">
</div>

4) Cómo se maneja los punteros en la función `asignar_elementos_en_vector`.  
En el código podemos observar que hacermos un casteo `void ***puntero_a_vector = (void ***)vector`, como vimos en la imagen del punto 3, vemos que cada parte corresponde un puntero void en particular, en nuestro caso, al un un puntero que apunta al puntero del vector, es un `void***`, de ahí el porqué el casteo. Con esto gano 'movilidad'.  
El recorrido postorden de nuestro abb, seria: 5, 9, 8.

<div align="center">
<img width="70%" src="img/triple_puntero_vector1.png">
</div>

<div align="center">
<img width="70%" src="img/triple_puntero_vector2.png">
</div>

<div align="center">
<img width="70%" src="img/triple_puntero_vector3.png">
</div>

Podemos observar que aquí, cuando llegamos al al último bloque del vector, y avanzamos, vamos a un lugar peligroso, un lugar que está por guera del límite, pero, es peligroso si interactuamos con dicho lugar, ¿por qué menciono esto? Pues me refiero a las condiciones de corte en la función recursiva: `if (*contador == tope || !f(nodo_actual->elemento, ctx))` ... Al ser un `or`, significa que, si la primera condición es cierta, no va a verificar si es cierto o no lo de la derecha, lo que significa que si no es cierto la primera condición, entra en la función f. Debido a esa lóigca, cuando el contador llegue al tamaño del vector, nos aseguramos que jamás entrará a terreno prohibido.