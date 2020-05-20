#include "Mapa.h"
#include "Lista.h"

struct Mapa* crearMapa(int f, int c) {
    struct Mapa* m;
    m = malloc(sizeof (struct Mapa*));
    m->fila = f;
    m->columnas = c;
    m->tam = f*c;
    m->mapaS = malloc(f * sizeof (int *)*10);
    for (int i = 0; i < f; i++) {
        m->mapaS[i] = malloc(c * sizeof (int)*10);
    }
    for (int i = 0; i < m->fila; i++) {
        for (int j = 0; j < m->columnas; j++) {
            //m->mapaS[i][j] = i*10+j;
            m->mapaS[i][j] = 0;
        }
    }
    return m;
}

void dibujarMapa(struct Mapa* m) {
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    int ant_x, ant_y;
    for (int i = 0; i < m->fila; i++) {
        for (int j = 0; j < m->columnas; j++) {
            if (m->mapaS[i][j] != 0) {
                //attron(COLOR_PAIR(m->mapaS[i][j]));
                move(i + 2, j * 3 + 2);
                addch('O');
                /*
                                mvprintw(i+2,j*3+2,"%i",m->mapaS[i][j]);
                 */
                //attroff(COLOR_PAIR(m->mapaS[i][j]));
            }
            if (m->mapaS[i][j] == 0) {
                move(i + 2, j * 3 + 2);
                addch(' ');
            }
            refresh();
        }
    }
}
