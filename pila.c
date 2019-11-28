#include "pila.h"
#include <stdlib.h>
#define tam_inicial 10
/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t* pila_crear(void){
    pila_t* pila = malloc(sizeof(pila_t));
    if (pila == NULL) {
        return NULL;
    }
    pila->datos = malloc(tam_inicial * sizeof(void*));
    if (tam_inicial > 0 && pila->datos == NULL) {
        free(pila);
        return NULL;
    }
    pila->cantidad = 0;
    pila->capacidad = tam_inicial;
    return pila;
}
void pila_destruir(pila_t *pila){
    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
    return pila->cantidad == 0;
}

bool redimensionar_pila(pila_t *pila, size_t tam_nuevo){
    void* datos_nuevo = realloc(pila->datos,  tam_nuevo * sizeof(void*));
    if (datos_nuevo == NULL) {
        return false;
    } else {
    pila->datos = datos_nuevo;
    pila->capacidad = tam_nuevo;
    return true;
    }
}

bool pila_apilar(pila_t *pila, void* valor){

    if (pila->cantidad >= pila->capacidad){
        size_t tam_nuevo = pila->capacidad*2;
        bool pudo_redimensionar =  redimensionar_pila(pila, tam_nuevo);
        if (pudo_redimensionar ==false){
            return false;
        }
    }       
    pila->datos[pila->cantidad] = valor;
    pila->cantidad += 1;
    return true;

}
void* pila_ver_tope(const pila_t *pila){
    if (pila->cantidad == 0){
        return NULL;
    } 
    return pila->datos[pila->cantidad -1];

}

void* pila_desapilar(pila_t *pila){
    if (pila->cantidad == 0){
        return NULL;
    } 
    if (pila->cantidad <= (pila->capacidad/4)){
        size_t tam_nuevo = pila->capacidad /2;
        redimensionar_pila(pila, tam_nuevo);
    }
    pila->cantidad -= 1;
    return pila->datos[pila->cantidad];
}

// ...
