/**
 * \file mecanique.h
 * \brief Fichier d'en-tete de mecanique.c.
 * \author HARDY Elise & BEN HAMOUDA Amel
 */

#ifndef __MECANIQUE__
    #define __MECANIQUE__

	#include <MLV/MLV_all.h>

    #define SIZE_PICTURE 512
    #define SIZE_WINDOW_H (512 * 2) + 45
    #define SIZE_PART_BUTTON 450
    #define IMAG_DEP_X 15
    #define IMAG_ARR_X (30 + SIZE_PICTURE)
    #define IMAG_DEP_Y 15
    #define IMAG_ARR_Y 15

    /**
     * \struct Clic, Point
     * \brief Object clic, point.
     *
     * Clic, Point is a point object. 
     * The point knows its coordinates x and y.
     */
    typedef struct {
        int x; /*!< The coordinate x. */
        int y; /*!< The coordinate y. */
    } Clic, Point;

    /**
     * \struct Couple
     * \brief Object couple.
     *
     * Couple is an object containing two clicks.
     * The couple knows his click on the first and second images.
     */
    typedef struct {
        Clic c1; /*!< The click on the first image. */
        Clic c2; /*!< The click on the second image. */
    } Couple;

    /**
     * \struct Triangle
     * \brief Object triangle.
     *
     * Triangle is an object containing two couples.
     * The triangle knows its coordinates.
     */
    typedef struct{
        Couple cp1; /*!< The first point of the triangle. */
        Couple cp2; /*!< The second point of the triangle. */
        Couple cp3; /*!< The third point of the triangle. */
    } Triangle;

    /**
     * \struct TabTriangle
     * \brief Object tabtriangle.
     *
     * TabTriangle is an object containing triangles.
     */
    typedef struct{
        Triangle* t; /*!< The triangle board. */
        int size; /*!< The actual size of the triangle board. */
        int tMax; /*!< The maximum size of the triangle board. */
    } TabTriangle;

    /**
     * \struct ColorPixel
     * \brief Object colorpixel.
     *
     * ColorPixel is an object containing argument for generate frame.
     */
    typedef struct {
        Point p; /*!< The coordinates of the pixel. */
        int red; /*!< Red component of the pixel. */
        int green; /*!< Green component of the pixel. */
        int blue; /*!< Blue component of the pixel. */
        int alpha; /*!< Alpha component (transparency) of the pixel. */
    } ColorPixel;

    /**
     * \struct Board
     * \brief Object board.
     *
     * Board is an object that designates the graphic window.
     */
    typedef struct {
        int nbFrame; /*!< The number of frames. */
        MLV_Image *picture1; /*!< The first picture. */
        MLV_Image *picture2; /*!< The second picture. */
        int active; /*!< Booelan who determinate if the lines are visible. */
        Point **listPoint; /*!< The red points board. */
    } Board;

    /**
     * \fn int inPictureOrButton(Clic clic)
     * \brief Function that checks whether the click is on one of the drawn buttons.
     *
     * \param clic The user's click.
     * \return The function returns:
     * \return  -> returns 0 if it is the button Add constraint point,
     * \return  -> returns 1 if it's the Hide constraint point button,
     * \return  -> returns 2 if it is the Start rendering button,
     * \return  -> returns 3 if it's the <<< button,
     * \return  -> returns 4 if it's the >>> button,
     * \return  -> returns 5 if it's the Quit button,
     * \return  -> returns 6 if we click on the image on the left,
     * \return  -> returns 7 if we click on the image on the right,
     * \return  -> returns -1 if it's a bad click.
     */
    int inPictureOrButton(Clic clic);

#endif
