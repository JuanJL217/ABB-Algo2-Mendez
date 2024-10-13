#include "pa2m.h"
#include "src/abb.h"

int comparar_numeros(void* a, void* b)
{
	return *(int*)a - *(int*)b;
}

int comparar_letras(void* a, void* b)
{
	return *(char*)a - *(char*)b;
}

bool sumar_elementos(void* elemento, void* sumador)
{	
	(*(int*)sumador) += (*(int*)elemento);
	return true;
}

bool corte_elementos(void* elemento, void* corte)
{
	return (*(int*)elemento == *(int*)corte)?false:true;
}

void inicializarAbb()
{
	abb_t* abb = abb_crear(comparar_numeros);
	if (!abb)
		return;
	int numero = 5;
	pa2m_afirmar(abb_cantidad(abb) == 0, "ABB inicializado tiene 0 elemento");
	if (!abb_insertar(abb, (void*)&numero)) {
		abb_destruir(abb);
		return;
	}
	pa2m_afirmar(abb_cantidad(abb) == 1, "Se agregó satisfactoriamene un elemento");
	abb_destruir(abb);
	
}

void agregarElementosDiferentes()
{
	abb_t* abb = abb_crear(comparar_numeros);
	if (!abb)
		return;
	
	int numeros[] = {6, 2, 7, 1, 8, 9};
	for (size_t i = 0; i < 6; i++) {
		if (!abb_insertar(abb, (void*)&numeros[i])) {
			abb_destruir(abb);
			return;
		}
	}
	pa2m_afirmar(abb_cantidad(abb) == 6, "Se agregaron 6 elementos diferentes en el abb");
	abb_destruir_todo(abb, NULL);
}

void agregarTodosRepetidos()
{
	abb_t* abb = abb_crear(comparar_numeros);
	if (!abb)
		return;
	
	int numeros[] = {6, 6, 6, 6, 6, 6, 6, 6, 6, 6};
	for (size_t i = 0; i < 10; i++) {
		if (!abb_insertar(abb, (void*)&numeros[i])) {
			abb_destruir(abb);
			return;
		}
	}
	pa2m_afirmar(abb_cantidad(abb) == 10, "Se agregaron 10 elementos repetidos en el abb");
	abb_destruir_todo(abb, NULL);
}

void agregarElementosVariados()
{	
	abb_t* abb = abb_crear(comparar_numeros);
	int numeros[] = {10, 2, 2, 6, 9, 2, 14, 10, 17, 6, 1, 1, 1, 9, 2, 14};
	for (size_t i = 0; i < 16; i++){
		if (!abb_insertar(abb, (void*)&numeros[i])) {
			abb_destruir(abb);
			return;
		}
	}
	pa2m_afirmar(abb_cantidad(abb) == 16, "Se agregaron 16 elementos, entre repetidos y diferentes en el abb");
	abb_destruir(abb);
}
void obtenerElementos()
{
	abb_t* abb = abb_crear(comparar_numeros);
	if (!abb)
		return;
	
	int numeros[] = {10, -4, 2, 5, 8, 1, 13, -9};
	for (size_t i = 0; i < 8; i++) {
		if (!abb_insertar(abb, (void*)&numeros[i])) {
			abb_destruir(abb);
			return;
		}
	}
	pa2m_afirmar(abb_cantidad(abb) == 8, "Se agregaron 8 elementos");

	int numeros_a_buscar[] = {-9, 13, 1, 8, 5, 2, -4, 10};
	int* obtenido;
	for (size_t i = 0; i < 8; i++) {
		obtenido = (int*) abb_obtener(abb, (void*)&numeros_a_buscar[i]);
		pa2m_afirmar(obtenido == &numeros[7-i], "Se encontró el elemento '%d', direccion obtenida: '%p' -> direccion esperada: '%p'", numeros[7-i], obtenido, &numeros[7-i]);
	}
	int buscar = 20;
	obtenido = (int*) abb_obtener(abb, (void*)&buscar);
	pa2m_afirmar(obtenido == NULL, "Buscar un elemento que no está en el abb, retorna NULL");

	abb_destruir_todo(abb, NULL);
}

