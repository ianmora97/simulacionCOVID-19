/*
 * Esta implementacion de lista, es una implementacion hecha en el curso de 
 * Estructuras Discretas
 */

#include "Lista.h"
#include "Agente.h"

list* crearLista(){
    list* l;
    l = malloc(sizeof(list*));
    l->cant = 0;
    l->inicio = NULL;
    return l;
}
int insertarElemento(list* l,struct agent* item) {
    nodo* nuevo;
    nuevo = malloc(sizeof(nodo*));
    nuevo->valor = item;
    nuevo->next = NULL;

    if (l->inicio == NULL)
        l->inicio = nuevo;
    else {
        nodo* tmp = l->inicio;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = nuevo;
    }
    return l->cant++;
}


bool listaVacia(list* l) {
    if (l->inicio == NULL)
        return true;
    return false;
}