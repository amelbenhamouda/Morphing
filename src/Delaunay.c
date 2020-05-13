#include <stdio.h>
#include <stdlib.h>

#include "./../include/mecanique.h"
#include "./../include/graphique.h"
#include "./../include/Delaunay.h"


void addTriangle(TabTriangle *triangle, Triangle tr) {
    if (triangle->size  >= triangle->tMax) {
        triangle->tMax *= 2;
        triangle->t = (Triangle*)realloc(triangle->t, triangle->tMax * sizeof(Triangle));
        if (triangle->t == NULL) {
            printf("Erreur d'allocation.\n");
            exit(EXIT_FAILURE);
        }
    }    
    triangle->t[triangle->size] = tr;      
    triangle->size += 1;
}

void initializeArrayTriangle(TabTriangle *triangle) {
    Triangle tr1;
    Triangle tr2;

    /* First triangle imposed */
    tr1.cp1.c1.x = 0;
    tr1.cp1.c1.y = 0;
    tr1.cp1.c2.x = 0;
    tr1.cp1.c2.y = 0;

    tr1.cp2.c1.x = 0;
    tr1.cp2.c1.y = SIZE_PICTURE;
    tr1.cp2.c2.x = 0;
    tr1.cp2.c2.y = SIZE_PICTURE;

    tr1.cp3.c1.x = SIZE_PICTURE;
    tr1.cp3.c1.y = SIZE_PICTURE;
    tr1.cp3.c2.x = SIZE_PICTURE;
    tr1.cp3.c2.y = SIZE_PICTURE;

    /* Second triangle imposed */
    tr2.cp1.c1.x = 0;
    tr2.cp1.c1.y = 0;
    tr2.cp1.c2.x = 0;
    tr2.cp1.c2.y = 0;

    tr2.cp2.c1.x = SIZE_PICTURE;
    tr2.cp2.c1.y = SIZE_PICTURE;
    tr2.cp2.c2.x = SIZE_PICTURE;
    tr2.cp2.c2.y = SIZE_PICTURE;

    tr2.cp3.c1.x = SIZE_PICTURE;
    tr2.cp3.c1.y = 0;
    tr2.cp3.c2.x = SIZE_PICTURE;
    tr2.cp3.c2.y = 0;
       
    triangle->size = 0;
    triangle->tMax = 4;
    
    triangle->t = (Triangle*)malloc(sizeof(Triangle) * triangle->tMax);
    if (triangle->t == NULL) {
        printf("Erreur d'allocation.\n");
        exit(EXIT_FAILURE);
    }
    addTriangle(triangle, tr1);
    addTriangle(triangle, tr2);
}

int insertPointAndDelaunay(TabTriangle  *listTriangle,Couple *point) {
    int index = findTriangle((*listTriangle), point->c1);

    remove1Create3Triangle(listTriangle, index, *point);
    delaunayTriangle(&listTriangle->t[index], listTriangle);
    delaunayTriangle(&listTriangle->t[listTriangle->size - 2], listTriangle);
    delaunayTriangle(&listTriangle->t[listTriangle->size - 1], listTriangle);
    return 0;
}

int isPositif(BarycentricCoordinates cordBary) {
    return (cordBary.alpha >= 0 && cordBary.beta >= 0 && cordBary.gamma >= 0);
}

int areaCalcul(Triangle triangle) {
    int A = triangle.cp2.c1.x - triangle.cp1.c1.x;
    int B = triangle.cp2.c1.y - triangle.cp1.c1.y;
    int C = triangle.cp3.c1.x - triangle.cp1.c1.x;
    int D = triangle.cp3.c1.y - triangle.cp1.c1.y;
    return determinant2x2(A, B, C, D); 
}