void eliminarRaizSinHijos()
{
	abb_t* abb = abb_crear(comparar_letras);
	if (!abb)
		return;
	char* nombre[] = {"Juan", "Leonardo"};
	if (!abb_insertar(abb, (void*)nombre[0])) {
		abb_destruir(abb);
		return;
	}
	pa2m_afirmar(abb_cantidad(abb) == 1, "Se agregó un elemento en la raiz");

	char* nombre_quitado;
	char* nombre_eliminar = "Juan";
	abb_quitar(abb, (void*)nombre_eliminar, (void**)&nombre_quitado);
	pa2m_afirmar(nombre_quitado == nombre[0], "Se quitó el elemento 'Juan', la direccion obtenida es: '%p' -> esperado: '%p'", nombre_quitado, nombre[0]);
	pa2m_afirmar(abb_cantidad(abb) == 0, "No hay elemento en el abb");
	pa2m_afirmar(abb_obtener(abb, (void*)&nombre_eliminar) == NULL, "No se encontró el elemento 'Juan' quitado en el abb");

	if(!abb_insertar(abb, (void*)nombre[1])) {
		abb_destruir(abb);
		return;
	}
	pa2m_afirmar(abb_cantidad(abb) == 1, "Se agregó un alemento al abb");

	nombre_eliminar = "Leonardo";
	abb_quitar(abb, (void*)nombre_eliminar, (void**)&nombre_quitado);
	pa2m_afirmar(nombre_quitado == nombre[1], "Se quitó el elemento 'Leonardo', la direccion obtenida es: '%p' -> esperado: '%p'", nombre_quitado, nombre[1]);
	pa2m_afirmar(abb_cantidad(abb) == 0, "No hay elemento en el abb");
	pa2m_afirmar(abb_obtener(abb, (void*)&nombre_eliminar) == NULL, "No se encontró el elemento 'Leonardo' quitado en el abb");
	free(abb);
}

void eliminarElementosSinHijos()
{
	abb_t* abb = abb_crear(comparar_letras);
	if (!abb)
		return;
	char letras[] = {'c', 'a', 'd'};
	for (size_t i = 0; i < 3; i++) {
		if (!abb_insertar(abb, (void*)&letras[i])) {
			abb_destruir(abb);
			return;
		}
	}
	pa2m_afirmar(abb_cantidad(abb) == 3, "El abb tiene 3 elementos: 'c', 'a', 'd'");
	char* letra_quitada;
	char letra_eliminar = 'a';
	abb_quitar(abb, (void*)&letra_eliminar, (void**)&letra_quitada);
	pa2m_afirmar(letra_quitada == &letras[1], "Se quitó el elemento 'a', la dirección obtenida es: '%p' -> esperado: '%p'", letra_quitada, &letras[1]);
	pa2m_afirmar(abb_cantidad(abb) == 2, "Quedan 2 elementos en el abb");
	pa2m_afirmar(abb_obtener(abb, (void*)&letra_eliminar) == NULL, "No se encontró el elemento 'a' en el abb");

	letra_eliminar = 'd';
	abb_quitar(abb, (void*)&letra_eliminar, (void**)&letra_quitada);
	pa2m_afirmar(letra_quitada == &letras[2], "Se quitó el elemento 'd', la dirección obtenida es: '%p' -> esperado: '%p'", letra_quitada, &letras[2]);
	pa2m_afirmar(abb_cantidad(abb) == 1, "Quedan 1 elementos en el abb");
	pa2m_afirmar(abb_obtener(abb, (void*)&letra_eliminar) == NULL, "No se encontró el elemento 'd' en el abb");

	letra_eliminar = 'c';
	abb_quitar(abb, (void*)&letra_eliminar, (void**)&letra_quitada);
	pa2m_afirmar(letra_quitada == &letras[0], "Se quitó el elemento 'c', la dirección obtenida es: '%p' -> esperado: '%p'", letra_quitada, &letras[0]);
	pa2m_afirmar(abb_cantidad(abb) == 0, "No hay elementos en el abb");
	pa2m_afirmar(abb_obtener(abb, (void*)&letra_eliminar) == NULL, "No se encontró el elemento 'c' en el abb");
	abb_destruir_todo(abb, NULL);
}

