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
int insertarElemento(list* l, agent* item) {
    nodo* nuevo;
    nuevo = malloc(sizeof(nodo*));
    nuevo->valor = item;
    nuevo->next = NULL;

    if (l->inicio == NULL)
        l->inicio = nuevo;
    else {
        Nodo* tmp = l->inicio;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = nuevo;
    }
    return l->cant++;
}

agent* borrarElemento(list* l, agent* item) {
    if (listaVacia())
        return NULL;
    nodo* tmp;
    tmp = l->inicio;
    if (l->inicio->valor == item) {
        l->inicio = l->inicio->next;
        free(tmp);
        return item;
    }

    nodo* tmp2;
    tmp2 = tmp->next;
    while (tmp2 != NULL) {
        if (tmp2->valor == item) {
            tmp->next = tmp2->next;
            free(tmp2);
            return item;
        }
        tmp = tmp2;
        tmp2 = tmp2->next;
    }
    return NULL;
}

agent* buscarElemento(list* l,int id) {
    nodo* tmp;
    tmp = l->inicio;
    while (tmp != NULL) {
        if (tmp->valor->id == id) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

void borrarLista(list* l) {
    nodo* tmp;
    while (l->inicio != NULL) {
        tmp = l->inicio;
        l->inicio = l->inicio->next;
        free(tmp);
    }
    l->cant = 0;
}

bool listaVacia(list* l) {
    if (l->inicio == NULL)
        return true;
    return false;
}