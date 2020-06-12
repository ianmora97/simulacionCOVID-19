
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <ncurses.h>
#include <pthread.h>
#include <time.h>
#include "Simulacion.h"
#include "tools.h"

void* refrescar() {
    while (1) {
        refresh();
        usleep(50000);
    }
}

void* cleanS() {
    while (1) {
        clear();
        usleep(1000000);
    }
}

int main(int argc, char** argv) {

    srand(time(0));
    int f, c, cant_paredes, cont = 0;
    int *v,*ca,*ta,*vel;
    char *es;

    FILE* fichero;
    fichero = fopen("fichero", "r");
    if (fichero == NULL) {
        fputs("Archivo no encontrado!", stderr);
        exit(1);
    }
    else{
        printf("Archivo abierto\n");
    }

    fscanf(fichero, "%d %d\n", &f, &c);
    fscanf(fichero, "%d\n", &cant_paredes);
    v = (int*) malloc(sizeof (int)*cant_paredes * 10);

    for (int i = 0; i < cant_paredes; i++) {
        fscanf(fichero, "%d %d %d %d\n", &v[cont++], &v[cont++], &v[cont++], &v[cont++]);
    }
    fclose(fichero);

    fichero = fopen("fichero2", "r");
    if (fichero == NULL) {
        fputs("Archivo no encontrado!", stderr);
        exit(1);
    }
    else{
        printf("Archivo abierto\n");
    }
    
    int cont_grupos=0, cont_tipos=0, cont_vel=0, cont_estados=0;
    cont = 0;
    fscanf(fichero, "%d\n", &cant_paredes);
    ca = (int*) malloc(sizeof (int)*cant_paredes * 10);
    ta = (int*) malloc(sizeof (int)*cant_paredes * 10);
    vel = (int*) malloc(sizeof (int)*cant_paredes * 20);
    es = (char*) malloc(sizeof (char)*cant_paredes * 20);
    for (int i = 0; i < cant_paredes; i++) {
        fscanf(fichero, "%d\n", &ca[cont_grupos++]); //cantidad por grupo
        fscanf(fichero, "%d\n", &ta[cont_tipos++]); //tipos
        fscanf(fichero, "%d %d\n", &vel[cont_vel++], &vel[cont_vel++]); //velocidades
        fscanf(fichero, "%c\n", &es[cont_estados++]); //estados
    }
    fclose(fichero);

    printf("%i, %i, %i, %i ",cont_grupos,cont_tipos,cont_vel,cont_estados);
    
    initscr();
    start_color();
    init_pair(1, 10, COLOR_BLACK); //sano
    init_pair(2, 10, COLOR_BLACK); //sano
    init_pair(3, 10, COLOR_BLACK); //sano
    init_pair(4, 10, COLOR_BLACK); //sano

    init_pair(5, 9, COLOR_BLACK);
    init_pair(6, 9, COLOR_BLACK);
    init_pair(7, 9, COLOR_BLACK);
    init_pair(8, 9, COLOR_BLACK);

    init_pair(9, COLOR_YELLOW, COLOR_BLACK);
    init_pair(10, COLOR_YELLOW, COLOR_BLACK);
    init_pair(11, COLOR_YELLOW, COLOR_BLACK);
    init_pair(12, COLOR_YELLOW, COLOR_BLACK);
    
    //bkgd(COLOR_PAIR(9));
    noecho();
    curs_set(0);
    for (int i = 0; i < 10; i++) {
        attron(COLOR_PAIR(1));
        move(6, 6 + i);
        addch('o');
        attroff(COLOR_PAIR(1));
        usleep(1000000);
        refresh();
    }
    clear();
    
    refresh();
    pthread_t update;
    pthread_create(&update, NULL, refrescar, NULL);
    pthread_t clear_t;
    pthread_create(&clear_t, NULL, cleanS, NULL);

    

    crearSimulacion(f, c);
    crearAgentes(cont_grupos, cont_tipos, cont_vel, cont_estados,ca,ta,vel,es);
    dibujarCuadro(f, c);
    
    pthread_join(update, NULL);
    pthread_join(clear_t, NULL);
    getch();
    endwin();
    return (EXIT_SUCCESS);
}

