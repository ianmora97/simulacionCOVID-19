/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Simulacion.h"

void crearSimulacion(int filas, int columnas, double m_pro[4][4], int p_muerte, int t_curarse, int t_morir, bool recontagio) {
    mapa = crearMapa(filas, columnas);

    cant_rectos = 0;
    cant_estaticos = 0;
    cant_aleatorios = 0;
    cant_estacionales = 0;

    cant_rectos_e = 0;
    cant_estaticos_e = 0;
    cant_aleatorios_e = 0;
    cant_estacionales_e = 0;

    cantidadAgentes = 0;
    mapa->re_contagio = recontagio;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matriz[i][j] = m_pro[i][j];
        }
    }
    mapa->segundosCurarse = t_curarse;
    mapa->segundosMorir = t_morir;
    mapa->p_muerte = p_muerte;
    ag_hilos = malloc(filas * columnas * sizeof (pthread_t)*5000);
    reporte = malloc(filas * columnas * sizeof (pthread_t)*5000);
}

void *imprimirReporte(void* arg) {
    int time = (int*)arg;
    usleep(1000000 * time);
    
    FILE* fichero;
    fichero = fopen("simulacionPrint.csv", "w");
    if (fichero == NULL) {
        fputs("Archivo no encontrado!", stderr);
        exit(1);
    } else {
        printf("Archivo abierto\n");
    }
    fprintf(fichero, "Curados, Enfermos, Muertos, Sanos/n");
    fprintf(fichero, "%d, %d, %d, %d ",mapa->contadorCurados,mapa->contadorEnfermos,mapa->contadorMuertos,mapa->contadorSanos);
    fclose(fichero);
    mvprintw(5,5,"%i, %i, %i, %i",mapa->contadorCurados,mapa->contadorEnfermos,mapa->contadorMuertos,mapa->contadorSanos);
    clear();
    refresh();
    exit(-1);
    
}