void eliminarRaizConUnHijo()
{
	abb_t* abb = abb_crear(comparar_letras);
	if (!abb)
		return;
	char letras[] = {'c', 'a', 'd'};
	for (size_t i = 0; i < 2; i++) {
		if (!abb_insertar(abb, (void*)&letras[i])) {
			abb_destruir(abb);
			return;
		}
	}
	pa2m_afirmar(abb_cantidad(abb) == 2, "El abb tiene 2 elementos: 'c', 'a'");
	char* letra_quitada;
	char letra_eliminar = 'c';
	abb_quitar(abb, (void*)&letra_eliminar, (void**)&letra_quitada);
	pa2m_afirmar(letra_quitada == &letras[0], "Se quitó el elemento 'c', la dirección obtenida es: '%p' -> esperado: '%p'", letra_quitada, &letras[0]);
	pa2m_afirmar(abb_cantidad(abb) == 1, "Quedan 1 elementos en el abb");
	pa2m_afirmar(abb_obtener(abb, (void*)&letra_eliminar) == NULL, "No se encontró el elemento 'c' en el abb");

	if(!abb_insertar(abb, (void*)&letras[2])) {
		abb_destruir(abb);
		return;
	}
	pa2m_afirmar(abb_cantidad(abb) == 2, "Se agregó el elemento 'd', hay 2 elementos en el abb");

	letra_eliminar = 'a';
	abb_quitar(abb, (void*)&letra_eliminar, (void**)&letra_quitada);
	pa2m_afirmar(letra_quitada == &letras[1], "Se quitó el elemento 'a', la dirección obtenida es: '%p' -> esperado: '%p'", letra_quitada, &letras[1]);
	pa2m_afirmar(abb_cantidad(abb) == 1, "Quedan 1 elementos en el abb");
	pa2m_afirmar(abb_obtener(abb, (void*)&letra_eliminar) == NULL, "No se encontró el elemento 'a' en el abb");

	letra_eliminar = 'd';
	abb_quitar(abb, (void*)&letra_eliminar, (void**)&letra_quitada);
	pa2m_afirmar(letra_quitada == &letras[2], "Se quitó el elemento 'd', la dirección obtenida es: '%p' -> esperado: '%p'", letra_quitada, &letras[2]);
	pa2m_afirmar(abb_cantidad(abb) == 0, "No hay elementos en el abb");
	pa2m_afirmar(abb_obtener(abb, (void*)&letra_eliminar) == NULL, "No se encontró el elemento 'd' en el abb");

	abb_destruir_todo(abb, NULL);
}

void eliminarElementosConUnHijo()
{
	abb_t* abb = abb_crear(comparar_letras);
	if (!abb)
		return;
	char letras[] = {'h', 'b', 'e', 'd', 'c'};
	for (size_t i = 0; i < 5; i++) {
		if (!abb_insertar(abb, (void*)&letras[i])) {
			abb_destruir(abb);
			return;
		}
	}
	pa2m_afirmar(abb_cantidad(abb) == 5, "El abb tiene 5 elementos: 'h', 'b', 'e', 'd', 'c'");
	char* letra_quitada;
	char letra_eliminar = 'b';
	abb_quitar(abb, (void*)&letra_eliminar, (void**)&letra_quitada);
	pa2m_afirmar(letra_quitada == &letras[1], "Se quitó el elemento 'b', la dirección obtenida es: '%p' -> esperado: '%p'", letra_quitada, &letras[1]);
	pa2m_afirmar(abb_cantidad(abb) == 4, "Quedan 4 elementos en el abb");
	pa2m_afirmar(abb_obtener(abb, (void*)&letra_eliminar) == NULL, "No se encontró el elemento 'b' en el abb");

	letra_eliminar = 'e';
	abb_quitar(abb, (void*)&letra_eliminar, (void**)&letra_quitada);
	pa2m_afirmar(letra_quitada == &letras[2], "Se quitó el elemento 'e', la dirección obtenida es: '%p' -> esperado: '%p'", letra_quitada, &letras[2]);
	pa2m_afirmar(abb_cantidad(abb) == 3, "Quedan 3 elementos en el abb");
	pa2m_afirmar(abb_obtener(abb, (void*)&letra_eliminar) == NULL, "No se encontró el elemento 'e' en el abb");

	letra_eliminar = 'h';
	abb_quitar(abb, (void*)&letra_eliminar, (void**)&letra_quitada);
	pa2m_afirmar(letra_quitada == &letras[0], "Se quitó el elemento 'h', la dirección obtenida es: '%p' -> esperado: '%p'", letra_quitada, &letras[0]);
	pa2m_afirmar(abb_cantidad(abb) == 2, "Quedan 2 elementos en el abb");
	pa2m_afirmar(abb_obtener(abb, (void*)&letra_eliminar) == NULL, "No se encontró el elemento 'h' en el abb");

	char* obtenido;
	char buscar = 'c';
	obtenido = abb_obtener(abb, (void*)&buscar);
	pa2m_afirmar(obtenido == &letras[4], "Se encontró el elemento 'c', la dirección obtenida es: '%p' -> esperado: '%p'", obtenido, &letras[4]);

	buscar = 'd';
	obtenido = abb_obtener(abb, (void*)&buscar);
	pa2m_afirmar(obtenido == &letras[3], "Se encontró el elemento 'd', la dirección obtenida es: '%p' -> esperado: '%p'", obtenido, &letras[3]);

	abb_destruir_todo(abb, NULL);
}

