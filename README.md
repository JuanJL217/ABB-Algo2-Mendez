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

#   Explique teóricamente (y utilizando gráficos) qué es una árbol, árbol
    binario y árbol binario de búsqueda. Explique cómo funcionan, cuáles son sus
    operaciones básicas (incluyendo el análisis de complejidad de cada una de
    ellas) y por qué es importante la distinción de cada uno de estos diferentes
    tipos de árboles. Ayúdese con diagramas para explicar.

### Operaciones básicas: insertar, obtener y eliminar

## Árbol

## Arbol Binario

## Árbol Binario de Busqueda

## ¿Por qué es importante la distintición entre estos tipos de árboles?

#   Explique la implementación de ABB realizada y las decisiones de diseño
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