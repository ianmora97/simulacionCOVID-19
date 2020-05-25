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
            int r_dx = random() % 6; //genero una probabilidad de cambio de direccion para x y y
            int r_dy = random() % 6;

            if (r_dx == 2) { //si cae lo cambio
                ag->dx = ag->dx == 1 ? -1 : 1;
            }
            if (r_dy == 2) {
                ag->dy = ag->dy == 1 ? -1 : 1;
            }

            if (ag->pos_y + ag->dy == ag->mapa->columnas) { //si al cambiarlo toca los extremos cambia la direccion
                ag->dy = -1;
            } else if (ag->pos_y + ag->dy == 0) {
                ag->dy = 1;
            }
            if (ag->pos_x + ag->dx == ag->mapa->fila) {
                ag->dx = -1;
            } else if (ag->pos_x + ag->dx == 0) {
                ag->dx = 1;
            }

            ant_x = ag->pos_x;
            ant_y = ag->pos_y;
            switch (ag->dx) {
                case 1:ag->dis = 1;
                    break;
                case -1:ag->dis = 2;
                    break;
            }
            switch (ag->dy) {
                case 1:ag->dis = 3;
                    break;
                case -1:ag->dis = 4;
                    break;
            }
            if (checkCollision(ag)) {
                pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
                if (ag->mapa->mapaS[ant_x][ant_y] != 2) {
                    ag->mapa->mapaS[ant_x][ant_y] = 0;
                }
                pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
            } else {
                ag->pos_x += ag->dx;
                ag->pos_y += ag->dy;
                pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                ag->mapa->mapaS[ag->pos_x][ag->pos_y] = ag->id;
                pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);

                pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
                if (ag->mapa->mapaS[ant_x][ant_y] != 2) {
                    ag->mapa->mapaS[ant_x][ant_y] = 0;
                }
                pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);

            }




        } else if (ag->tipo == 'R') { //rectos
            if (ag->dis == 1) { //moviendose hacia abajo
                ant_x = ag->pos_x;
                ant_y = ag->pos_y;

                if (ag->pos_x + ag->dx == ag->mapa->fila) {
                    ag->dx = -1;
                    ag->dis = 2; //hacia arriba
                }

                if (checkCollision(ag)) {


                    pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
                    if (ag->mapa->mapaS[ant_x][ant_y] != 2) {
                        ag->mapa->mapaS[ant_x][ant_y] = 0;
                    }
                    pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);

                } else {
                    ag->pos_x += ag->dx;
                    pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                    ag->mapa->mapaS[ag->pos_x][ag->pos_y] = ag->id;
                    pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);

                    pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
                    if (ag->mapa->mapaS[ant_x][ant_y] != 2) {
                        ag->mapa->mapaS[ant_x][ant_y] = 0;
                    }
                    pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
                }

            } else if (ag->dis == 2) { //moviendose hacia arriba
                ant_x = ag->pos_x;
                ant_y = ag->pos_y;


                if (ag->pos_x + ag->dx == 0) {
                    ag->dx = 1;
                    ag->dis = 1; //hacia abajo
                }

                if (!checkCollision(ag)) {
                    ag->pos_x += ag->dx;
                    pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                    ag->mapa->mapaS[ag->pos_x][ag->pos_y] = ag->id;
                    pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                    pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
                    if (ag->mapa->mapaS[ant_x][ant_y] != 2) {
                        ag->mapa->mapaS[ant_x][ant_y] = 0;
                    }
                    pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
                } else {


                    pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
                    if (ag->mapa->mapaS[ant_x][ant_y] != 2) {
                        ag->mapa->mapaS[ant_x][ant_y] = 0;
                    }
                    pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);

                }

            } else if (ag->dis == 3) { //moviendose hacia derecha
                ant_x = ag->pos_x;
                ant_y = ag->pos_y;


                if (ag->pos_y + ag->dy == ag->mapa->columnas) {
                    ag->dy = -1;
                    ag->dis = 4; //cambia hacia izquierda
                }

                if (!checkCollision(ag)) {
                    ag->pos_y += ag->dy;
                    pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                    ag->mapa->mapaS[ag->pos_x][ag->pos_y] = ag->id;
                    pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);

                    pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
                    if (ag->mapa->mapaS[ant_x][ant_y] != 2) {
                        ag->mapa->mapaS[ant_x][ant_y] = 0;
                    }
                    pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
                } else {
                    pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
                    if (ag->mapa->mapaS[ant_x][ant_y] != 2) {
                        ag->mapa->mapaS[ant_x][ant_y] = 0;
                    }
                    pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
                }
            } else if (ag->dis == 4) { //moviendose hacia izquierda
                ant_x = ag->pos_x;
                ant_y = ag->pos_y;

                if (ag->pos_y + ag->dy == 0) {
                    ag->dy = 1;
                    ag->dis = 3; //hacia derecha
                }

                if (!checkCollision(ag)) {
                    ag->pos_y += ag->dy;
                    pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                    ag->mapa->mapaS[ag->pos_x][ag->pos_y] = ag->id;
                    pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);

                    pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
                    if (ag->mapa->mapaS[ant_x][ant_y] != 2) {
                        ag->mapa->mapaS[ant_x][ant_y] = 0;
                    }
                    pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
                } else {

                    pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);
                    if (ag->mapa->mapaS[ant_x][ant_y] != 2) {
                        ag->mapa->mapaS[ant_x][ant_y] = 0;
                    }
                    pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ant_x][ant_y]);

                }
            }


        } else if (ag->tipo == 'E') {

        }
        usleep(500000 * 10 / ag->vel);
        dibujarMapa(ag->mapa);
    }

    //}
}

