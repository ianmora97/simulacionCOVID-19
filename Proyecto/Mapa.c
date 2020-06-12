#include "Mapa.h"
#include "Lista.h"

struct Mapa* crearMapa(int f, int c) {
    struct Mapa* m;
    m = malloc(sizeof (struct Mapa*)*50);
    m->fila = f;
    m->columnas = c;
    m->tam = f*c;
    m->mapaS = malloc(f * sizeof (int *)*20);
    for (int i = 0; i < f; i++) {
        m->mapaS[i] = malloc(c * sizeof (int)*20);
    }
    m->mapa_pos_mutex = malloc(f * sizeof (int *)*20);
    for (int i = 0; i < f; i++) {
        m->mapa_pos_mutex[i] = malloc(c * sizeof (int)*20);
    }
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            pthread_mutex_init(&m->mapa_pos_mutex[i][j], NULL);
        }
    }
    for (int i = 0; i < m->fila; i++) {
        for (int j = 0; j < m->columnas; j++) {
            //m->mapaS[i][j] = i*10+j;
            m->mapaS[i][j] = 0;
        }
    }
    pthread_mutex_init(&m->lockRefresh, NULL);
    m->contadorEnfermos=0;
    m->contadorSanos=0;
    m->contadorCurados=0;
    m->contadorMuertos=0;
    return m;
}

void dibujarMapa(struct Mapa* m) {
    for (int i = 0; i < m->fila; i++) {
        for (int j = 0; j < m->columnas; j++) {
            if (m->mapaS[i][j] != 0) {
                attron(COLOR_PAIR(m->mapaS[i][j]) | A_BOLD);
                move(i + 2, j * 3 + 2);
                addch(ACS_DIAMOND);
                attroff(COLOR_PAIR(m->mapaS[i][j]) | A_BOLD);
            }else if (m->mapaS[i][j] == 0) {
                attron(COLOR_PAIR(5));
                move(i + 2, j * 3 + 2);
                addch(' ');
                attroff(COLOR_PAIR(5));
            }
        }
    }
    //dibujarCuadro(m->fila, m->columnas);
}
