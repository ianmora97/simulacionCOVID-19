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
    m->mapa_pos_mutex = malloc(f * sizeof (int *)*10);
    for (int i = 0; i < f; i++) {
        m->mapa_pos_mutex[i] = malloc(c * sizeof (int)*10);
    }
    for(int i=0;i<f;i++){
        for(int j=0;j<c;j++){
            pthread_mutex_init(&m->mapa_pos_mutex[i][j],NULL);
        }
    }
    for (int i = 0; i < m->fila; i++) {
        for (int j = 0; j < m->columnas; j++) {
            //m->mapaS[i][j] = i*10+j;
            m->mapaS[i][j] = 0;
        }
    }
    pthread_mutex_init(&m->lockRefresh,NULL);
    return m;
}

void dibujarMapa(struct Mapa* m) {
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_GREEN);
    init_pair(3, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(4, COLOR_WHITE, COLOR_GREEN);
    init_pair(5, COLOR_WHITE, COLOR_WHITE);
    for (int i = 0; i < m->fila; i++) {
        for (int j = 0; j < m->columnas; j++) {
            if (m->mapaS[i][j] != 0) {
                attron(COLOR_PAIR(m->mapaS[i][j]));
                move(i + 2, j * 3 + 2);
                addch(ACS_DIAMOND);
                attroff(COLOR_PAIR(m->mapaS[i][j]));
            }
            if (m->mapaS[i][j] == 0) {
                move(i + 2, j * 3 + 2);
                addch(' ');
            }
            
            pthread_mutex_lock(&m->lockRefresh);
            
            refresh();
            pthread_mutex_unlock(&m->lockRefresh);
        }
    }
}
