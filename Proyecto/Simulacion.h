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
int cantidadAgentes;
int cant_rectos, cant_estaticos, cant_aleatorios; 
int *dir_x, *dir_y;

void crearSimulacion(int,int);
void run(int time);
void crearAgentes();
#endif /* SIMULACION_H */

