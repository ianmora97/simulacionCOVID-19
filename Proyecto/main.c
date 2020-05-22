
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

int main(int argc, char** argv) {
    
    srand(time(0));

    
    FILE* fichero;
    fichero = fopen("fichero", "r");
    if (fichero == NULL) {
        fputs("Archivo no encontrado!", stderr);
        exit(1);
    }
    int f, c;
    fscanf(fichero, "%d %d", &f, &c);
    int op;
    scanf("%d", &op);
    initscr();

    start_color();
    init_pair(9, 15, 15);
    bkgd(COLOR_PAIR(9));
    noecho();
    curs_set(0);
    system("clear");
    pthread_t update;
    pthread_create(&update,NULL, refrescar, NULL);
    
    
    crearSimulacion(f, c);
    dibujarCuadro(f, c);
    run(0);
    pthread_join(update,NULL);
    getch();
    endwin();
    return (EXIT_SUCCESS);
}

