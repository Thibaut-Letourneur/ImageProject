#ifndef PARTITIONIMAGE_H
#define PARTITIONIMAGE_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Initialisation du tableau.
 *
 * @param n Nombre de ligne
 * @param m Nombre de colone
 *
 * @return Alocation du tableau dynamic
 */
extern int** init_tableau(int n, int m);

/**
 * @brief Liberation de l'espace aloué du tableau.
 *
 * @param t Tableau dynamic a liberer
 * @param n Tombre de ligne
 * @param m Nombre de colone
 */
extern void liberation_tableau(int **t, int n, int m);

/**
 * @brief Affichage du tableau.
 *
 * @param t Tableau dynamic a afficher
 * @param n Nombre de ligne
 * @param m Nombre de colone
 */
extern void afficher_tableau(int **t, int n, int m);

/**
 * @brief Determination des voisins.
 *
 * @param t Tableau dynamic
 * @param p Numero d'une case du tableau
 * @param n Nombre de ligne
 * @param m Nombre de colone
 *
 * @return Tableau des voisins
 */
extern int* voisin_case(int **t, int p, int n, int m);

/**
 * @brief Determination du blocs en fonction dans une image de taille L x H.
 *
 * @param x Position sur l'axe des x dans l'image
 * @param y Position sur l'axe des y dans l'image
 * @param L Nombre de pixel sur l'axe des x
 * @param H Nombre de pixel sur l'axe des y
 * @param n Nombre de ligne
 * @param m Nombre de colone
 *
 * @return Bloc dans lequel on se trouve
 */
extern int image_coordone(int x, int y, int L, int H, int n, int m);


#endif