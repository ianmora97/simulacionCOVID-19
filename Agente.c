#include "Agente.h"

struct Agente* crearAgente(int i, char t, char e, double pi, double pm, double pc, struct Mapa* ma, int px, int py, int placa) {
    struct Agente* ag;
    ag = malloc(sizeof (struct Agente*)*5000);
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
    ag->placa = placa;
    return ag;
}

void* moverAgente(void* agente) {
    struct Agente* ag = (struct Agente*) agente;
    int dx_r = 0, dy_r = 0;
    if (ag->tipo == 'E') {
        ag->dis = 1;
    }

    int pos = 0;
    int dx_pos[10]; //para las posiciones del agente de ruta
    int dy_pos[10];
    for (int i = 0; i < 10; i++) {
        dx_pos[i] = rand() % 2;
    }
    for (int i = 0; i < 10; i++) {
        dy_pos[i] = rand() % 2;
    }
    int ant_x, ant_y; //posicion anterior, al que hay que poner en 0
    while (1) {
        //if ((ag->pos_x > 2 && ag->pos_x < ag->mapa->columnas) && (ag->pos_y > 2 && ag->pos_y < ag->mapa->fila)) {
        if (ag->tipo == 'A') {
            ant_x = ag->pos_x;
            ant_y = ag->pos_y;
            int r_dx = random() % 10; //genero una probabilidad de cambio de direccion para x y y
            int r_dy = random() % 10;

            if (r_dx == 0) { //si la probabilidad es 2 lo cambio
                ag->dx = ag->dx == 1 ? -1 : 1;
            }
            if (r_dy == 0) {
                ag->dy = ag->dy == 1 ? -1 : 1;
            }

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

            if (!checkCollision(ag)) {
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
            } else {
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
            if (ag->pos_y + ag->dy == ag->mapa->columnas) { //si al cambiarlo toca los extremos cambia la direccion
                dy_r = 9;
                dx_r = 9;
            } else if (ag->pos_y + ag->dy == 0) {
                dy_r = 0;
                dx_r = 0;
            }
            if (ag->pos_x + ag->dx == ag->mapa->fila) {
                dy_r = 9;
                dx_r = 9;
            } else if (ag->pos_x + ag->dx == 0) {
                dy_r = 0;
                dx_r = 0;
            }

            if (ag->dis) { //dis =1 para arriba derecha
                pos = 1;
                ag->dx = dx_pos[dx_r++];
                ag->dy = dy_pos[dy_r++];
                if (dx_r == 10) {
                    ag->dis = 0;
                    dx_r--;
                    dy_r--;
                }
                ant_x = ag->pos_x;
                ant_y = ag->pos_y;
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
            } else { //dis = 0 para abajo izquierda
                pos = -1;
                ag->dx = dx_pos[dx_r--] * -1;
                ag->dy = dy_pos[dy_r--] * -1;
                if (dx_r == -1) {
                    ag->dis = 1;
                    dx_r++;
                    dy_r++;
                }
                ant_x = ag->pos_x;
                ant_y = ag->pos_y;
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

void* p_muerte(void *agente) {
    struct Agente* ag = (struct Agente*) agente;
    int time = 0;
    int numeroMantiza = rand() % 100;
    int numeroExponente = rand() % 10;
    double p = numeroMantiza + numeroExponente * 0.1;
    if (ag->p_morir + p > 100) {
        time = 20; //se muere
    } else {
        time = 18; //se cura
    }
    for (int i = 0; i < time; i++) {
        usleep(1000000);
    }
    if (ag->tipo == 'R') {
        if (time == 20) {
            ag->id = 0;
            ag->estado = MUERTO;
        } else {
            ag->estado = CURADO;
            ag->id = 9;
        }
    } else if (ag->tipo == 'Q') {
        if (time == 20) {
            ag->id = 0;
            ag->estado = MUERTO;
        } else {
            ag->estado = CURADO;
            ag->id = 10;
        }
    } else if (ag->tipo == 'A') {
        if (time == 20) {
            ag->id = 0;
            ag->estado = MUERTO;
        } else {
            ag->estado = CURADO;
            ag->id = 11;
        }
    } else if (ag->tipo == 'E') {
        if (time == 20) {
            ag->id = 0;
            ag->estado = MUERTO;
        } else {
            ag->estado = CURADO;
            ag->id = 12;
        }
    }
    generarReporte(ag);
}

void *generarReporte(void *agente) {
    struct Agente* ag = (struct Agente*) agente;
    switch (ag->estado) {
        case CURADO:
            ag->mapa->v_cu[ag->mapa->contadorCurados++] = 1;
            ag->mapa->v_en[ag->mapa->contadorEnfermos++] = 0;
            ag->mapa->v_sa[ag->mapa->contadorSanos++] = 0;
            ag->mapa->v_mu[ag->mapa->contadorMuertos++] = 0;
            break;
        case ENFERMO:
            ag->mapa->v_en[ag->mapa->contadorEnfermos++] = 1;
            ag->mapa->v_sa[ag->mapa->contadorSanos++] = 0;
            ag->mapa->v_cu[ag->mapa->contadorCurados++] = 0;
            ag->mapa->v_mu[ag->mapa->contadorMuertos++] = 0;
            break;
        case MUERTO:
            ag->mapa->v_mu[ag->mapa->contadorMuertos++] = 1;
            ag->mapa->v_en[ag->mapa->contadorEnfermos++] = 0;
            ag->mapa->v_sa[ag->mapa->contadorSanos++] = 0;
            ag->mapa->v_cu[ag->mapa->contadorCurados++] = 0;
            break;
        case SANO:
            ag->mapa->v_sa[ag->mapa->contadorSanos++] = 1;
            ag->mapa->v_cu[ag->mapa->contadorCurados++] = 0;
            ag->mapa->v_mu[ag->mapa->contadorMuertos++] = 0;
            ag->mapa->v_en[ag->mapa->contadorEnfermos++] = 0;
            break;
    }
    usleep(100000);
}

bool checkCollision(struct Agente* ag) {
    if (ag->id == 1 || ag->id == 5 || ag->id == 9) { //recto
        if (ag->dis == 1 || ag->dis == 2) {
            if (ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] != 0) {
                int numeroMantiza = rand() % 100;
                int numeroExponente = rand() % 10;
                double p = numeroMantiza + numeroExponente * 0.1;
                if (ag->p_infeccion > p) { //SE ENFERMA
                    if ((ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] == 5 ||
                            ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] == 7 ||
                            ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] == 8) && ag->id == 1) {
                        pthread_t probabilidadMuerte;
                        pthread_create(&probabilidadMuerte, NULL, p_muerte, ag);
                        pthread_join(probabilidadMuerte, NULL);
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
                if (ag->p_infeccion > p) { //SE ENFERMA
                    if ((ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] == 5 ||
                            ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] == 7 ||
                            ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] == 8) && ag->id == 1) {
                        ag->estado = ENFERMO;
                        pthread_t probabilidadMuerte;
                        pthread_create(&probabilidadMuerte, NULL, p_muerte, ag);
                        pthread_join(probabilidadMuerte, NULL);
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
            if ((ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] == 5 ||
                    ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] == 7 ||
                    ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] == 8)) {
                int numeroMantiza = rand() % 100;
                int numeroExponente = rand() % 10;
                double p = numeroMantiza + numeroExponente * 0.1;
                if (ag->p_infeccion > p) {
                    if (ag->id == 3) {
                        pthread_t probabilidadMuerte;
                        pthread_create(&probabilidadMuerte, NULL, p_muerte, ag);
                        pthread_join(probabilidadMuerte, NULL);
                        ag->estado = ENFERMO;
                        pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ag->pos_x + ag->dx][ag->pos_y]);
                        ag->id = 7;
                        pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ag->pos_x + ag->dx][ag->pos_y]);
                    }
                }
                return true;

            }

        } else if (ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->pos_y] != 0) {
            if ((ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] == 5 ||
                    ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] == 7 ||
                    ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] == 8)) {
                int numeroMantiza = rand() % 100;
                int numeroExponente = rand() % 10;
                double p = numeroMantiza + numeroExponente * 0.1;
                if (ag->p_infeccion > p) {
                    if (ag->id == 3) {
                        pthread_t probabilidadMuerte;
                        pthread_create(&probabilidadMuerte, NULL, p_muerte, ag);
                        pthread_join(probabilidadMuerte, NULL);
                        ag->estado = ENFERMO;
                        pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y + ag->dy]);
                        ag->id = 7;
                        pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y + ag->dy]);
                    }
                }

            }
            return true;
        }
    } else if (ag->id == 2) {
        if (ag->mapa->mapaS[ag->pos_x + 1][ag->pos_y] != 0 ||
                ag->mapa->mapaS[ag->pos_x][ag->pos_y + 1] != 0) {
            int numeroMantiza = rand() % 100;
            int numeroExponente = rand() % 10;
            double p = numeroMantiza + numeroExponente * 0.1;
            if (ag->p_infeccion > p) { //SE ENFERMA
                if (ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] == 5 ||
                        ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] == 7 ||
                        ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] == 8) {
                    ag->estado = ENFERMO;
                    pthread_t probabilidadMuerte;
                    pthread_create(&probabilidadMuerte, NULL, p_muerte, ag);
                    pthread_join(probabilidadMuerte, NULL);
                    pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                    ag->id = 6;
                    pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                } else if (ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] == 5 ||
                        ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] == 7 ||
                        ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] == 8) {
                    ag->estado = ENFERMO;
                    pthread_t probabilidadMuerte;
                    pthread_create(&probabilidadMuerte, NULL, p_muerte, ag);
                    pthread_join(probabilidadMuerte, NULL);
                    pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                    ag->id = 6;
                    pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y]);
                }
            }

            return true;
        }
    } else if (ag->id == 4) {
        if (ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] != 0) {
            int numeroMantiza = rand() % 100;
            int numeroExponente = rand() % 10;
            double p = numeroMantiza + numeroExponente * 0.1;
            if (ag->p_infeccion > p) { //SE ENFERMA
                if ((ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] == 5 ||
                        ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] == 7 ||
                        ag->mapa->mapaS[ag->pos_x][ag->pos_y + ag->dy] == 8) && ag->id == 4) {
                    ag->estado = ENFERMO;
                    pthread_t probabilidadMuerte;
                    pthread_create(&probabilidadMuerte, NULL, p_muerte, ag);
                    pthread_join(probabilidadMuerte, NULL);
                    pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y + ag->dy]);
                    ag->id = 8;
                    pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ag->pos_x][ag->pos_y + ag->dy]);
                }
            }
        } else if (ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] != 0) {
            int numeroMantiza = rand() % 100;
            int numeroExponente = rand() % 10;
            double p = numeroMantiza + numeroExponente * 0.1;
            if (ag->p_infeccion > p) { //SE ENFERMA
                if ((ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] == 5 ||
                        ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] == 7 ||
                        ag->mapa->mapaS[ag->pos_x + ag->dx][ag->pos_y] == 8) && ag->id == 4) {
                    pthread_t probabilidadMuerte;
                    pthread_create(&probabilidadMuerte, NULL, p_muerte, ag);
                    pthread_join(probabilidadMuerte, NULL);
                    ag->estado = ENFERMO;
                    pthread_mutex_lock(&ag->mapa->mapa_pos_mutex[ag->pos_x + ag->dx][ag->pos_y]);
                    ag->id = 8;
                    pthread_mutex_unlock(&ag->mapa->mapa_pos_mutex[ag->pos_x + ag->dx][ag->pos_y]);
                }
            }
        }
    }
    return false;
}
