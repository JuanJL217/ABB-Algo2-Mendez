<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA ABB

# ESTO ES UN TEMPLATE, COMPLETAR LO QUE HAGA FALTA, ELIMINAR LO QUE SOBRE (INCLUIDA ESTA LÍNEA)

## Alumno: Juan Ernesto Juarez Lezama - 110418 - jjuarez@gmail.com

- Para compilar:

```bash
línea de compilación
```

- Para ejecutar:

```bash
línea de ejecución
```

- Para ejecutar con valgrind:
```bash
línea con valgrind
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

## Arbol Binario

## Árbol Binario de Busqueda

## ¿Por qué es importante la distintición entre estos tipos de árboles?

-   Explique la implementación de ABB realizada y las decisiones de diseño
    tomadas (por ejemplo, si tal o cuál funciones fue planteada de forma
    recursiva, iterativa o mixta y por qué, que dificultades encontró al manejar
    los nodos y punteros, reservar y liberar memoria, etc).

## Diseño
Cómo ya sabemos, en nuestra implementación usaremos 2 estructuras: `abb_t` es la estructura principal de nuestro TDA y `nodo_t` que es ela estructura que almacenará nuestra información.

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

Tanto para las funciones de insertar, obtener y quitar, vamos a tener una función en común, que es la función de buscar un nodo. Al ser un Árbol Binario de Busqueda, vamos a tener que hacer comparaciones para llegar a un nodo, o llegar a ninguno (si es que tal elemento no se encuentra en el abb), ya esto, usé una función recursiva:
```c
nodo_t** buscar_nodo(abb_t* abb, nodo_t** nodo_actual, void* elemento)
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

## Recorridos:
-Preorden
-Inorden
-Postorden