void eliminarRaizConDosHijos()
{
	abb_t* abb = abb_crear(comparar_numeros);
	if (!abb)
		return;
	int numeros[] = {5, 2, 7};
	for (size_t i = 0; i < 3; i++) {
		if (!abb_insertar(abb, (void*)&numeros[i])) {
			abb_destruir(abb);
			return;
		}
	}
	pa2m_afirmar(abb_cantidad(abb) == 3, "Hay 3 elementos en el abb '5', '2', '7'");

	int* numero_quitado;
	int numero_eliminar = 5;
	abb_quitar(abb, (void*)&numero_eliminar, (void**)&numero_quitado);
	pa2m_afirmar(numero_quitado == &numeros[0], "Se quitó el elemento '5', la dirección obtenida es: '%p' -> esperado: '%p'", numero_quitado, &numeros[0]);
	pa2m_afirmar(abb_cantidad(abb) == 2, "Quedan 2 elementos en el abb");
	pa2m_afirmar(abb_obtener(abb, (void*)&numero_eliminar) == NULL, "No se encontró el elemento '5' en el abb");

	int* obtenido;
	int buscar = 2;
	obtenido = abb_obtener(abb, (void*)&buscar);
	pa2m_afirmar(obtenido == &numeros[1], "Se encontró el elemento '2', la dirección obtenida es: '%p' -> esperado: '%p'", obtenido, &numeros[1]);

	buscar = 7;
	obtenido = abb_obtener(abb, (void*)&buscar);
	pa2m_afirmar(obtenido == &numeros[2], "Se encontró el elemento '7', la dirección obtenida es: '%p' -> esperado: '%p'", obtenido, &numeros[2]);
	abb_destruir(abb);
}

