/**
 * \file graphique.h
 * \brief Header file of graphique.c.
 * \author HARDY Elise & BEN HAMOUDA Amel
 */

#ifndef __GRAPHIQUE__
    #define __GRAPHIQUE__

    #define ESP 4

    /**
     * \fn void drawPointAndLine(TabTriangle *triangle)
     * \brief Function that draws the points and red lines on the picture according to the coordinates in parameters.
     *
     * \param triangle The drawing triangle list.
     */
    void drawPointAndLine(TabTriangle *triangle);

    /**
     * \fn void drawButton(Board *p)
     * \brief Function that draws the buttons.
     *
     * \param p The board to access the numbers of frames.
     */
    void drawButton(Board *p);

    /**
     * \fn void drawAll(Board *p, TabTriangle listTriangle)
     * \brief Function that draws everything in the window.
     *
     * \param p The board to access everything in the structure.
     * \param listTriangle The triangle list to draw.
     */
    void drawAll(Board *p, TabTriangle listTriangle);

    /**
     * \fn void drawInstruct()
     * \brief Function that draws instruction in the window while the positioning of points.
     *
     */
    void drawInstruct();
    

    
#endif
