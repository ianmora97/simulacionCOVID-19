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
#include <stdio.h>
#include <stdlib.h>

typedef struct Agente{
    int id;
    char tipo;
    char estado;
    double p_infeccion;
    double p_morir;
    double p_curarse;
    map *mapa;
    int pos_x;
    int pos_y;
} agent; 

agent* crearAgente(int,char,char,double,double,double,map*,int,int);
void* moverAgente(agent*);

#endif /* AGENTE_H */

