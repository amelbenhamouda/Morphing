#include <stdlib.h>

#include "./../include/mecanique.h"
#include "./../include/graphique.h"
#include "./../include/action.h"
#include "./../include/Delaunay.h"


int actionButton(int action, Board *p, int addPoint) {
    if (addPoint) {
        switch (action) {
            case 1: isActive(p); break;
            case 3: p->nbFrame = p->nbFrame / 2; break;
            case 4: p->nbFrame = p->nbFrame * 2; break;
            case 5: exit(EXIT_SUCCESS); break;
            default: break;
        }
    }
    else {
        switch (action) {
            case 5: exit(EXIT_SUCCESS); break;
            default: break;
        } 
    }
    return action;
}

int wait2Points(Clic clic, Board *p, Couple *cp) {
    int point = 0;
    int result;
    while (point != 2) {
        drawInstruct();
        MLV_wait_mouse(&(clic.x), &(clic.y));
        result = actionButton(inPictureOrButton(clic), p, 0);
        if (result == 6 && point == 0) {
            cp->c1.x = clic.x -IMAG_DEP_X;
            cp->c1.y = clic.y - IMAG_DEP_Y;
            point ++;
        }
        else if (result == 7 && point == 1) {
            cp->c2.x = clic.x - IMAG_ARR_X;
            cp->c2.y = clic.y-IMAG_ARR_Y;
            point ++;
        }    
    }
    return 6;
}

void isActive(Board *p) {
    switch (p->active) {
        case 1: p->active = 0; break;
        case 0: p->active = 1; break;
        default: p->active = 1; break;
    }
}
