
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
        usleep(100000);
    }
}
void* cleanS(){
    while (1) {
        clear();
        usleep(1000000);
    }
}

int main(int argc, char** argv) {
    
    srand(time(0));
    int f, c, cant_paredes, cont=0;
    int *v;
    
    FILE* fichero;
    fichero = fopen("fichero", "r");
    if (fichero == NULL) {
        fputs("Archivo no encontrado!", stderr);
        exit(1);
    }
    
    fscanf(fichero, "%d %d\n", &f, &c);
    fscanf(fichero, "%d\n", &cant_paredes);
    v = (int*)malloc(sizeof(int)*cant_paredes*10);
      
    for(int i=0;i<cant_paredes;i++){
        fscanf(fichero, "%d %d %d %d\n", &v[cont++], &v[cont++], &v[cont++], &v[cont++]);
    }
    fclose(fichero);
    
/*
    fichero = fopen("fichero2", "r");
    if (fichero == NULL) {
        fputs("Archivo no encontrado!", stderr);
        exit(1);
    }
    fclose(fichero);
*/
    
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
    
    init_pair(8, 15, COLOR_BLACK);
    init_pair(9, 15, 15);
    //bkgd(COLOR_PAIR(9));
    noecho();
    curs_set(0);
    for(int i=0;i<5;i++){
        attron(COLOR_PAIR(10));
        move(1,6+1); 
        addch('o');
        attroff(COLOR_PAIR(10));
        usleep(1000000);
    }
    clear();
    pthread_t update;
    pthread_create(&update,NULL, refrescar, NULL);
    pthread_t clear_t;
    pthread_create(&clear_t,NULL, cleanS, NULL);
    //bkgd(COLOR_PAIR(9));
    
    crearSimulacion(f, c);
    dibujarCuadro(f, c);
    run(0);
    pthread_join(update,NULL);
    pthread_join(clear_t,NULL);
    getch();
    endwin();
    return (EXIT_SUCCESS);
}

