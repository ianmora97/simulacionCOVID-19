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
#include <ncurses.h>
#include <unistd.h>
#include "Lista.h"

struct Mapa {
    int tam;
    int fila;
    int columnas;
    int **mapaS;
};
typedef struct Mapa map;

struct Mapa* crearMapa(int,int);
void dibujarMapa(struct Mapa*);

#endif /* MAPA_H */

