/**
 * \file action.h
 * \brief Header file of action.c.
 * \author HARDY Elise & BEN HAMOUDA Amel
 */

#ifndef __ACTION__
    #define __ACTION__

    /**
     * \fn int actionButton(int action, Board *p, int addPoint)
     * \brief Function that does an action according to the button clicked.
     *
     * \param action The action we are doing.
     * \param p The Board (the graphic window).
     * \param addPoint Adding a point.
     */
    int actionButton(int action, Board *p, int addPoint);

    /**
     * \fn int wait2Points(Clic clic, Board *p, Couple *cp);
     * \brief Function that wait for the user to click on the left then right window to place the point pair.
     *
     * \param clic The user's click.
     * \param p The Board (the graphic window).
     * \param cp The click couple with the first and second picture.
     */
    int wait2Points(Clic clic, Board *p, Couple *cp);

    /**
     * \fn void isActive(Board *p)
     * \brief Function that change boolean displaying traits.
     *
     * \param p The Board (the graphic window).
     */
    void isActive(Board *p);

#endif