void eliminarElementosConDosHijos()
{
	abb_t* abb = abb_crear(comparar_numeros);
	if (!abb)
		return;
	int numeros[] = {18, 15, 9, 16};
	for (size_t i = 0; i < 4; i++) {
		if (!abb_insertar(abb, (void*)&numeros[i])) {
			abb_destruir(abb);
			return;
		}
	}
	pa2m_afirmar(abb_cantidad(abb) == 4, "Nuevo abb. Hay 4 elementos en el abb '18', '15', '9', '16'");

	int* numero_quitado;
	int numero_eliminar = 15;
	abb_quitar(abb, (void*)&numero_eliminar, (void**)&numero_quitado);
	pa2m_afirmar(numero_quitado == &numeros[1], "Se quitó el elemento '15', la dirección obtenida es: '%p' -> esperado: '%p'", numero_quitado, &numeros[1]);
	pa2m_afirmar(abb_cantidad(abb) == 3, "Quedan 3 elementos en el abb");
	pa2m_afirmar(abb_obtener(abb, (void*)&numero_eliminar) == NULL, "No se encontró el elemento '15' en el abb");

	int numeros2[] = {5, 6, 7};
	for (size_t i = 0; i < 3; i++) {
		if (!abb_insertar(abb, (void*)&numeros2[i])) {
			abb_destruir(abb);
			return;
		}
	}
	pa2m_afirmar(abb_cantidad(abb) == 6, "Se agregaron: '5', '6', '7'");

	numero_eliminar = 9;
	abb_quitar(abb, (void*)&numero_eliminar, (void**)&numero_quitado);
	pa2m_afirmar(numero_quitado == &numeros[2], "Se quitó el elemento '9', la dirección obtenida es: '%p' -> esperado: '%p'", numero_quitado, &numeros[2]);
	pa2m_afirmar(abb_cantidad(abb) == 5, "Quedan 5 elementos en el abb");
	pa2m_afirmar(abb_obtener(abb, (void*)&numero_eliminar) == NULL, "No se encontró el elemento '9' en el abb");

	numero_eliminar = 7;
	abb_quitar(abb, (void*)&numero_eliminar, (void**)&numero_quitado);
	pa2m_afirmar(numero_quitado == &numeros2[2], "Se quitó el elemento '7', la dirección obtenida es: '%p' -> esperado: '%p'", numero_quitado, &numeros2[2]);
	pa2m_afirmar(abb_cantidad(abb) == 4, "Quedan 4 elementos en el abb");
	pa2m_afirmar(abb_obtener(abb, (void*)&numero_eliminar) == NULL, "No se encontró el elemento '7' en el abb");

	numero_eliminar = 6;
	abb_quitar(abb, (void*)&numero_eliminar, (void**)&numero_quitado);
	pa2m_afirmar(numero_quitado == &numeros2[1], "Se quitó el elemento '6', la dirección obtenida es: '%p' -> esperado: '%p'", numero_quitado, &numeros2[1]);
	pa2m_afirmar(abb_cantidad(abb) == 3, "Quedan 3 elementos en el abb");
	pa2m_afirmar(abb_obtener(abb, (void*)&numero_eliminar) == NULL, "No se encontró el elemento '6' en el abb");

	int* obtenido;
	int buscar = 16;
	obtenido = abb_obtener(abb, (void*)&buscar);
	pa2m_afirmar(obtenido == &numeros[3], "Se encontró el elemento '16', la dirección obtenida es: '%p' -> esperado: '%p'", obtenido, &numeros[3]);

	buscar = 5;
	obtenido = abb_obtener(abb, (void*)&buscar);
	pa2m_afirmar(obtenido == &numeros2[0], "Se encontró el elemento '5', la dirección obtenida es: '%p' -> esperado: '%p'", obtenido, &numeros2[0]);

	buscar = 18;
	obtenido = abb_obtener(abb, (void*)&buscar);
	pa2m_afirmar(obtenido == &numeros[0], "Se encontró el elemento '18', la dirección obtenida es: '%p' -> esperado: '%p'", obtenido, &numeros[0]);
	abb_destruir(abb);
}

void iteradorInternoInorden()
{
	abb_t* abb = abb_crear(comparar_numeros);
	if (!abb)
		return;
	int numeros[] = {20, 15, 9, 16, 25, 27, 19, 18};
	// recorrido: 9, 15, 16, 18, 19, 20, 25, 27
	for (size_t i = 0; i < 8; i++) {
		if (!abb_insertar(abb, (void*)&numeros[i])) {
			abb_destruir(abb);
			return;
		}
	}
	pa2m_afirmar(abb_cantidad(abb) == 8, "Nuevo abb. Hay 8 elementos: 20, 15, 9, 16, 25, 27, 19, 18");

	int sumador = 0;
	size_t cantidad;
	cantidad = abb_iterar_inorden(abb, sumar_elementos, (void*)&sumador);
	pa2m_afirmar(cantidad == 8, "Se iteró todos los elementos");
	pa2m_afirmar(sumador == 149, "La suma total debe ser: '149' -> obtenido: '%d'", sumador);

	int corte = 9;
	cantidad = abb_iterar_inorden(abb, corte_elementos, (void*)&corte);
	pa2m_afirmar(cantidad == 1, "Se cortó en la primera iteracion");

	corte = 16;
	cantidad = abb_iterar_inorden(abb, corte_elementos, (void*)&corte);
	pa2m_afirmar(cantidad == 3, "Se cortó en la tercera iteracion");

	corte = 20;
	cantidad = abb_iterar_inorden(abb, corte_elementos, (void*)&corte);
	pa2m_afirmar(cantidad == 6, "Se cortó en la sexta iteracion");

	corte = 27;
	cantidad = abb_iterar_inorden(abb, corte_elementos, (void*)&corte);
	pa2m_afirmar(cantidad == 8, "Se cortó en la octava iteracion");

	corte = 30;
	cantidad = abb_iterar_inorden(abb, corte_elementos, (void*)&corte);
	pa2m_afirmar(cantidad == 8, "No se cortó la iteración, recorrió todo el abb");

	abb_destruir_todo(abb, NULL);
}