BarycentricCoordinates calculBarycentricCoordinates(Point p, Triangle triangle) {
    BarycentricCoordinates tmp;
    int aireTriangle = areaCalcul(triangle);
    tmp.alpha = (float)determinant2x2(p.x - triangle.cp1.c1.x, p.y - triangle.cp1.c1.y, p.x - triangle.cp2.c1.x, p.y - triangle.cp2.c1.y) / (float)aireTriangle;
    tmp.beta = (float)determinant2x2(p.x - triangle.cp2.c1.x, p.y - triangle.cp2.c1.y, p.x - triangle.cp3.c1.x, p.y - triangle.cp3.c1.y) / (float)aireTriangle;
    tmp.gamma = (float)determinant2x2(p.x - triangle.cp3.c1.x, p.y - triangle.cp3.c1.y, p.x - triangle.cp1.c1.x, p.y - triangle.cp1.c1.y) / (float)aireTriangle;
    return tmp;
}

int isInTriangle(Point p, Triangle triangle) {
    return isPositif(calculBarycentricCoordinates(p, triangle));
}

long determinant2x2(long c00, long c01, long c10, long c11) {
    return (c00 * c11) - (c01 * c10);
}

int strangeCalcul(int a, int b, int c, int d) {
    return (a - b) * (c - d);
}

int builtCounterclickwiseTriangle(Couple c1, Couple c2, Couple c3, Triangle *triangle) {
    Couple tmp;
    /* Formula triangle ABC : (Cx - Ax) * (By - Ay) - (Bx - Ax) * (Cy - Ay) > 0 */
    if (strangeCalcul(c3.c1.x, c1.c1.x, c2.c1.y, c1.c1.y) - strangeCalcul(c2.c1.x, c1.c1.x, c3.c1.y, c1.c1.y) < 0) {
        /* Swap B and C. */
        tmp = c2;
        c2 = c3;
        c3 = tmp;
    }
    triangle->cp1 = c1;
    triangle->cp2 = c2;
    triangle->cp3 = c3;
    return 0;
}

int findTriangle(TabTriangle listTriangle, Point p) {
    int i;
    for (i = 0; i < listTriangle.size; i++) {
        if (isInTriangle(p, listTriangle.t[i])) {
            break;
        }
    }
    return i;
}

int equalTriangle(Triangle tr1, Triangle tr2) {
    if (equalPoint(tr1.cp1, tr2.cp1) && equalPoint(tr1.cp2, tr2.cp2) && equalPoint(tr1.cp3, tr2.cp3)) {
        return 1;
    }
    return 0;
}

void copyTriangle(Triangle tr, Triangle *tr2) {
    tr2->cp1 = tr.cp1;
    tr2->cp2 = tr.cp2;
    tr2->cp3 = tr.cp3;
}

int remove1Create3Triangle(TabTriangle *triangle, int index, Couple p) {
    Triangle tmp;
    Triangle tmp2;
    Triangle tmp3;
    Couple p1 = triangle->t[index].cp1;
    Couple p2 = triangle->t[index].cp2;
    Couple p3 = triangle->t[index].cp3;

    builtCounterclickwiseTriangle(p2, p1, p, &tmp);
    copyTriangle(tmp, &(triangle->t[index]));
    builtCounterclickwiseTriangle(p3, p2, p, &tmp2);
    builtCounterclickwiseTriangle(p1, p3, p, &tmp3);
    addTriangle(triangle, tmp2);
    addTriangle(triangle, tmp3);
    return 0;
}

int equalPoint(Couple c1, Couple c2) {
    return c1.c1.x == c2.c1.x && c1.c1.y == c2.c1.y && c1.c2.x == c2.c2.x && c1.c2.y == c2.c2.y;
}

int isEqualSommit(Triangle triangle, Couple point) {
    if (equalPoint(triangle.cp1, point)) {
        return 1;
    }
    else if (equalPoint(triangle.cp2, point)) {
        return 2;
    }
    else if (equalPoint(triangle.cp3, point)) {
        return 3;
    }
    else {
        return -1;
    }
}

