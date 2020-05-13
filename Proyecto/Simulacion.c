/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Simulacion.h"

struct ListaArchivo* crearListaA(){
    struct ListaArchivo* l;
    l = malloc(sizeof(struct ListaArchivo*));
    l->cant = 0;
    l->inicio = NULL;
    return l;
}
int insertarElementoA(struct ListaArchivo* l, struct GruposAgentes* item) {
    struct NodoArchivo* nuevo;
    nuevo = malloc(sizeof(struct NodoArchivo*));
    nuevo->ga = item;
    nuevo->next = NULL;

    if (l->inicio == NULL)
        l->inicio = nuevo;
    else {
        struct NodoArchivo* tmp = l->inicio;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = nuevo;
    }
    return l->cant++;
}
bool listaVaciaA(struct ListaArchivo* l) {
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