/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Simulacion.h"

void crearSimulacion(int filas,int columnas){
    mapa = crearMapa(filas,columnas);
    
    cant_rectos = 15;
    cant_estaticos = 0;
    cant_aleatorios = 0;
    cantidadAgentes = 0;
    
    ag_hilos = malloc(filas * columnas *sizeof(pthread_t)*50);
}

void run(int time){
    crearAgentes();
}
void crearAgentes(){
    for(int i=0;i<cant_rectos-2;i++){
        int dx,dy;
        bool ban = true;
        while(ban){
            dx = (3+rand()% mapa->fila -3);
            dy = (3+ rand()%  mapa->columnas -3 );
            if(mapa->mapaS[dx][dy] == 0){
                ban = false;
            }
        }
        struct Agente *ag= crearAgente(1,'R','v', 99.5, 99.5 ,99.0 ,mapa,dx,dy);
        mapa->mapaS[dx][dy] = 1; //1 rectos
        pthread_create(&(ag_hilos[cantidadAgentes++]),NULL,moverAgente,ag);
        
    }
    for(int i=0;i<2;i++){
        int dx,dy;
        bool ban = true;
        while(ban){
            dx = (3+rand()% mapa->fila -3);
            dy = (3+ rand()%  mapa->columnas -3 );
            if(mapa->mapaS[dx][dy] == 0){
                ban = false;
            }
        }
        struct Agente *ag= crearAgente(5,'R','e', 99.5, 99.5 ,99.0 ,mapa,dx,dy);
        mapa->mapaS[dx][dy] = 5; //1 rectos
        pthread_create(&(ag_hilos[cantidadAgentes++]),NULL,moverAgente,ag);
        
    }
    for(int i=0;i<cant_estaticos;i++){
        int dx,dy;
        bool ban = true;
        while(ban){
            dx = (3+rand()% mapa->fila -3);
            dy = (3+ rand()%  mapa->columnas -3 );
            if(mapa->mapaS[dx][dy] == 0){
                ban = false;
            }
        }
        struct Agente *ag;
        ag=crearAgente(2,'Q','v',99.0,99.0,99.0,mapa,dx,dy);
        mapa->mapaS[dx][dy] = 2; //1 rectos

    }
    for(int i=0;i<cant_aleatorios;i++){
        int dx,dy;
        bool ban = true;
        while(ban){
            dx = (3+rand()% mapa->fila -3);
            dy = (3+ rand()%  mapa->columnas -3 );
            if(mapa->mapaS[dx][dy] == 0){
                ban = false;
            }
        }
        struct Agente *ag= crearAgente(3,'A','v', 0.0, 0.0 ,0.0 ,mapa,dx,dy);
        mapa->mapaS[dx][dy] = 3; //3 aleatorios
        pthread_create(&(ag_hilos[cantidadAgentes++]),NULL,moverAgente,ag);
    }
    for(int i=0;i<(cantidadAgentes);i++){
        pthread_join(ag_hilos[i],NULL);
    }
}
