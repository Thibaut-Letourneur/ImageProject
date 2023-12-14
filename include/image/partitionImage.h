#ifndef PARTITIONIMAGE_HEADER
#define PARTITIONIMAGE_HEADER


#include <stdio.h>
#include <stdlib.h>

/**
 * @brief initialisation du tableau.
 *
 * @param n nombre de ligne
 * @param m nombre de colone
 *
 * @return alocation du tableau dynamic
 */
extern int** init_tableau(int n, int m);

/**
 * @brief liberation de l'espace aloué du tableau.
 *
 * @param t tableau dynamic a liberer
 * @param n nombre de ligne
 * @param m nombre de colone
 */
extern void liberation_tableau(int **t, int n, int m);

/**
 * @brief affichage du tableau.
 *
 * @param t tableau dynamic a afficher
 * @param n nombre de ligne
 * @param m nombre de colone
 */
extern void afficher_tableau(int **t, int n, int m);

/**
 * @brief Determination des voisins.
 *
 * @param t tableau dynamic
 * @param p numero d'une case du tableau
 * @param n nombre de ligne
 * @param m nombre de colone
 *
 * @return tableau des voisins
 */
extern int* voisin_case(int **t, int p, int n, int m);

/**
 * @brief Determination du blocs en fonction dans une image de taille L x H.
 *
 * @param x position sur l'axe des x dans l'image
 * @param y position sur l'axe des y dans l'image
 * @param L nombre de pixel sur l'axe des x
 * @param H nombre de pixel sur l'axe des y
 * @param n nombre de ligne
 * @param m nombre de colone
 *
 * @return bloc dans lequel on se trouve
 */
extern int image_coordone(int x, int y, int L, int H, int n, int m);

static int bas(int p, int n, int m);
static int haut(int p, int m);
static int droite(int p, int m);
static int gauche(int p, int m);

#endif