void iteradorInternoPreorden()
{
	abb_t* abb = abb_crear(comparar_numeros);
	if (!abb)
		return;
	int numeros[] = {20, 15, 9, 16, 25, 27, 19, 18};
	// recorrido: 20, 15, 9, 16, 19, 18, 25, 27
	for (size_t i = 0; i < 8; i++) {
		if (!abb_insertar(abb, (void*)&numeros[i])) {
			abb_destruir(abb);
			return;
		}
	}
	pa2m_afirmar(abb_cantidad(abb) == 8, "Nuevo abb. Hay 8 elementos: 20, 15, 9, 16, 25, 27, 19, 18");

	int sumador = 0;
	size_t cantidad;
	cantidad = abb_iterar_preorden(abb, sumar_elementos, (void*)&sumador);
	pa2m_afirmar(cantidad == 8, "Se iteró todos los elementos");
	pa2m_afirmar(sumador == 149, "La suma total debe ser: '149' -> obtenido: '%d'", sumador);

	int corte = 20;
	cantidad = abb_iterar_preorden(abb, corte_elementos, (void*)&corte);
	pa2m_afirmar(cantidad == 1, "Se cortó en la primera iteracion");

	corte = 9;
	cantidad = abb_iterar_preorden(abb, corte_elementos, (void*)&corte);
	pa2m_afirmar(cantidad == 3, "Se cortó en la tercera iteracion");

	corte = 18;
	cantidad = abb_iterar_preorden(abb, corte_elementos, (void*)&corte);
	pa2m_afirmar(cantidad == 6, "Se cortó en la sexta iteracion");

	corte = 27;
	cantidad = abb_iterar_preorden(abb, corte_elementos, (void*)&corte);
	pa2m_afirmar(cantidad == 8, "Se cortó en la octava iteracion");

	corte = 30;
	cantidad = abb_iterar_preorden(abb, corte_elementos, (void*)&corte);
	pa2m_afirmar(cantidad == 8, "No se cortó la iteración, recorrió todo el abb");

	abb_destruir_todo(abb, NULL);
}

void iteradorIternoPostorden()
{
	abb_t* abb = abb_crear(comparar_numeros);
	if (!abb)
		return;
	int numeros[] = {20, 15, 9, 16, 25, 27, 19, 18};
	// recorrido: 9, 18, 19, 16, 15, 27, 25, 20
	for (size_t i = 0; i < 8; i++) {
		if (!abb_insertar(abb, (void*)&numeros[i])) {
			abb_destruir(abb);
			return;
		}
	}
	pa2m_afirmar(abb_cantidad(abb) == 8, "Nuevo abb. Hay 8 elementos: 20, 15, 9, 16, 25, 27, 19, 18");
	int sumador = 0;
	size_t cantidad;
	cantidad = abb_iterar_postorden(abb, sumar_elementos, (void*)&sumador);
	pa2m_afirmar(cantidad == 8, "Se iteró todos los elementos");
	pa2m_afirmar(sumador == 149, "La suma total debe ser: '149' -> obtenido: '%d'", sumador);

	int corte = 9;
	cantidad = abb_iterar_postorden(abb, corte_elementos, (void*)&corte);
	pa2m_afirmar(cantidad == 1, "Se cortó en la primera iteracion");

	corte = 19;
	cantidad = abb_iterar_postorden(abb, corte_elementos, (void*)&corte);
	pa2m_afirmar(cantidad == 3, "Se cortó en la tercera iteracion");

	corte = 27;
	cantidad = abb_iterar_postorden(abb, corte_elementos, (void*)&corte);
	pa2m_afirmar(cantidad == 6, "Se cortó en la sexta iteracion");

	corte = 20;
	cantidad = abb_iterar_postorden(abb, corte_elementos, (void*)&corte);
	pa2m_afirmar(cantidad == 8, "Se cortó en la octava iteracion");

	corte = 30;
	cantidad = abb_iterar_postorden(abb, corte_elementos, (void*)&corte);
	pa2m_afirmar(cantidad == 8, "No se cortó la iteración, recorrió todo el abb");

	abb_destruir_todo(abb, NULL);
}

