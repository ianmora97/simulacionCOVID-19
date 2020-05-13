/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "tools.h"

void dibujarCuadro(int x, int y){   
    for(int i=0;i<y*3;i++, i++, i++){
        gotoxy(i,1);printf("---");     
    }
    for(int i=0;i<y*3;i++, i++, i++){
        gotoxy(i,x+2);printf("---");
    }
    for(int i=1;i<=x+1;i++){
        gotoxy(1,i);printf("|");
    }
    for(int i=1;i<=x+1;i++){
        gotoxy(y*3,i);printf("|");
    }
    gotoxy(1,1); printf("+");
    gotoxy(x*3,1); printf("+");
    gotoxy(1,y+2); printf("+");
    gotoxy(x*3,y+2); printf("+");
}
