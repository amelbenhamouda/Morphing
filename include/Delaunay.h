/**
 * \file Delaunay.h
 * \brief Header file of Delaunay.c.
 * \author HARDY Elise & BEN HAMOUDA Amel
 */
 
#ifndef __DELAUNAY__
    #define __DELAUNAY__


    /**
     * \struct Matrix
     * \brief object matrix.
     *
     * Matrix is a Matrix management object.
     * The Matrix knows its length and width, 
     * the Matrix is contained in a two-dimensional long-type array.
     */
    typedef struct {
        int n; /*!< Length of the Matrix. */
        int p; /*!< Width of the Matrix. */
        long** mat; /*!< Two-dimensional array containing the Matrix. */
    } Matrix;

    /**
     * \struct BarycentricCoordinates
     * \brief object barycentric coordinate.
     *
     * BarycentricCoordinates is a management object of a coordinate.
     */
    typedef struct {
        float alpha; /*!< The first determinant. */
        float beta; /*!< The second determinant. */
        float gamma; /*!< The third determinant. */
    } BarycentricCoordinates;

	/**
	 * \fn void addTriangle(TabTriangle *triangle, Triangle tr)
	 * \brief Function that adds a triangle in the triangle list.
	 *
	 * \param triangle The triangle list.
	 * \param tr Triangle to add to the triangle list.
	 */
    void addTriangle(TabTriangle *triangle, Triangle tr);

    /**
	 * \fn void initializeArrayTriangle(TabTriangle *triangle)
	 * \brief Function that initializes the triangle array with the two beginning triangles.
	 *
	 * \param triangle The triangle list.
	 */
    void initializeArrayTriangle(TabTriangle *triangle);

    /**
	 * \fn int insertPointAndDelaunay(TabTriangle *listTriangle, Couple *point)
	 * \brief Function that removes and creates the right points and verifies that the triangle creates is Delaunay.
	 *
	 * \param listTriangle The triangle list.
	 * \param point The couple of points of the click on the image.
	 * \return 0 if everything goes well.
	 */
    int insertPointAndDelaunay(TabTriangle *listTriangle, Couple *point);

    /**
	 * \fn int isPositif(BarycentricCoordinates cordBary)
	 * \brief Function that checks whether the barycentric coordinates are positive.
	 *
	 * \param coordBary The coordinates to check.
	 * \return 1 if everything is positive otherwise 0.
	 */
    int isPositif(BarycentricCoordinates cordBary);

    /**
	 * \fn int areaCalcul(Triangle triangle)
	 * \brief Fonction qui calculer aire du triangle.
	 *
	 * \param triangle The triangle for which we want to know the area.
	 * \return The area of the triangle.
	 */
    int areaCalcul(Triangle triangle);

    /**
	 * \fn BarycentricCoordinates calculBarycentricCoordinates(Point p, Triangle triangle)
	 * \brief Function that calculates area of the triangle.
	 *
	 * \param p The point of the click.
	 * \param triangle The triangle containing the point.
	 * \return tmp The calculated barycentric coordinate.
	 */
    BarycentricCoordinates calculBarycentricCoordinates(Point p, Triangle triangle);

    /**
	 * \fn int isInTriangle(Point p, Triangle triangle)
	 * \brief Function that checks if point is in the triangle.
	 *
	 * \param p The point of the click.
	 * \param triangle The triangle containing the point.
	 * \return  1 if true else 0.
	 */
    int isInTriangle(Point p, Triangle triangle);

    /**
	 * \fn long determinant2x2(long c00, long c01, long c10, long c11)
	 * \brief Function that calculates 2x2 determinant.
	 *
	 * \param c00 The value at the top left of a Matrix.
	 * \param c01 The value at the top right of a Matrix.
	 * \param c10 The value at the bottom left of a Matrix.
	 * \param c11 The value at the bottom right of a Matrix.
	 * \return The result of the determinant calculate.
	 */
    long determinant2x2(long c00, long c01, long c10, long c11);

    /**
	 * \fn int strangeCalcul(int a, int b, int c, int d)
	 * \brief Function that calculates a result according to the given formula.
	 *
	 * \param a Fisrt number of calculation.
	 * \param b Second number of calculation.
	 * \param c Third number of calculation.
	 * \param d Fourth number of calculation.
	 * \return The result of calculation.
	 */
    int strangeCalcul(int a, int b, int c, int d);

    /**
	 * \fn int builtCounterclickwiseTriangle(Couple c1, Couple c2 ,Couple c3,Triangle *triangle)
	 * \brief Function that calculates a result according to the given formula builds counterclockwise triangle to make sure the coordinates are positive.
	 *
	 * \param c1 One of the points of the triangle.
	 * \param c2 One of the points of the triangle.
	 * \param c3 One of the points of the triangle.
	 * \param triangle Is the triangle built according to the three couples set in parameters.
	 * \return 0 if all is well.
	 */
    int builtCounterclickwiseTriangle(Couple c1, Couple c2, Couple c3, Triangle *triangle);

    /**
	 * \fn int findTriangle(TabTriangle listTriangle, Point p)
	 * \brief Function that finds the triangle in which the point is located.
	 *
	 * \param listTriangle The list of triangles.
	 * \param p The point of the click.
	 * \return The position of the triangle in the list according to the point.
	 */
    int findTriangle(TabTriangle listTriangle, Point p);

    /**
	 * \fn int equalTriangle(Triangle tr1, Triangle tr2)
	 * \brief Function that checks if one triangle is equal to another.
	 *
	 * \param tr1 First triangle to test.
	 * \param tr2 Second triangle to test.
	 * \return 1 if the two triangles are equal, 0 otherwise.
	 */
    int equalTriangle(Triangle tr1, Triangle tr2);

    /**
	 * \fn void copyTriangle(Triangle tr, Triangle *tr2)
	 * \brief Function that copies a triangle into another.
	 *
	 * \param tr The triangle to copy.
	 * \param tr2 The triangle that will contain the copy.
	 */
    void copyTriangle(Triangle tr, Triangle *tr2);

    /**
	 * \fn int remove1Create3Triangle(TabTriangle *triangle, int indice, Couple p)
	 * \brief Function that deletes a triangle to create 3 others.
	 *
	 * \param triangle The triangle board.
	 * \param indice Is the place where the triangle is in the table.
	 * \param p The point of the click.
	 * \return 0 if all is well.
	 */
    int remove1Create3Triangle(TabTriangle *triangle, int indice, Couple p);

    /**
	 * \fn int equalPoint(Couple c1, Couple c2)
	 * \brief Function that checks if two points are equal.
	 *
	 * \param c1 The first point to test.
	 * \param c2 The second point to test.
	 * \return 1 if the two points are equal, 0 otherwise.
	 */
    int equalPoint(Couple c1, Couple c2);

    /**
	 * \fn int isEqualSommit(Triangle triangle, Couple point)
	 * \brief Function that checks if a point is a vertex of a triangle.
	 *
	 * \param triangle The triangle to test.
	 * \param point The point of the click.
	 * \return 0 if it is the cp1, 1 if it is the cp2, 2 if it is the cp3 and -1 otherwise.
	 */
    int isEqualSommit(Triangle triangle, Couple point);

    /**
	 * \fn int isNeighbour(Triangle tr1, Triangle tr2, Couple *cp)
	 * \brief Function that checks if a triangle is close to another.
	 *
	 * \param tr1 First triangle to test.
	 * \param tr2 Second triangle to test.
	 * \param cp Couple to contain the value of summits of the triangle 
	 * \return 0 if all is well.
	 */
	int isNeighbour(Triangle tr1, Triangle tr2, Couple *cp);

    /**
	 * \fn int square(int ax, int ay, int bx, int by)
	 * \brief Function that calculates the value [3] [3] of a Matrix 3 x 3.
	 *
	 * \param ax Abcissa of summit.
	 * \param ay Ordinate of summit.
	 * \param bx Abcissa of second summit.
	 * \param by Ordinate of second summit.
	 * \return The result of calculation.
	 */
    int square(int ax, int ay, int bx, int by);

    /**
	 * \fn Matrix * createDelaunayMatrix(Point point, Triangle triangle)
	 * \brief Function that creates a Matrix delaunay 3x3.
	 *
	 * \param point To check.
	 * \param triangle To check.
	 * \return A Delaunay matrix of the point and the triangle.
	 */
    Matrix * createDelaunayMatrix(Point point, Triangle triangle);

    /**
	 * \fn int isDelaunay(Couple point, Triangle triangle)
	 * \brief Function that checks if the triangle is Delaunay.
	 *
	 * \param point Point to check.
	 * \param triangle To check.
	 * \return 1 if the triangle is delaunay(det <=0) with the point else 0.
	 */
    int isDelaunay(Couple point, Triangle triangle);

    /**
	 * \fn int removeEdge(Triangle *tr1, Triangle *tr2, Couple cp)
	 * \brief Function that flip a diagonal.
	 *
	 * \param tr1 First triangle create.
	 * \param tr2 Second triangle create.
	 * \param cp Couple to contain data of summit.
	 * \return 0 if all is well.
	 */
	int removeEdge(Triangle *tr1, Triangle *tr2, Couple cp);

    /**
	 * \fn void delaunayTriangle(Triangle *triangle, TabTriangle *listTriangle)
	 * \brief Function that creates the Delaunay triangles.
	 *
	 * \param triangle To check.
	 * \param listTriangle Which contains all triangle.
	 */
    void delaunayTriangle(Triangle *triangle, TabTriangle *listTriangle);

    /**
	 * \fn Matrix* allocateMatrixNxN(int n, int p)
	 * \brief Function that allocates a Matrix n x n.
	 *
	 * \param n The length of the Matrix.
	 * \param p The width of the Matrix.
	 * \return tmp which is the allocated Matrix.
	 */
    Matrix* allocateMatrixNxN(int n, int p);

    /**
	 * \fn void freeMatrix(Matrix *matrix)
	 * \brief Function that free a Matrix.
	 *
	 * \param Matrix The Matrix to free.
	 */
    void freeMatrix(Matrix *matrix);

    /**
	 * \fn long determinantMatrix(Matrix *matrix)
	 * \brief Function that calculates the determinant of the delaunay Matrix.
	 *
	 * \param matrix To determinate the determinant.
	 * \return The determinant of the matrix.
	 */
    long determinantMatrix(Matrix *matrix);

    /**
	 * \fn void initializeArrayTriangleEmpty(TabTriangle *triangle)
	 * \brief Function that initializes an empty triangle array.
	 *
	 * \param triangle List of triangle empty.
	 */
    void initializeArrayTriangleEmpty(TabTriangle *triangle);

    /**
	 * \fn void deformedTriangulatorT(TabTriangle *tmp, double t, TabTriangle listTriangle)
	 * \brief Function that calculates the deformed triangulation.
	 *
	 * \param tmp List of triangle of the deformed triangulation.
	 * \param t Data of frame.
	 * \param listTriangle List triangle original.
	 */
    void deformedTriangulatorT(TabTriangle *tmp, double t, TabTriangle listTriangle);

    /**
	 * \fn void generateFrame(Board p, TabTriangle listTriangle)
	 * \brief Function that generates the rendering.
	 *
	 * \param p Board with image, boolean and number of frame.
	 * \param listTriangle List triangle to genererate pixel.
	 */
    void generateFrame(Board p, TabTriangle listTriangle);

#endif
