#include "abb.h"
#include "abb_estructura_privada.h"

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


void abb_destruir(abb_t* abb)
{
    return;
}


void abb_destruir_todo(abb_t* abb, void (*destructor)(void*))
{
    return;
}

bool abb_insertar(abb_t *abb, void* elemento)
{
    return true;
}


bool abb_quitar(abb_t* abb, void* buscado, void** encontrado)
{
    return true;
}


void* abb_obtener(abb_t* abb, void* elemento)
{
    return;
}


size_t abb_cantidad(abb_t* abb)
{
    return 0;
}


size_t abb_iterar_inorden(abb_t* abb, bool (*f)(void*,void*), void* ctx)
{
    return 0;
}
size_t abb_iterar_preorden(abb_t* abb, bool (*f)(void*,void*), void* ctx)
{
    return 0;
}

size_t abb_iterar_postorden(abb_t* abb, bool (*f)(void*,void*), void* ctx)
{
    return 0;
}

size_t abb_vectorizar_inorden(abb_t* abb, void** vector, size_t tamaño)
{
    return 0;
}

size_t abb_vectorizar_preorden(abb_t* abb, void** vector, size_t tamaño)
{
    return 0;
}

size_t abb_vectorizar_postorden(abb_t* abb, void** vector, size_t tamaño)
{
    return 0;
}