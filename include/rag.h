#ifndef RAG_H
#define RAG_H

#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "momentImage.h"
#include "partitionImage.h"

typedef struct MOMENTS *moments;
struct MOMENTS {
    int M0;
    double M1[3];
    double M2[3];
};

typedef struct CELLULE *cellule;
struct CELLULE {
    int block;
    cellule next;
};

typedef struct RAG * rag;
struct RAG  {
    image img;
    int nb_blocks;
    long double erreur_partition;
    moments m;
    int *father;
    cellule *neighbors;
};


/**
 * @brief Creation du graphe d’adjacence de regions
 *
 * @param img Image dont on veux determiner le graphe d’adjacence de regions
 * @param n Nombre de ligne
 * @param m Nombre de colone
 * 
 * @return Graphe d’adjacence de regions
 */
extern rag create_RAG(image img, int n, int m);


/**
 * @brief Determination des deux indices dont la fusion induit la plus petite augmentation d’erreur quadratique
 *
 * @param self Graphe d’adjacence de regions utilise pour la fusion
 * @param indice1 Adresse du premier indice
 * @param indice2 Adresse du second indice
 */
extern void RAG_give_closest_region(rag self, int* indice1, int* indice2);

extern void RAG_merge_region(rag self, int B1, int B2);

#endif