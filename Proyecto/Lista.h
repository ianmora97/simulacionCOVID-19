/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lista.h
 * Author: ian
 *
 * Created on May 12, 2020, 11:08 PM
 */

#ifndef LISTA_H
#define LISTA_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct Nodo{
    agent* valor;
    nodo* next;
} nodo;

typedef struct Lista {
    nodo* inicio;
    int cant;
} list;

list* crearLista();
int insertarElemento(list* l, agent* item);
bool listaVacia(list* l);
agent* borrarElemento(list* l, agent* item);
void borrarLista(list* l);
agent* buscarElemento(list* l,int item);
#endif /* LISTA_H */

