#ifndef MOMENTIMAGE_H
#define MOMENTIMAGE_H

#include <stdio.h>
#include <stdlib.h>
#include "image.h"

/**
 * @brief Calcule des moments d'une image.
 *
 * @param self Image dans laquel on cherche les moments
 * @param numBlock Numero du block dans lequel on calcule de moment
 * @param n Nombre de ligne
 * @param m Nombre de colone
 * @param M0 Adresse du moment 0 (entier)
 * @param M1 Adresse du moment 1 (tableau de taille 3 d'entier)
 * @param M2 Adresse du moment 2 (tableau de taille 3 d'entier)
 */
extern void give_moments(image self, int numBlock, int n, int m, int* M0, double M1[3], double M2[3]);

#endif