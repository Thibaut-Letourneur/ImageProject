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
 * @file partitionImage.c
 * @brief Fonction de base pour la partition d'une image
 */

#include "partitionImage.h"

static int bas(int p, int n, int m);
static int haut(int p, int m);
static int droite(int p, int m);
static int gauche(int p, int m);


int** init_tableau(int n, int m) {
    int i, j;
    int** t;
    t = malloc(n * sizeof(*t));

    if (t == NULL) {
        free(t);
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n; i++) {
        t[i] = malloc(m * sizeof(**t));
        
        if (t[i] == NULL) {
            liberation_tableau(t, n, m);
            exit(EXIT_FAILURE);
        }
        for(j = 0; j < m; j++) {
            t[i][j] = j + m * i;
        }
    }

    return t;
}


void liberation_tableau(int **t, int n, int m) {
    int i;
    for (i = 0; i < n; i++) {
        free(t[i]);
    }
    free(t);
    t = NULL;
}


void afficher_tableau(int **t, int n, int m) {
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            if(t[i][j] <= 9) {
                printf(" %d ", t[i][j]);
            } else {
                printf("%d ", t[i][j]);
            }
        }
        printf("\n");
    }
}


int* voisin_case(int **t, int p, int n, int m) {
    int *voisin = malloc(4 * sizeof(int));
    int i = 0;
    
    for(i = 0; i < 4; i++) {
        switch (i)
        {
        case 0:
            if(haut(p, m)) {
                voisin[i] = t[(int)(p / m) - 1][p % m];
                break;
            }
            voisin[i] = -1;
            break;
        
        case 1:
            if(gauche(p, m)) {
                voisin[i] = t[(int)(p / m)][p % m - 1];
                break;
            }
            voisin[i] = -1;
            break;
        
        case 2:
            if(droite(p, m)) {
                voisin[i] = t[(int)(p / m)][p % m + 1];
                break;
            }
            voisin[i] = -1;
            break;
        
        case 3:
            if(bas(p, n, m)) {
                voisin[i] = t[(int)(p / m) + 1][p % m];
                break;
            }
            voisin[i] = -1;
            break;
        
        default:
            break;
        }
    }
    
    return voisin;
}


int bas(int p, int n, int m) { return p >= m * (n - 1) ? 0 : 1; }
int haut(int p, int m) { return p < m ? 0 : 1; }
int droite(int p, int m) { return p % m == m-1 ? 0 : 1; }
int gauche(int p, int m) { return p % m == 0 ? 0 : 1; }


int image_coordone(int x, int y, int L, int H, int n, int m) {
    int posL = x * m / L;
    int posH = y * n / H;
    return (posL + posH * m);
}