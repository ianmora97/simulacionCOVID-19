/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "tools.h"

void dibujarCuadro(int x, int y){   
    for(int i=0;i<y*3;i++, i++, i++){
        mvprintw(1,i,"---");     
    }
    for(int i=0;i<y*3;i++, i++, i++){
        mvprintw(x+2,i,"---");
    }
    for(int i=1;i<=x+1;i++){
        mvprintw(i,1,"|");
    }
    for(int i=1;i<=x+1;i++){
        mvprintw(i,y*3,"|");
    }
    mvprintw(1,1,"+");
    mvprintw(1,x*3,"+");
    mvprintw(y+2,1,"+");
    mvprintw(y+2,x*3,"+");
    refresh();
}
