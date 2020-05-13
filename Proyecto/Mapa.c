#include "Mapa.h"
#include "Lista.h"

map* crearMapa(int f,int c){
    map* m;
    m = malloc(sizeof(map*));
    m->fila = f;
    m->columnas=c;
    m->tam = f*c;
    m->mapaS = malloc(f * sizeof(int *));
    for (int i=0 ; i < f ; i++) {
    	m->mapaS[i] = malloc(c * sizeof(int));
    }
    for(int i=0;i<m->fila;i++){
        for(int j=0;j<m->columnas;j++){
            //m->mapaS[i][j] = i*10+j;
            m->mapaS[i][j] = 0;
        }
    }
    m->agentes = crearLista();
    return m;
}
void dibujarMapa(map* m){
    for(int i=0;i<m->fila;i++){
        for(int j=0;j<m->columnas;j++){
            gotoxy(j*3+2,i+2);printf("%i",m->mapaS[i][j]);
        }
    }
}