void *checkEstaticos(void* agente) {
    struct Agente* ag = (struct Agente*) agente;
    while (1) {
        checkCollision(ag);
        pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
        ag->mapa->mapaS[ag->pos_x][ag->pos_y] = ag->id;
        pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
    }
}

bool checkCollision(struct Agente* ag) {
    if (ag->id == 1 || ag->id == 5) { //recto
        if (ag->dis == 1 || ag->dis == 2) {
            if (ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] != 0) {
                int numeroMantiza = rand() % 100;
                int numeroExponente = rand() % 10;
                double p = numeroMantiza + numeroExponente * 0.1;
                if (ag->p_infeccion > p) {
                    if ((ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] == 5 ||
                            ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] == 7 ||
                            ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] == 8) && ag->id == 1) {
                        ag->estado = ENFERMO;
                        pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ag->pos_x + ag->dx][ag->pos_y]);
                        ag->id = 5;
                        pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ag->pos_x + ag->dx][ag->pos_y]);
                    }
                }
                switch (ag->dis) {
                    case 1: ag->dx = -1;
                        ag->dis = 2;
                        return true;
                    case 2: ag->dx = 1;
                        ag->dis = 1;
                        return true;
                }
            }
        } else if (ag->dis == 3 || ag->dis == 4) {
            if (ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] != 0) {
                int numeroMantiza = rand() % 100;
                int numeroExponente = rand() % 10;
                double p = numeroMantiza + numeroExponente * 0.1;
                if (ag->p_infeccion > p) {
                    if ((ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] == 5 ||
                            ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] == 7 ||
                            ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] == 8) && ag->id == 1) {
                        ag->estado = 'i';
                        pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y + ag->dy]);
                        ag->id = 5;
                        pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y + ag->dy]);
                    }
                }
                switch (ag->dis) {
                    case 3: ag->dy = -1;
                        ag->dis = 4;
                        return true;
                    case 4: ag->dy = 1;
                        ag->dis = 3;
                        return true;
                }
            }
        }

    } else if (ag->id == 3 || ag->id == 7) { //aleatorio
        if (ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] != 0) {

            int numeroMantiza = rand() % 100;
            int numeroExponente = rand() % 10;
            double p = numeroMantiza + numeroExponente * 0.1;
            if (ag->p_infeccion > p) {
                if ((ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] == 5 ||
                        ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] == 7 ||
                        ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] == 8)) {
                    if (ag->id == 3) {
                        ag->estado = ENFERMO;
                        pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ag->pos_x + ag->dx][ag->pos_y]);
                        ag->id = 7;
                        pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ag->pos_x + ag->dx][ag->pos_y]);

                    }
                }

            }
            ag->dy = 1;
            if (ag->pos_y + ag->dy == ag->mapa->columnas) { //si al cambiarlo toca los extremos cambia la direccion
                ag->dy = -1;
            } else if (ag->pos_y + ag->dy == 0) {
                ag->dy = 1;
            }
            if (ag->pos_x + ag->dx == ag->mapa->fila) {
                ag->dx = -1;
            } else if (ag->pos_x + ag->dx == 0) {
                ag->dx = 1;
            }
            return true;
        } else if (ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->pos_y] != 0) {
            int numeroMantiza = rand() % 100;
            int numeroExponente = rand() % 10;
            double p = numeroMantiza + numeroExponente * 0.1;
            if (ag->p_infeccion > p) {
                if ((ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] == 5 ||
                        ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] == 7 ||
                        ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] == 8)) {
                    if (ag->id == 3) {
                        ag->estado = ENFERMO;
                        pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y + ag->dy]);
                        ag->id = 7;
                        pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y + ag->dy]);
                    }
                }

            }
            ag->dx = 1;
            if (ag->pos_y + ag->dy == ag->mapa->columnas) { //si al cambiarlo toca los extremos cambia la direccion
                ag->dy = -1;
            } else if (ag->pos_y + ag->dy == 0) {
                ag->dy = 1;
            }
            if (ag->pos_x + ag->dx == ag->mapa->fila) {
                ag->dx = -1;
            } else if (ag->pos_x + ag->dx == 0) {
                ag->dx = 1;
            }
            return true;
        }
    } else if (ag->id == 2) {
        if (ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y + ag->dy] != 0 ||
                ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] != 0 ||
                ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] != 0) {
            int numeroMantiza = rand() % 100;
            int numeroExponente = rand() % 10;
            double p = numeroMantiza + numeroExponente * 0.1;
            if (ag->p_infeccion > p) {
                if (ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y + ag->dy] == 5 ||
                        ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y + ag->dy] == 7 ||
                        ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y + ag->dy] == 8) {
                    ag->estado = ENFERMO;
                    pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                    ag->id = 6;
                    pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                }
                else if (ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] == 5 ||
                        ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] == 7 ||
                        ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] == 8) {
                    ag->estado = ENFERMO;
                    pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                    ag->id = 6;
                    pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                }
                else if (ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] == 5 ||
                        ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] == 7 ||
                        ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] == 8) {
                    ag->estado = ENFERMO;
                    pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                    ag->id = 6;
                    pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                }
            }

            return true;
        }
    }

    return false;
}

/*
    if (ag->mapa->mapaS[ag->pos_x][ag->pos_y] != 0) {
        switch (ag->dis) {
            case 1: ag->dx = -1;
                ag->dis = 2;
                break;
            case 2: ag->dx = 1;
                ag->dis = 1;
                break;
            case 3: ag->dy = -1;
                ag->dis = 4;
                break;
            case 4: ag->dy = 1;
                ag->dis = 3;
                break;
            default: break;
        }
        return true;
    }
 */