void vectorizarInorden()
{
	abb_t* abb = abb_crear(comparar_numeros);
	if (!abb)
		return;
	int numeros[] = {20, 15, 9, 16, 25, 27, 19, 18};
	int recorrido_esperado[] = {9, 15, 16, 18, 19, 20, 25, 27};
	for (size_t i = 0; i < 8; i++) {
		if (!abb_insertar(abb, (void*)&numeros[i])) {
			abb_destruir(abb);
			return;
		}
	}
	pa2m_afirmar(abb_cantidad(abb) == 8, "Nuevo abb. Hay 8 elementos en el abb: 20, 15, 9, 16, 25, 27, 19, 18");

	int* vector_exacto[8];
	size_t tamaño = 8;
	size_t cantidad = abb_vectorizar_inorden(abb, (void**)&(vector_exacto), tamaño);
	pa2m_afirmar(cantidad == tamaño, "Se vectorizó los 8 elementos del abb");

	for (size_t i = 0; i < cantidad; i++) {
		pa2m_afirmar(recorrido_esperado[i] == *(vector_exacto[i]), "Elemento esperado: '%d' -> obtenido: '%d'", recorrido_esperado[i], *(vector_exacto[i]));
	}

	int* vector_menos_espacio[5];
	tamaño = 5;
	cantidad = abb_vectorizar_inorden(abb, (void**)&vector_menos_espacio, tamaño);
	pa2m_afirmar(cantidad == tamaño, "Se vectorizó 5 elementos del abb");

	for (size_t i = 0; i < cantidad; i++) {
		pa2m_afirmar(recorrido_esperado[i] == *(vector_menos_espacio[i]), "Elemento esperado: '%d' -> obtenido: '%d'", recorrido_esperado[i], *(vector_menos_espacio[i]));
	}

	int* vector_mas_espacio[10];
	tamaño = 10;
	cantidad = abb_vectorizar_inorden(abb, (void**)&vector_mas_espacio, tamaño);
	pa2m_afirmar(cantidad == 8, "Se vectorizó los 8 elementos del abb, pero faltan esos 2 elementos");

	for (size_t i = 0; i < cantidad; i++) {
		pa2m_afirmar(recorrido_esperado[i] == *(vector_mas_espacio[i]), "Elemento esperado: '%d' -> obtenido: '%d'", recorrido_esperado[i], *(vector_mas_espacio[i]));
	}

	abb_destruir(abb);
}

void vectorizarPreorden()
{
	abb_t* abb = abb_crear(comparar_numeros);
	if (!abb)
		return;
	int numeros[] = {20, 15, 9, 16, 25, 27, 19, 18};
	int recorrido_esperado[] = {20, 15, 9, 16, 19, 18, 25, 27};
	for (size_t i = 0; i < 8; i++) {
		if (!abb_insertar(abb, (void*)&numeros[i])) {
			abb_destruir(abb);
			return;
		}
	}
	pa2m_afirmar(abb_cantidad(abb) == 8, "Nuevo abb. Hay 8 elementos en el abb: 20, 15, 9, 16, 25, 27, 19, 18");

	int* vector_exacto[8];
	size_t tamaño = 8;
	size_t cantidad = abb_vectorizar_preorden(abb, (void**)&(vector_exacto), tamaño);
	pa2m_afirmar(cantidad == tamaño, "Se vectorizó los 8 elementos del abb");

	for (size_t i = 0; i < cantidad; i++) {
		pa2m_afirmar(recorrido_esperado[i] == *(vector_exacto[i]), "Elemento esperado: '%d' -> obtenido: '%d'", recorrido_esperado[i], *(vector_exacto[i]));
	}

	int* vector_menos_espacio[5];
	tamaño = 5;
	cantidad = abb_vectorizar_preorden(abb, (void**)&vector_menos_espacio, tamaño);
	pa2m_afirmar(cantidad == tamaño, "Se vectorizó 5 elementos del abb");

	for (size_t i = 0; i < cantidad; i++) {
		pa2m_afirmar(recorrido_esperado[i] == *(vector_menos_espacio[i]), "Elemento esperado: '%d' -> obtenido: '%d'", recorrido_esperado[i], *(vector_menos_espacio[i]));
	}

	int* vector_mas_espacio[10];
	tamaño = 10;
	cantidad = abb_vectorizar_preorden(abb, (void**)&vector_mas_espacio, tamaño);
	pa2m_afirmar(cantidad == 8, "Se vectorizó los 8 elementos del abb, pero faltan esos 2 elementos");

	for (size_t i = 0; i < cantidad; i++) {
		pa2m_afirmar(recorrido_esperado[i] == *(vector_mas_espacio[i]), "Elemento esperado: '%d' -> obtenido: '%d'", recorrido_esperado[i], *(vector_mas_espacio[i]));
	}

	abb_destruir(abb);
}

