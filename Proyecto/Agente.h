/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Agente.h
 * Author: ian
 *
 * Created on May 12, 2020, 8:09 PM
 */

#ifndef AGENTE_H
#define AGENTE_H
#include "Mapa.h"
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
struct Agente{
    int id;
    char tipo;
    char estado;
    double p_infeccion;
    double p_morir;
    double p_curarse;
    struct Mapa* mapa;
    int pos_x;
    int pos_y;
    int dx,dy;
    int dis;//direccion
    int vel;
};
typedef struct Agente agent; 

struct Agente* crearAgente(int,char,char,double,double,double,struct Mapa*,int,int);
void* moverAgente(void* agente);
bool checkCollision(struct Agente*);

#endif /* AGENTE_H */