int isNeighbour(Triangle tr1, Triangle tr2, Couple *cp) {
    int counter = 0;

    int result = isEqualSommit(tr2, tr1.cp1);
    if (result != -1) {
        if (counter == 0) {
            cp->c1.x = 1;
            cp->c2.x = result;
        }
        else {
            cp->c1.y = 1;
            cp->c2.y = result;
        }
        counter++;
    }

    result = isEqualSommit(tr2, tr1.cp2);
    if (result != -1) {
        if (counter == 0) {
            cp->c1.x = 2;
            cp->c2.x = result;
        }
        else {
            cp->c1.y = 2;
            cp->c2.y = result;
        } 
        counter++;
    }

    result = isEqualSommit(tr2, tr1.cp3);
    if (result != -1) {
        if (counter == 0) {
            cp->c1.x = 3;
            cp->c2.x = result;
        } 
        else {
            cp->c1.y = 3;
            cp->c2.y = result;
        }
        counter++;
    }

    if (counter == 2) {
        return 1;
    }
    return 0;
}

int square(int ax, int ay, int bx, int by) {
    return (((ax * ax) - (bx * bx)) + ((ay * ay) - (by * by)));
}

Matrix * createDelaunayMatrix(Point point, Triangle triangle) {
    Matrix *tmp;
    tmp = allocateMatrixNxN(3, 3);
 
    tmp->mat[0][0] = triangle.cp3.c1.x - point.x;
    tmp->mat[0][1] = triangle.cp3.c1.y - point.y;
    tmp->mat[0][2] = square(triangle.cp3.c1.x, triangle.cp3.c1.y, point.x, point.y);

    tmp->mat[1][0] = triangle.cp2.c1.x - point.x;
    tmp->mat[1][1] = triangle.cp2.c1.y - point.y;
    tmp->mat[1][2] = square(triangle.cp2.c1.x, triangle.cp2.c1.y, point.x, point.y);
  
    tmp->mat[2][0] = triangle.cp1.c1.x - point.x;
    tmp->mat[2][1] = triangle.cp1.c1.y - point.y;
    tmp->mat[2][2] = square(triangle.cp1.c1.x, triangle.cp1.c1.y, point.x, point.y);
  
    return tmp;
}

int isDelaunay(Couple point, Triangle triangle) {
    Matrix *tmp = createDelaunayMatrix(point.c1, triangle);
    long det = determinantMatrix(tmp);
    freeMatrix(tmp);
    return det <= 0;
}

int removeEdge(Triangle *tr1, Triangle *tr2, Couple cp) {
    Couple a;
    Couple b; 
    Couple c;
    Couple d;

    int ncouple = cp.c1.x;
    switch (ncouple) {
        case 1: a = tr1->cp1; break;
        case 2: a = tr1->cp2; break;
        case 3: a = tr1->cp3; break;
    }

    ncouple = cp.c1.y;
    switch (ncouple) {
        case 1: b = tr1->cp1; break;
        case 2: b = tr1->cp2; break;
        case 3: b = tr1->cp3; break;
    }

    ncouple = ((cp.c1.x + cp.c1.y) * 2) % 3;
    switch (ncouple) {
        case 0: c = tr1->cp3; break;
        case 1: c = tr1->cp1; break;
        case 2: c = tr1->cp2; break;
    }
    
    ncouple = ((cp.c2.x + cp.c2.y) * 2) % 3;
    switch (ncouple) {
        case 0: d = tr2->cp3; break;
        case 1: d = tr2->cp1; break;
        case 2: d = tr2->cp2; break;
    }

    builtCounterclickwiseTriangle(a, d, c, tr1);
    builtCounterclickwiseTriangle(b, c, d, tr2);
    return 0;
}

