#include "Agente.h"

struct Agente* crearAgente(int i, char t, char e, double pi, double pm, double pc, struct Mapa* ma, int px, int py) {
    struct Agente* ag;
    ag = malloc(sizeof (struct Agente*)*50);
    ag->id = i;
    ag->estado = e;
    ag->tipo = t;
    ag->p_infeccion = pi;
    ag->p_morir = pm;
    ag->p_curarse = pc;
    ag->mapa = ma;
    ag->pos_x = px;
    ag->pos_y = py;
    ag->dx = 1;
    ag->dy = 1;
    ag->dis = (1 + rand() % 4);
    switch (ag->dis) {
        case 1: ag->dx = 1;
            break;
        case 2: ag->dx = -1;
            break;
        case 3: ag->dy = 1;
            break;
        case 4: ag->dy = -1;
            break;
    }
    ag->vel = (5 + rand() % 50);
    return ag;
}

void* moverAgente(void* agente) {
    struct Agente* ag = (struct Agente*) agente;
    int ant_x, ant_y;
    while (1) {
        //if ((ag->pos_x > 2 && ag->pos_x < ag->mapa->columnas) && (ag->pos_y > 2 && ag->pos_y < ag->mapa->fila)) {
            if (ag->tipo == 'A') {

            } else if (ag->tipo == 'R') { //rectos
                if (ag->dis == 1) { //moviendose hacia abajo
                    ant_x = ag->pos_x;
                    ant_y = ag->pos_y;
                    
                    dibujarMapa(ag->mapa);
                    if (ag->pos_x + ag->dx == ag->mapa->fila) {
                        ag->dx = -1;
                        ag->dis = 2; //hacia arriba
                    }
                    ag->pos_x += ag->dx;
                    if(!checkCollision(ag)){
                        pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                        ag->mapa->mapaS[ag->pos_x][ag->pos_y] = 1;
                        pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                        pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
                        if(ag->mapa->mapaS[ant_x][ant_y] != 2){
                            ag->mapa->mapaS[ant_x][ant_y] = 0;
                        }
                        pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
                    }
                    dibujarMapa(ag->mapa);
                } else if (ag->dis == 2) { //moviendose hacia arriba
                    ant_x = ag->pos_x;
                    ant_y = ag->pos_y;
                    
                    dibujarMapa(ag->mapa);
                    if (ag->pos_x + ag->dx == 0) {
                        ag->dx = 1;
                        ag->dis = 1; //hacia abajo
                    }
                    ag->pos_x += ag->dx;
                    if(!checkCollision(ag)){
                        pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                        ag->mapa->mapaS[ag->pos_x][ag->pos_y] = 1;
                        pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                        pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
                        if(ag->mapa->mapaS[ant_x][ant_y] != 2){
                            ag->mapa->mapaS[ant_x][ant_y] = 0;
                        }
                        pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
                    }
                    dibujarMapa(ag->mapa);
                } else if (ag->dis == 3) { //moviendose hacia derecha
                    ant_x = ag->pos_x;
                    ant_y = ag->pos_y;
                    
                    dibujarMapa(ag->mapa);
                    if (ag->pos_y + ag->dy == ag->mapa->columnas) {
                        ag->dy = -1;
                        ag->dis = 4; //hacia izquierda
                    }
                    ag->pos_y += ag->dy;
                    if(!checkCollision(ag)){
                        pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                        ag->mapa->mapaS[ag->pos_x][ag->pos_y] = 1;
                        pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                        pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
                        if(ag->mapa->mapaS[ant_x][ant_y] != 2){
                            ag->mapa->mapaS[ant_x][ant_y] = 0;
                        }
                        pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
                    }
                    dibujarMapa(ag->mapa);
                } else if (ag->dis == 4) { //moviendose hacia izquierda
                    ant_x = ag->pos_x;
                    ant_y = ag->pos_y;
                    
                    dibujarMapa(ag->mapa);
                    if (ag->pos_y + ag->dy == 0) {
                        ag->dy = 1;
                        ag->dis = 3; //hacia derecha
                    }
                    ag->pos_y += ag->dy;
                    if(!checkCollision(ag)){
                        pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                        ag->mapa->mapaS[ag->pos_x][ag->pos_y] = 1;
                        pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                        
                        pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
                        if(ag->mapa->mapaS[ant_x][ant_y] != 2){
                            ag->mapa->mapaS[ant_x][ant_y] = 0;
                        }
                        pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
                    }
                    dibujarMapa(ag->mapa);
                }
                

            } else if (ag->tipo == 'E') {

            } else { //
                //doNothing
            }
        }

    //}
}
bool checkCollision(struct Agente* ag){
    if(ag->mapa->mapaS[ag->pos_x][ag->pos_y] == 2){
        switch(ag->dis){
            case 1: ag->dx = -1; ag->dis = 2; break;
            case 2: ag->dx = 1; ag->dis = 1; break;
            case 3: ag->dy = -1; ag->dis = 4; break;
            case 4: ag->dy = 1; ag->dis = 3; break;
            default: break;
        }
        return true;
    }
    return false;
}