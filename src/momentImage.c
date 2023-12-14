/*
 * ENSICAEN
 * 6 Boulevard Maréchal Juin
 * F-14050 Caen Cedex
 *
 * This file is owned by ENSICAEN students. No portion of this
 * document may be reproduced, copied or revised without written
 * permission of the authors.
 */

/**
 * @author Lucas OLLIER <lucas.ollier@ecole.ensicaen.fr>
 * @author Thibault LETOURNEUR <thibaut.letourneur@ecole.ensicaen.fr>
 * @version 1.0.0
 * @date 22 décembre 2022
 *
 * @todo the list of improvements suggested for the file.
 * @bug the list of known bugs.
 */

/**
 * @file momentImage.c
 * @brief Détermination des moments d'une image
 */

#include "momentImage.h"

void give_moments(image self, int numBlock, int n, int m, int* M0, double M1[3], double M2[3]) {
    *M0 = 0;
    for(int k = 0; k < 3; k++) {
        M1[k] = 0;
        M2[k] = 0;
    }

    int* RGB;
    RGB = (int*)malloc(3 * sizeof(int));
    if(RGB == NULL) {
        free(RGB);
        printf("Error molloc RGB\n");
        exit(EXIT_FAILURE);
    }

    int stepL = self->largeur / m;
    int stepH = self->hauteur / n;
    int starty = numBlock / n * stepH;

    Point pos;
    pos.coordx = numBlock % n * stepH;

    for(int i = starty; i < starty + stepH; i++) {
        pos.coordy = i;
        image_move_to(self,&pos);

        for(int j = 0; j < stepL; j++) {
            *M0 += 1;

            RGB = image_lire_pixel(self);
            for(int k = 0; k < 3; k++) {
                M1[k] += RGB[k];
                M2[k] += RGB[k] * RGB[k];
            }
            image_pixel_droite(self);
        }
    }
}