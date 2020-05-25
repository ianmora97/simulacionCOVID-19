/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Simulacion.h"

void crearSimulacion(int filas,int columnas){
    mapa = crearMapa(filas,columnas);
    
    cant_rectos = 0;
    cant_estaticos = 0;
    cant_aleatorios = 0;
    cant_estacionales = 0;
    
    cantidadAgentes = 0;
    
    ag_hilos = malloc(filas * columnas *sizeof(pthread_t)*500);
}

void run(int time){
    
}
void crearAgentes(int cont_grupos,int cont_tipos,int cont_vel,int cont_est, int* gv,int* tv,int* vv,char* ev){
    clear();
    for(int i=0;i<cont_grupos;i++){
        switch(tv[i]){
            case 1: cant_rectos += gv[i]; break;
            case 2: cant_estacionales += gv[i]; break;
            case 3: cant_aleatorios += gv[i]; break;
            case 4: cant_estaticos += gv[i]; break;
        }
        
    }
    printf("R:%i E:%i A:%i Q:%i",cant_rectos,cant_estacionales,cant_aleatorios,cant_estaticos);
    
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
        move(5,60+1); addch('R');
        usleep(100000);
        refresh();
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
        move(6,60+1); addch('R');
        usleep(100000);
        refresh();
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
        pthread_create(&(ag_hilos[cantidadAgentes++]),NULL,checkEstaticos,ag);
        move(7,60+1); addch('Q');
        usleep(100000);
        refresh();
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
        struct Agente *ag= crearAgente(3,'A','v', 99.0, 99.0 ,99.0 ,mapa,dx,dy);
        mapa->mapaS[dx][dy] = 3; //3 aleatorios
        pthread_create(&(ag_hilos[cantidadAgentes++]),NULL,moverAgente,ag);
        move(8,60+1); addch('A');
        usleep(100000);
        refresh();
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
        struct Agente *ag= crearAgente(7,'A','v', 99.0, 99.0 ,99.0 ,mapa,dx,dy);
        mapa->mapaS[dx][dy] = 7; //3 aleatorios
        pthread_create(&(ag_hilos[cantidadAgentes++]),NULL,moverAgente,ag);
        move(9,60+1); addch('A');
        usleep(100000);
        refresh();
    }
    for(int i=0;i<(cantidadAgentes);i++){
        pthread_join(ag_hilos[i],NULL);
    }
}