void delaunayTriangle(Triangle *triangle, TabTriangle *listTriangle) {
    int i;
    Couple ctmp;
    Couple cp;
    for (i = 0; i < listTriangle->size + 1; i++) {
        if (i == listTriangle->size) {
            return;
        }
        if (equalTriangle((*triangle), listTriangle->t[i])) {
            continue;
        }
        if (isNeighbour((*triangle), listTriangle->t[i], &cp) == 1) {
            int ncouple = ((cp.c2.x + cp.c2.y) * 2) % 3;
            switch (ncouple) {
                case 0: ctmp = listTriangle->t[i].cp3; break;
                case 1: ctmp = listTriangle->t[i].cp1; break;
                case 2: ctmp = listTriangle->t[i].cp2; break;
            }
            if (!isDelaunay(ctmp, (*triangle))) {
                break;
            }
        }
    }
    removeEdge(triangle, &listTriangle->t[i], cp);
    delaunayTriangle(triangle, listTriangle);
    delaunayTriangle(&listTriangle->t[i], listTriangle);
}

Matrix* allocateMatrixNxN(int n, int p) {
    Matrix* tmp = malloc(sizeof(Matrix));
    if (tmp == NULL) {
        printf("La Matrix n'a pas pu etre allouée.\n");
        exit(EXIT_FAILURE);
    }
    tmp->n = n;
    tmp->p = p;
    tmp->mat = (long**)malloc(sizeof(long*) * n);
    if (tmp->mat == NULL) {
        printf("Le tableau n'a pas pu etre allouée.\n");
        exit(EXIT_FAILURE);
    }

    int i;
    for (i = 0; i < n; i++) {
        tmp->mat[i] = (long*)malloc(sizeof(long) * p);
        if (tmp->mat[i] == NULL) {
            printf("Le tableau n'a pas pu etre allouée.\n");
            exit(EXIT_FAILURE);
        }
    }

    int j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < p; j++) {
            tmp->mat[i][j] = 1;
        }
    }
    return tmp;
}

void freeMatrix(Matrix *matrix) {
    int i;
    for (i = 0; i < matrix->n; i++) {
        free(matrix->mat[i]);
    }
    free(matrix->mat);
    free(matrix);
}

long determinantMatrix(Matrix *matrix) {
    long A = matrix->mat[0][0] * matrix->mat[1][1] * matrix->mat[2][2];
    long B = matrix->mat[0][1] * matrix->mat[1][2] * matrix->mat[2][0];
    long C = matrix->mat[1][0] * matrix->mat[2][1] * matrix->mat[0][2];
    long D = matrix->mat[2][0] * matrix->mat[1][1] * matrix->mat[0][2];
    long E = matrix->mat[0][0] * matrix->mat[2][1] * matrix->mat[1][2];
    long F = matrix->mat[1][0] * matrix->mat[0][1] * matrix->mat[2][2];

    return ((A + B + C) - (D + E + F));
}

void initializeArrayTriangleEmpty(TabTriangle *triangle) {
    triangle->size = 0;
    triangle->tMax = 4;
    triangle->t = (Triangle*)malloc(sizeof(Triangle) * triangle->tMax);
    if (triangle->t == NULL) {
        printf("Erreur d'allocation.\n");
        exit(EXIT_FAILURE);
    }  
}

void deformedTriangulatorT(TabTriangle *tmp, double t, TabTriangle listTriangle) {
    Triangle tritmp;
    int i;

    for (i = 0; i < listTriangle.size; i++) {
        tritmp.cp1.c2.x = listTriangle.t[i].cp1.c2.x;
        tritmp.cp1.c2.y = listTriangle.t[i].cp1.c2.y;
        tritmp.cp2.c2.x = listTriangle.t[i].cp2.c2.x;
        tritmp.cp2.c2.y = listTriangle.t[i].cp2.c2.y;
        tritmp.cp3.c2.x = listTriangle.t[i].cp3.c2.x;
        tritmp.cp3.c2.y = listTriangle.t[i].cp3.c2.y;
        
        tritmp.cp1.c1.x = ((double) 1 - t) * listTriangle.t[i].cp1.c1.x + t * listTriangle.t[i].cp1.c2.x;
        tritmp.cp1.c1.y = ((double) 1 - t) * listTriangle.t[i].cp1.c1.y + t * listTriangle.t[i].cp1.c2.y;
        tritmp.cp2.c1.x = ((double) 1 - t) * listTriangle.t[i].cp2.c1.x + t * listTriangle.t[i].cp2.c2.x;
        tritmp.cp2.c1.y = ((double) 1 - t) * listTriangle.t[i].cp2.c1.y + t * listTriangle.t[i].cp2.c2.y;
        tritmp.cp3.c1.x = ((double) 1 - t) * listTriangle.t[i].cp3.c1.x + t * listTriangle.t[i].cp3.c2.x;
        tritmp.cp3.c1.y = ((double) 1 - t) * listTriangle.t[i].cp3.c1.y + t * listTriangle.t[i].cp3.c2.y;

        addTriangle(tmp, tritmp);
    }
}

