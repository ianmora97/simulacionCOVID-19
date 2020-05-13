/* 
 * File:   Simulacion.h
 * Author: ian
 *
 * Created on May 12, 2020, 8:42 PM
 */

#ifndef SIMULACION_H
#define SIMULACION_H
#include "Mapa.h"
#include "Agente.h"
#include "Lista.h"
/*Para leer Los archivos*/
typedef struct GruposAgentes{
    int cantAg;
    int tipo;
    int vel_max;
    int vel_min;
    char estado;
} g_agent;
typedef struct NodoArchivo{
    struct GruposAgentes* ga;
    struct NodoArchivo* next;
} nodoA;

typedef struct ListaArchivo {
    struct NodoArchivo* inicio;
    int cant;
} a_list;

/*!Para leer Los archivos!*/

/* Variables del programa*/
map* mapa;
int cantidadAgentes;



/*Metodos de ListaArchivo*/
struct ListaArchivo* crearListaA();
int insertarElementoA(struct ListaArchivo* l, struct GruposAgentes* item);
bool listaVaciaA(struct ListaArchivo* l);
/*!Metodos de ListaArchivo*/

void crearSimulacion(int,int);
void run();
void crearAgentes();
#endif /* SIMULACION_H */

