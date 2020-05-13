/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mapa.h
 * Author: ian
 *
 * Created on May 12, 2020, 8:27 PM
 */

#ifndef MAPA_H
#define MAPA_H
#include <stdio.h>
#include <stdlib.h>
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
typedef struct Mapa{
    int tam;
    int fila;
    int columnas;
    int **mapaS;
    list* agentes;
} map;
map* crearMapa(int,int);
void dibujarMapa(map*);

#endif /* MAPA_H */