void generateFrame(Board p, TabTriangle listTriangle) {
    int indexFrame, absc, ord;
    BarycentricCoordinates cordBary;
    TabTriangle tmp;
    Point point;
    double t;
  
    for (indexFrame = 0; indexFrame < p.nbFrame; indexFrame++) {
        initializeArrayTriangleEmpty(&tmp);
        t = (double)indexFrame / (double)p.nbFrame;
        deformedTriangulatorT(&tmp, t, listTriangle);
        for (absc = 0; absc < SIZE_PICTURE; absc++) {
            for (ord = 0; ord < SIZE_PICTURE; ord++) {
                point.x = absc;
                point.y = ord;
                int index = findTriangle(tmp, point);
                cordBary = calculBarycentricCoordinates(point, tmp.t[index]);
                Couple point2;
                point2.c1.x = (cordBary.alpha*listTriangle.t[index].cp3.c1.x)+(cordBary.beta * listTriangle.t[index].cp1.c1.x) + (cordBary.gamma * listTriangle.t[index].cp2.c1.x) / (cordBary.alpha + cordBary.beta + cordBary.gamma);
                point2.c1.y = (cordBary.alpha*listTriangle.t[index].cp3.c1.y)+(cordBary.beta * listTriangle.t[index].cp1.c1.y) + (cordBary.gamma * listTriangle.t[index].cp2.c1.y) / (cordBary.alpha + cordBary.beta + cordBary.gamma);
                point2.c2.x = (cordBary.alpha*listTriangle.t[index].cp3.c2.x)+(cordBary.beta * listTriangle.t[index].cp1.c2.x) + (cordBary.gamma * listTriangle.t[index].cp2.c2.x) / (cordBary.alpha + cordBary.beta + cordBary.gamma);
                point2.c2.y = (cordBary.alpha*listTriangle.t[index].cp3.c2.y)+(cordBary.beta * listTriangle.t[index].cp1.c2.y) + (cordBary.gamma * listTriangle.t[index].cp2.c2.y) / (cordBary.alpha + cordBary.beta + cordBary.gamma);

                ColorPixel pixelImDep;
                pixelImDep.p = point2.c1;
                ColorPixel pixelImArr;
                pixelImArr.p = point2.c2;
                MLV_get_pixel_on_image(p.picture1, pixelImDep.p.x, pixelImDep.p.y, &pixelImDep.red, &pixelImDep.green, &pixelImDep.blue, &pixelImDep.alpha);
                MLV_get_pixel_on_image(p.picture2, pixelImArr.p.x, pixelImArr.p.y, &pixelImArr.red, &pixelImArr.green, &pixelImArr.blue, &pixelImArr.alpha);
                MLV_draw_pixel(IMAG_DEP_X + absc, IMAG_DEP_Y + ord, MLV_rgba((double)(1 - t) * pixelImDep.red + t * pixelImArr.red, (double)(1 - t) * pixelImDep.green + t * pixelImArr.green, (double)(1 - t) * pixelImDep.blue + t * pixelImArr.blue, (double)(1 - t) * pixelImDep.alpha + t * pixelImArr.alpha));
            }
        }
        free(tmp.t);
        MLV_actualise_window();
    }
}