void vectorizarPostorden()
{
	abb_t* abb = abb_crear(comparar_numeros);
	if (!abb)
		return;
	int numeros[] = {20, 15, 9, 16, 25, 27, 19, 18};
	int recorrido_esperado[] = {9, 18, 19, 16, 15, 27, 25, 20};
	for (size_t i = 0; i < 8; i++) {
		if (!abb_insertar(abb, (void*)&numeros[i])) {
			abb_destruir(abb);
			return;
		}
	}
	pa2m_afirmar(abb_cantidad(abb) == 8, "Nuevo abb. Hay 8 elementos en el abb: 20, 15, 9, 16, 25, 27, 19, 18");

	int* vector_exacto[8];
	size_t tamaño = 8;
	size_t cantidad = abb_vectorizar_postorden(abb, (void**)&(vector_exacto), tamaño);
	pa2m_afirmar(cantidad == tamaño, "Se vectorizó los 8 elementos del abb");

	for (size_t i = 0; i < cantidad; i++) {
		pa2m_afirmar(recorrido_esperado[i] == *(vector_exacto[i]), "Elemento esperado: '%d' -> obtenido: '%d'", recorrido_esperado[i], *(vector_exacto[i]));
	}

	int* vector_menos_espacio[5];
	tamaño = 5;
	cantidad = abb_vectorizar_postorden(abb, (void**)&vector_menos_espacio, tamaño);
	pa2m_afirmar(cantidad == tamaño, "Se vectorizó 5 elementos del abb");

	for (size_t i = 0; i < cantidad; i++) {
		pa2m_afirmar(recorrido_esperado[i] == *(vector_menos_espacio[i]), "Elemento esperado: '%d' -> obtenido: '%d'", recorrido_esperado[i], *(vector_menos_espacio[i]));
	}

	int* vector_mas_espacio[10];
	tamaño = 10;
	cantidad = abb_vectorizar_postorden(abb, (void**)&vector_mas_espacio, tamaño);
	pa2m_afirmar(cantidad == 8, "Se vectorizó los 8 elementos del abb, pero faltan esos 2 elementos");

	for (size_t i = 0; i < cantidad; i++) {
		pa2m_afirmar(recorrido_esperado[i] == *(vector_mas_espacio[i]), "Elemento esperado: '%d' -> obtenido: '%d'", recorrido_esperado[i], *(vector_mas_espacio[i]));
	}

	abb_destruir(abb);
}

int main()
{
	pa2m_nuevo_grupo("============== PRUEBA INICIALIZAR ABB ===============");
	inicializarAbb();

	pa2m_nuevo_grupo("============== PRUEBA AGREGAR ELEMENTOS AL ABB ===============");
	agregarElementosDiferentes();
	agregarTodosRepetidos();
	agregarElementosVariados();

	pa2m_nuevo_grupo("============== PRUEBA OBTENER ELEMENTOS ===============");
	obtenerElementos();

	pa2m_nuevo_grupo("============== PRUEBA ELIMINAR ELEMENTOS SIN HIJOS ===============");
	eliminarRaizSinHijos();
	eliminarElementosSinHijos();

	pa2m_nuevo_grupo("============== PRUEBA ELIMINAR ELEMENTOS CON UN HIJO ===============");
	eliminarRaizConUnHijo();
	eliminarElementosConUnHijo();

	pa2m_nuevo_grupo("============== PRUEBA ELIMINAR ELEMENTOS CON DOS HIJO ===============");
	eliminarRaizConDosHijos();
	eliminarElementosConDosHijos();

	pa2m_nuevo_grupo("============== PRUEBA ITERADOR INDORDEN ==============");
	iteradorInternoInorden();

	pa2m_nuevo_grupo("============== PRUEBA ITERADOR PREORDEN ==============");
	iteradorInternoPreorden();

	pa2m_nuevo_grupo("============== PRUEBA ITERADOR POSTORDEN ==============");
	iteradorIternoPostorden();

	pa2m_nuevo_grupo("============== PRUEBA VECTORIZAR INORDEN ==============");
	vectorizarInorden();

	pa2m_nuevo_grupo("============== PRUEBA VECTORIZAR PREORDEN ==============");
	vectorizarPreorden();

	pa2m_nuevo_grupo("============== PRUEBA VECTORIZAR POSTORDEN ==============");
	vectorizarPostorden();

	return pa2m_mostrar_reporte();
}
