/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Simulacion.h"

a_list* crearLista(){
    a_list* l;
    l = malloc(sizeof(a_list*));
    l->cant = 0;
    l->inicio = NULL;
    return l;
}
int insertarElemento(a_list* l, g_agent* item) {
    nodoA* nuevo;
    nuevo = malloc(sizeof(nodoA*));
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
bool listaVacia(a_list* l) {
    if (l->inicio == NULL)
        return true;
    return false;
}

void crearSimulacion(int filas,int columnas){
    mapa = crearMapa(filas,columnas);
    cantidadAgentes = 50;
}

void run(int time){
    dibujarMapa(mapa);   
}
void crearAgentes(){
    
}