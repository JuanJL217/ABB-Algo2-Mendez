#include "pa2m.h"
#include "src/abb.h"

int comparar_numeros(void* a, void* b)
{
	return *(int*)a - *(int*)b;
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

void agregarMismoElemento()
{
	return;
}

bool mostrar_numeros(void* elemento, void* nada)
{	
	printf("%d ", *(int*)elemento);
	if (*(int*)elemento == 2)
		return false;
	return true;
}

void iteradorIternoSinCorte()
{
	return;
}

void iteradorIternoConCorte()
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
	size_t cantidad = abb_iterar_postorden(abb, mostrar_numeros, NULL);
	pa2m_afirmar(cantidad == 5, "Se recorrió solo 5 elementos");
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

	pa2m_nuevo_grupo("============== PRUEBA ITERADOR POSTORDEN ==============");
	iteradorIternoSinCorte();
	iteradorIternoConCorte();
	// pa2m_nuevo_grupo("============== PRUEBA AGREGAR MISMO ELEMENTO ===============");
	// agregarMismoElemento();

	return pa2m_mostrar_reporte();
}