void crearAgentes(int cont_grupos, int cont_tipos, int cont_vel, int cont_est, int* gv, int* tv, int* vv, char* ev) {
    clear();
    for (int i = 0; i < cont_grupos; i++) {
        switch (tv[i]) {
            case 1: //tipo recto 
                if (ev[i] == 's') {
                    cant_rectos += gv[i];
                } else {
                    cant_rectos_e += gv[i];
                }
                break;
            case 2: //tipo estacional
                if (ev[i] == 's') {
                    cant_estaticos += gv[i];
                } else {
                    cant_estaticos_e += gv[i];
                }
                break;
            case 3: //tipo aleatorio
                if (ev[i] == 's') {
                    cant_aleatorios += gv[i];
                } else {
                    cant_aleatorios_e += gv[i];
                }
                break;
            case 4: //tipo estatico
                if (ev[i] == 's') {
                    cant_estacionales += gv[i];
                } else {
                    cant_estacionales_e += gv[i];
                }
                break;

        }

    }
    printf("R:%i E:%i A:%i Q:%i", cant_rectos, cant_estacionales, cant_aleatorios, cant_estaticos);
    refresh();
    for (int i = 0; i < cant_rectos; i++) { //rectos sanos
        int dx, dy;
        bool ban = true;
        while (ban) {
            dx = (3 + rand() % mapa->fila - 3);
            dy = (3 + rand() % mapa->columnas - 3);
            if (mapa->mapaS[dx][dy] == 0) {
                ban = false;
            }
        }
        struct Agente *ag = crearAgente(1, 'R', SANO, matriz[0][0], mapa->p_muerte, 50.0, mapa, dx, dy, cantidadAgentes + 1);
        mapa->mapaS[dx][dy] = 1; //1 rectos sanos
        pthread_create(&(ag_hilos[cantidadAgentes]), NULL, moverAgente, ag);
        pthread_create(&(reporte[cantidadAgentes++]), NULL, generarReporte, ag);
    }

    for (int i = 0; i < cant_rectos_e; i++) { //rectos enfermos
        int dx, dy;
        bool ban = true;
        while (ban) {
            dx = (3 + rand() % mapa->fila - 3);
            dy = (3 + rand() % mapa->columnas - 3);
            if (mapa->mapaS[dx][dy] == 0) {
                ban = false;
            }
        }
        struct Agente *ag = crearAgente(5, 'R', ENFERMO, matriz[0][0], mapa->p_muerte, 50.0, mapa, dx, dy, cantidadAgentes + 1);
        mapa->mapaS[dx][dy] = 5; //5 rectos enfermos
        pthread_create(&(ag_hilos[cantidadAgentes]), NULL, moverAgente, ag);
        pthread_create(&(reporte[cantidadAgentes++]), NULL, generarReporte, ag);
    }
    for (int i = 0; i < cant_estaticos; i++) { //estaticos sanos
        int dx, dy;
        bool ban = true;
        while (ban) {
            dx = (3 + rand() % mapa->fila - 3);
            dy = (3 + rand() % mapa->columnas - 3);
            if (mapa->mapaS[dx][dy] == 0) {
                ban = false;
            }
        }
        struct Agente *ag;
        ag = crearAgente(2, 'Q', SANO, matriz[0][1], mapa->p_muerte, 50.0, mapa, dx, dy, cantidadAgentes + 1);
        mapa->mapaS[dx][dy] = 2; //1 rectos
        pthread_create(&(ag_hilos[cantidadAgentes]), NULL, checkEstaticos, ag);
        pthread_create(&(reporte[cantidadAgentes++]), NULL, generarReporte, ag);
    }
    for (int i = 0; i < cant_estaticos_e; i++) { //estaticos enfermos
        int dx, dy;
        bool ban = true;
        while (ban) {
            dx = (3 + rand() % mapa->fila - 3);
            dy = (3 + rand() % mapa->columnas - 3);
            if (mapa->mapaS[dx][dy] == 0) {
                ban = false;
            }
        }
        struct Agente *ag;
        ag = crearAgente(6, 'Q', ENFERMO, matriz[0][1], mapa->p_muerte, 50.0, mapa, dx, dy, cantidadAgentes + 1);
        mapa->mapaS[dx][dy] = 6; //1 rectos
        pthread_create(&(ag_hilos[cantidadAgentes]), NULL, checkEstaticos, ag);
        pthread_create(&(reporte[cantidadAgentes++]), NULL, generarReporte, ag);
    }
    for (int i = 0; i < cant_aleatorios; i++) { //aleatorios sanos
        int dx, dy;
        bool ban = true;
        while (ban) {
            dx = (5 + rand() % mapa->fila - 5);
            dy = (5 + rand() % mapa->columnas - 5);
            if (mapa->mapaS[dx][dy] == 0) {
                ban = false;
            }
        }
        struct Agente *ag;
        ag = crearAgente(3, 'A', SANO, matriz[0][2], mapa->p_muerte, 50.0, mapa, dx, dy, cantidadAgentes + 1);
        mapa->mapaS[dx][dy] = 3; //3 aleatorios
        pthread_create(&(ag_hilos[cantidadAgentes]), NULL, moverAgente, ag);
        pthread_create(&(reporte[cantidadAgentes++]), NULL, generarReporte, ag);
    }
    for (int i = 0; i < cant_aleatorios_e; i++) { //aleatorios enfermos
        int dx, dy;
        bool ban = true;
        while (ban) {
            dx = (5 + rand() % mapa->fila - 5);
            dy = (5 + rand() % mapa->columnas - 5);
            if (mapa->mapaS[dx][dy] == 0) {
                ban = false;
            }
        }
        struct Agente *ag;
        ag = crearAgente(7, 'A', ENFERMO, matriz[0][2], mapa->p_muerte, 50.0, mapa, dx, dy, cantidadAgentes + 1);
        mapa->mapaS[dx][dy] = 7; //7 aleatorios
        pthread_create(&(ag_hilos[cantidadAgentes]), NULL, moverAgente, ag);
        pthread_create(&(reporte[cantidadAgentes++]), NULL, generarReporte, ag);
    }
    for (int i = 0; i < cant_estacionales; i++) { //estacionales sanos
        int dx, dy;
        bool ban = true;
        while (ban) {
            dx = (15 + rand() % mapa->fila - 15);
            dy = (15 + rand() % mapa->columnas - 15);
            if (mapa->mapaS[dx][dy] == 0) {
                ban = false;
            }
        }
        struct Agente *ag = crearAgente(4, 'E', SANO, matriz[0][3], mapa->p_muerte, 50.0, mapa, dx, dy, cantidadAgentes + 1);
        mapa->mapaS[dx][dy] = 4; //3 aleatorios
        pthread_create(&(ag_hilos[cantidadAgentes]), NULL, moverAgente, ag);
        pthread_create(&(reporte[cantidadAgentes++]), NULL, generarReporte, ag);
    }
    for (int i = 0; i < cant_estacionales_e; i++) { //estacionales enfermos
        int dx, dy;
        bool ban = true;
        while (ban) {
            dx = (15 + rand() % mapa->fila - 15);
            dy = (15 + rand() % mapa->columnas - 15);
            if (mapa->mapaS[dx][dy] == 0) {
                ban = false;
            }
        }
        struct Agente *ag = crearAgente(8, 'E', ENFERMO, matriz[0][3], mapa->p_muerte, 50.0, mapa, dx, dy, cantidadAgentes + 1);
        mapa->mapaS[dx][dy] = 8; //7 aleatorios
        pthread_create(&(ag_hilos[cantidadAgentes]), NULL, moverAgente, ag);
        pthread_create(&(reporte[cantidadAgentes++]), NULL, generarReporte, ag);
    }

    for (int i = 0; i < (cantidadAgentes); i++) {
        pthread_join(ag_hilos[i], NULL);
        pthread_join(reporte[i], NULL);
    }
}
