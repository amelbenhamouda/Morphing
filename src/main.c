#include "./../include/mecanique.h"
#include "./../include/graphique.h"
#include "./../include/action.h"
#include "./../include/Delaunay.h"


int main(int argc, char const *argv[]) {
    /* Creating and/or initializing variables. */
    int resultat = -1;
    Clic clic;
    Couple cp;
    TabTriangle triangle;
    Board p;
    p.nbFrame = 2;
    p.active = 1;
    /* Check if the user has put both images in argument. */
    if (argc == 3) {
        /* Creation of the graphic window. */
        MLV_create_window( "Morphing", "", SIZE_WINDOW_H, SIZE_WINDOW_H - SIZE_PART_BUTTON);
    
        /* Loading images. */
        p.picture1 = MLV_load_image(argv[1]);
        p.picture2 = MLV_load_image(argv[2]);
        MLV_resize_image(p.picture1, SIZE_PICTURE, SIZE_PICTURE);
        MLV_resize_image(p.picture2, SIZE_PICTURE, SIZE_PICTURE);

        /* Displays loaded images. */
        MLV_draw_image(p.picture1, IMAG_DEP_X, IMAG_DEP_Y);
        MLV_draw_image(p.picture2, SIZE_WINDOW_H - SIZE_PICTURE - IMAG_DEP_X, IMAG_ARR_Y);     
            
        /* Creating a triangle table. */
        initializeArrayTriangle(&triangle);
        
        /* Displays red points and lines. */
        drawPointAndLine(&triangle);

        /* Displays buttons. */
        drawButton(&p);
        MLV_actualise_window();
        
        while (1) {
            MLV_wait_mouse(&(clic.x), &(clic.y));
            resultat = actionButton(inPictureOrButton(clic), &p, 1);

            if (resultat == 0) {
                resultat = wait2Points(clic, &p, &cp);
                insertPointAndDelaunay(&triangle, &cp);
                drawPointAndLine(&triangle);
            }
            if (resultat == 2) {
                generateFrame(p, triangle);
            }
            drawAll(&p, triangle);  
        }
        MLV_free_image(p.picture2);
        MLV_free_image(p.picture1);
        MLV_free_window();
    }
    else {
        printf("Erreur sur la saisie des arguments.\n");
    }
    
    return 0;
}
