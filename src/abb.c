#include "abb.h"
#include "abb_estructura_privada.h"

nodo_t* nodo_crear(void* elemento)
{
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (!nodo)
        return NULL;
    nodo->elemento = elemento;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

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

abb_t* abb_crear(int (*comparador)(void*, void*))
{
    abb_t* inicializar_abb = malloc(sizeof(abb_t));
    if (!inicializar_abb)
        return NULL;
    inicializar_abb->nodos = 0;
    inicializar_abb->raiz = NULL;
    inicializar_abb->comparador = comparador;
    return inicializar_abb;
}

void destruir_todo_el_abb(nodo_t* nodo_actual, void (*destructor)(void*))
{
    //POSTORDEN
    if (!nodo_actual)
        return;
    destruir_todo_el_abb(nodo_actual->izq, destructor);
    destruir_todo_el_abb(nodo_actual->der, destructor);
    if (destructor)
        destructor(nodo_actual->elemento);
    free(nodo_actual);
}

void abb_destruir_todo(abb_t* abb, void (*destructor)(void*))
{
    if (!abb)
        return;
    destruir_todo_el_abb(abb->raiz, destructor);
    free(abb);
}

void abb_destruir(abb_t* abb)
{
    if (!abb)
        return;
    abb_destruir_todo(abb, NULL);
}

nodo_t** buscar_predecesor_inorden(nodo_t** nodo_actual)
{   
    if (!*nodo_actual) {
        return nodo_actual;
    }
    return buscar_predecesor_inorden(&((*nodo_actual)->der));
}

bool abb_esta_vacio(abb_t* abb)
{
    return abb->nodos == 0;
}

bool abb_insertar(abb_t *abb, void* elemento)
{
    if (!abb)
        return false;

    nodo_t* nuevo_nodo = nodo_crear(elemento);
    if (!nuevo_nodo) 
        return false;

    if (abb_esta_vacio(abb)) {
        abb->raiz = nuevo_nodo;
    } else {
        nodo_t** nodo_padre = buscar_nodo(abb, &(abb->raiz), elemento);
        if (!*nodo_padre) {
            (*nodo_padre) = nuevo_nodo;
        } else {
            nodo_t** nodo_encontrado = buscar_predecesor_inorden(&((*nodo_padre)->izq));
            (*nodo_encontrado) = nuevo_nodo;
        }
    }
    abb->nodos++;
    return true;
}



// bool abb_quitar(abb_t* abb, void* buscado, void** encontrado)
// {   
//     if (!abb || !abb->raiz)
//         return false;
    
//     nodo_t* nodo_eliminar = buscar_nodo(abb, &(abb->raiz), buscado);
//     if (!nodo_eliminar)
//         return false;

//     void* elemento_encontrado = nodo_eliminar->elemento;

//     // los casos ...


//     if (encontrado)
//         *encontrado = elemento_encontrado;
//     return true;
// }


void* abb_obtener(abb_t* abb, void* elemento)
{
    if (!abb || !abb->raiz)
        return NULL;
    
    nodo_t** nodo_obtenido = buscar_nodo(abb, &(abb->raiz), elemento);
    if (!*nodo_obtenido)
        return NULL;
    
    return (*nodo_obtenido)->elemento;
}


size_t abb_cantidad(abb_t* abb)
{
    return abb->nodos;
}

// void recorrido_inorden(nodo_t* nodo_actual, bool (*f)(void*, void*), void* ctx, size_t* contador)
// {  
//     if !()
// }

// size_t abb_iterar_inorden(abb_t* abb, bool (*f)(void*,void*), void* ctx)
// {
//     if(!abb || !abb->raiz)
//         return 0;
//     size_t cantidad_nodos_recorridos = 0;
//     recorrido_inorden(abb->raiz, f, &cantidad_nodos_recorridos);
//     return cantidad_nodos_recorridos;
// }
// size_t abb_iterar_preorden(abb_t* abb, bool (*f)(void*,void*), void* ctx)
// {
//     return 0;
// }


bool recorrido_postorden(nodo_t* nodo_actual, bool (*f)(void*, void*), void* ctx, size_t* contador)
{
    if (!nodo_actual)
        return true;
    if (!recorrido_postorden(nodo_actual->izq, f, ctx, contador) || !recorrido_postorden(nodo_actual->der, f, ctx, contador))
        return false;
    if (!f(nodo_actual->elemento, ctx))
        return false;
    (*contador)++;
    return true;
}


size_t abb_iterar_postorden(abb_t* abb, bool (*f)(void*,void*), void* ctx)
{
    if (!abb)
        return 0;
    
    size_t cantidad_nodos_recorridos = 0;
    if (!recorrido_postorden(abb->raiz, f, ctx, &cantidad_nodos_recorridos))
        return cantidad_nodos_recorridos+1;
    return abb->nodos;
}

// size_t abb_vectorizar_inorden(abb_t* abb, void** vector, size_t tamaño)
// {
//     return 0;
// }

// size_t abb_vectorizar_preorden(abb_t* abb, void** vector, size_t tamaño)
// {
//     return 0;
// }

// size_t abb_vectorizar_postorden(abb_t* abb, void** vector, size_t tamaño)
// {
//     return 0;
// }