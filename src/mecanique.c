#include <stdio.h>
#include <stdlib.h>

#include "./../include/mecanique.h"


int inPictureOrButton(Clic clic) {
    if ((clic.x >= 142 && clic.x <= 292) && (clic.y >= SIZE_PICTURE + (3 * IMAG_DEP_Y) && clic.y <= SIZE_PICTURE + (5 * IMAG_DEP_Y))) {
        return 0;
    }
    else if ((clic.x >= 302  && clic.x <= 462) && (clic.y >= SIZE_PICTURE + (3 * IMAG_DEP_Y) && clic.y <= SIZE_PICTURE + (5 * IMAG_DEP_Y))) {
        return 1;
    }
    else if ((clic.x >= 472 && clic.x <= 602) && (clic.y >= SIZE_PICTURE + (3 * IMAG_DEP_Y) && clic.y <= SIZE_PICTURE + (5 * IMAG_DEP_Y))) {
        return 2;
    }
    else if ((clic.x >= 612  && clic.x <= 662) && (clic.y >= SIZE_PICTURE + (3 * IMAG_DEP_Y) && clic.y <= SIZE_PICTURE + (5 * IMAG_DEP_Y))) {
        return 3;
    }
    else if ((clic.x >= 782 && clic.x <= 832) && (clic.y >= SIZE_PICTURE + (3 * IMAG_DEP_Y) && clic.y <= SIZE_PICTURE + (5 * IMAG_DEP_Y))) {
        return 4;
    }
    else if ((clic.x >= 842 && clic.x <= 902) && (clic.y >= SIZE_PICTURE + (3 * IMAG_DEP_Y) && clic.y <= SIZE_PICTURE + (5 * IMAG_DEP_Y))) {
        return 5;
    }
    else  if ((clic.x >= IMAG_DEP_X && clic.x <= SIZE_PICTURE + IMAG_DEP_X) && (clic.y >= IMAG_DEP_Y && clic.y <= SIZE_PICTURE + IMAG_DEP_Y)) {
        return 6;
    }
    else if ((clic.x >= SIZE_WINDOW_H - SIZE_PICTURE - IMAG_DEP_X  && clic.x <= SIZE_WINDOW_H - IMAG_DEP_X) && (clic.y >= IMAG_DEP_Y && clic.y <= SIZE_PICTURE + IMAG_DEP_Y)) {
        return 7;
    }
    return -1;
}
