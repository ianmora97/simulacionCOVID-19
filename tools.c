/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "tools.h"

void dibujarCuadro(int x, int y){
    
    attron(COLOR_PAIR(8));
    for(int i=1;i<y*3;i++, i++, i++){
        move(1,i);
        addch(ACS_HLINE);
        move(1,i+1);
        addch(ACS_HLINE);
        move(1,i+2);
        addch(ACS_HLINE);
    }
    for(int i=1;i<y*3;i++, i++, i++){
        move(x+2,i);
        addch(ACS_HLINE);
        move(x+2,i+1);
        addch(ACS_HLINE);
        move(x+2,i+2);
        addch(ACS_HLINE);
    }
    for(int i=1;i<=x+1;i++){
        move(i,y*3+1);
        addch(ACS_VLINE);
    }
    for(int i=1;i<=x+1;i++){
        move(i,1);
        addch(ACS_VLINE);
    }
    
    move(1,1);
    addch(ACS_ULCORNER);
    move(1,x*3+1);
    addch(ACS_URCORNER);
    move(y+2,1);
    addch(ACS_LLCORNER);
    move(y+2,x*3+1);
    addch(ACS_LRCORNER);
    attroff(COLOR_PAIR(8));
    
}

