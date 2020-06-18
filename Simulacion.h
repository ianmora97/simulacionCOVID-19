/* 
 * File:   Simulacion.h
 * Author: ian
 *
 * Created on May 12, 2020, 8:42 PM
 */

#ifndef SIMULACION_H
#define SIMULACION_H
#include <ncurses.h>
#include <unistd.h>
#include <pthread.h>
#include "Mapa.h"
#include "Agente.h"
#include "Lista.h"

/* Variables del programa*/
struct Mapa* mapa;
pthread_t *ag_hilos;
pthread_t *reporte;
int cantidadAgentes;
int cant_rectos, cant_estaticos, cant_aleatorios,cant_estacionales;
int cant_rectos_e, cant_estaticos_e, cant_aleatorios_e,cant_estacionales_e; 
int *dir_x, *dir_y;
double matriz[4][4];

void crearSimulacion(int,int,double m_pro[4][4],int p_muerte, int t_curarse,int t_morir,bool recontagio);
void crearParedes(int, int*);
void *imprimirReporte(void* arg);
void crearAgentes(int,int,int,int, int*,int*,int*,char*);
#endif /* SIMULACION_H */

