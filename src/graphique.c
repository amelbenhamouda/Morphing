#include "./../include/mecanique.h"
#include "./../include/graphique.h"


void drawPointAndLine(TabTriangle *triangle) {
    int i;
    for (i = 0; i < triangle->size; i++) {
        /* Points */
        MLV_draw_filled_circle(triangle->t[i].cp1.c1.x+IMAG_DEP_X, triangle->t[i].cp1.c1.y+IMAG_DEP_Y, ESP, MLV_COLOR_RED);
        MLV_draw_filled_circle(triangle->t[i].cp2.c1.x+IMAG_DEP_X, triangle->t[i].cp2.c1.y+IMAG_DEP_Y, ESP, MLV_COLOR_RED);
        MLV_draw_filled_circle(triangle->t[i].cp3.c1.x+IMAG_DEP_X, triangle->t[i].cp3.c1.y+IMAG_DEP_Y, ESP, MLV_COLOR_RED);
        MLV_draw_filled_circle(triangle->t[i].cp1.c2.x+IMAG_ARR_X, triangle->t[i].cp1.c2.y+IMAG_ARR_Y, ESP, MLV_COLOR_RED);
        MLV_draw_filled_circle(triangle->t[i].cp2.c2.x+IMAG_ARR_X, triangle->t[i].cp2.c2.y+IMAG_ARR_Y, ESP, MLV_COLOR_RED);
        MLV_draw_filled_circle(triangle->t[i].cp3.c2.x+IMAG_ARR_X, triangle->t[i].cp3.c2.y+IMAG_ARR_Y, ESP, MLV_COLOR_RED);
        
        /* Lines */
        MLV_draw_line(triangle->t[i].cp1.c1.x+IMAG_DEP_X, triangle->t[i].cp1.c1.y+IMAG_DEP_Y, triangle->t[i].cp2.c1.x+IMAG_DEP_X, triangle->t[i].cp2.c1.y+IMAG_DEP_Y, MLV_COLOR_RED);
        MLV_draw_line(triangle->t[i].cp2.c1.x+IMAG_DEP_X, triangle->t[i].cp2.c1.y+IMAG_DEP_Y, triangle->t[i].cp3.c1.x+IMAG_DEP_X, triangle->t[i].cp3.c1.y+IMAG_DEP_Y, MLV_COLOR_RED);
        MLV_draw_line(triangle->t[i].cp3.c1.x+IMAG_DEP_X, triangle->t[i].cp3.c1.y+IMAG_DEP_Y, triangle->t[i].cp1.c1.x+IMAG_DEP_X, triangle->t[i].cp1.c1.y+IMAG_DEP_Y, MLV_COLOR_RED);
        MLV_draw_line(triangle->t[i].cp1.c2.x+IMAG_ARR_X, triangle->t[i].cp1.c2.y+IMAG_ARR_Y, triangle->t[i].cp2.c2.x+IMAG_ARR_X, triangle->t[i].cp2.c2.y+IMAG_ARR_Y, MLV_COLOR_RED);
        MLV_draw_line(triangle->t[i].cp2.c2.x+IMAG_ARR_X, triangle->t[i].cp2.c2.y+IMAG_ARR_Y, triangle->t[i].cp3.c2.x+IMAG_ARR_X, triangle->t[i].cp3.c2.y+IMAG_ARR_Y, MLV_COLOR_RED);
        MLV_draw_line(triangle->t[i].cp3.c2.x+IMAG_ARR_X, triangle->t[i].cp3.c2.y+IMAG_ARR_Y, triangle->t[i].cp1.c2.x+IMAG_ARR_X, triangle->t[i].cp1.c2.y+IMAG_ARR_Y, MLV_COLOR_RED);
    }
}

void drawButton(Board *p) {
    int y = SIZE_WINDOW_H - SIZE_PICTURE;
    int height = 2 * IMAG_DEP_X;
    int interligne = 9;

    if (p->nbFrame <= 2) {
        p->nbFrame = 2;
    }
       
    MLV_draw_text_box(142, y, 150, height, "Add constraint point", interligne, MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box(302, y, 160, height, "Hide constraint points", interligne, MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box(472, y, 130, height, "Start rendering", interligne, MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box(612, y, 50, height, "<<<", interligne, MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box(672, y, 100, height, "%d Frames", interligne, MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER, p->nbFrame);
    MLV_draw_text_box(782, y, 50, height, ">>>", interligne, MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_text_box(842, y, 60, height, "Quit", interligne, MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}

void drawAll(Board *p, TabTriangle listTriangle) {
    MLV_clear_window(MLV_COLOR_BLACK);
    drawButton(p);
    MLV_draw_image(p->picture1, IMAG_DEP_X, IMAG_DEP_X);
    MLV_draw_image(p->picture2, SIZE_WINDOW_H - SIZE_PICTURE - IMAG_DEP_Y, IMAG_DEP_Y);     
        
    if (p->active) {
        drawPointAndLine(&listTriangle);
    }
         
    MLV_actualise_window();
}

void drawInstruct(){
    int y = SIZE_WINDOW_H - SIZE_PICTURE - 25;
    int height = 2 * IMAG_DEP_X - 10;
    int interligne = 9;
    MLV_draw_text_box(270, y, 520, height, "Veuillez appuier sur l'image de gauche puis de droite", interligne, MLV_COLOR_GREY, MLV_COLOR_BLACK, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_actualise_window(); 
}

