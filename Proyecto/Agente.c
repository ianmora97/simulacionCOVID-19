#include "Agente.h"

struct agent* crearAgente(int i,char t,char e,double pi,double pm,double pc,struct map* mapa, int px, int py){
    struct Agente* ag;
    ag = malloc(sizeof(struct agent*));
    ag->id = i;
    ag->estado = e;
    ag->tipo = t;
    ag->p_infeccion=pi;
    ag->p_morir = pm;
    ag->p_curarse=pc;
    ag->mapa = mapa;
    ag->pos_x = px;
    ag->pos_y = py;
    return ag;
}
void* moverAgente(struct Agente* ag){
    if(ag->tipo == 'A'){
        
    }
    else if(ag->tipo == 'R'){
        
    }
    else if(ag->tipo == 'E'){
        
    }
    else{ //
        //doNothing
    }
}