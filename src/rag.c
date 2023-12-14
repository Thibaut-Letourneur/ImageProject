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
 * @file rag.c
 * @brief Fonction de creation et de manipulation d'un graphe d’adjacence de régions
 */


#include "rag.h"


static void init_moments_priv(rag,int,int);
static void init_father_priv(rag);
static void init_neighbors_priv(rag,int,int);
static void init_partition_error_priv(rag);
static double error_between_two_block(rag, int, int);
static void change_moments(rag self, int i, int j);
static void change_neighbors(rag self, int i, int j);


rag create_RAG(image img, int n, int m) {
    rag self;
    self = (rag)malloc(sizeof(struct RAG));

    self->nb_blocks = n * m;
    self->img = img;
    
    init_moments_priv(self, n, m);
    init_neighbors_priv(self, n, m);
    init_partition_error_priv(self);
    init_father_priv(self);
    return self;
}

void init_moments_priv(rag self, int n, int m) {
    self->m = (moments)malloc(self->nb_blocks * sizeof(struct MOMENTS));
    if(self->m == NULL) {
        free(self->m);
        printf("Error malloc momments rag");
        exit(EXIT_FAILURE);
    }

    for(int block = 0; block < self->nb_blocks; block++) {
        give_moments(self->img, block, n, m, &(self->m[block].M0), self->m[block].M1, self->m[block].M2);
    }
}

void init_father_priv(rag self) {
    self->father = (int*)malloc(self->nb_blocks * sizeof(int));
    if(self->father == NULL) {
        free(self->father);
        printf("Erreur malloc father rag");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < self->nb_blocks; i++) {
        self->father[i] = i;
    }
}

void init_neighbors_priv(rag self, int n, int m) {
    self->neighbors = (cellule*)malloc(self->nb_blocks * sizeof(cellule));
    if(self->neighbors == NULL) {
        free(self->neighbors);
        printf("Erreur malloc neighbors rag");
        exit(EXIT_FAILURE);
    }

    int **tab;
    tab = init_tableau(n, m);

    int *voisin;
    cellule cell;
    cellule temp;
    int j;
    for(int block = 0; block < self->nb_blocks; block++) {
        j = 0;
        voisin = voisin_case(tab, block, n, m);
        for(int i = 0; i < 4; i++) {
            if(voisin[i] > block) {
                if(j == 0) {
                    cell = (cellule)malloc(sizeof(struct CELLULE));
                    if(cell == NULL) {
                        free(cell);
                        printf("Erreur malloc cellule of neighbors rag");
                        exit(EXIT_FAILURE);
                    }

                    cell->block = voisin[i];
                    self->neighbors[block] = cell;
                    temp = cell;
                } else {
                    cell = (cellule)malloc(sizeof(struct CELLULE));
                    if(cell == NULL) {
                        free(cell);
                        printf("Erreur malloc cellule of neighbors rag");
                        exit(EXIT_FAILURE);
                    }

                    cell->block = voisin[i];
                    temp->next = cell;
                    temp = cell;
                }
                j++;
            }
        }
        if(j == 0) {
            self->neighbors[block] = NULL;
        } else {
            temp->next = NULL;
        }
    }
}

void init_partition_error_priv(rag self) {
    long double error = 0;
    for(int block = 0; block < self->nb_blocks; block++) {
        for(int i = 0; i < 3; i++) {
            error += self->m[block].M2[i] - ((self->m[block].M1[i] * self->m[block].M1[i]) / self->m[block].M0);
        }
    }
    self->erreur_partition = error;
}


void RAG_give_closest_region(rag self, int* B1, int* B2) {
    *B1 = 0;
    *B2 = 1;
    double temp;
    double erreur = error_between_two_block(self, *B1, *B2);

    for(int i = 0; i < self->nb_blocks; i++) {
        for(int j = 0; j < self->nb_blocks; j++) {
            if(i != j) {
                temp = error_between_two_block(self, i, j);
                if(temp < erreur) {
                    erreur = temp;
                    *B1 = i;
                    *B2 = j;
                }
            }
        }
    }
}

double error_between_two_block(rag self, int B1, int B2) {
    int result;
    result = ((self->m[B1].M1[0] - self->m[B2].M1[0]) / self->m[B2].M0)*((self->m[B1].M1[0] - self->m[B2].M1[0]) / self->m[B2].M0);
    result += ((self->m[B1].M1[1] - self->m[B2].M1[1]) / self->m[B2].M0)*((self->m[B1].M1[1] - self->m[B2].M1[1]) / self->m[B2].M0);
    result += ((self->m[B1].M1[2] - self->m[B2].M1[2]) / self->m[B2].M0)*((self->m[B1].M1[2] - self->m[B2].M1[2]) / self->m[B2].M0);

    return result * (self->m[B1].M0 * self->m[B2].M0)/(self->m[B1].M0 + self->m[B2].M0);
}



void RAG_merge_region(rag self, int B1, int B2) {
    int i, j;
    if(B1 < B2) {
        i = B1;
        j = B2;
    } else {
        j = B1;
        i = B2;
    }

    self->father[i] = j;

    change_moments(self, i, j);
    change_neighbors(self, i, j);
    self->erreur_partition = error_between_two_block(self, i, j);
}


void change_moments(rag self, int i, int j) {
    self->m[j].M0 += self->m[i].M0;
    for(int k = 0; k < 3; k++) {
        self->m[j].M1[k] += self->m[i].M1[k];
        self->m[j].M2[k] += self->m[i].M2[k];
    }
}


void change_neighbors(rag self, int i, int j) {
    cellule cellI = self->neighbors[i];
    cellule cellJ = self->neighbors[j];
    cellule temp;

    while(cellJ != NULL) {
        if(cellI == NULL) {
            break;
        }

        if(cellI->block != j) {
            if(cellI->block < cellJ->block) {
                self->neighbors[j] = cellI;
                cellI = cellI->next;
                self->neighbors[j]->next = cellJ;
                cellJ = cellJ->next;
            }

            if(cellI->block > cellJ->block) {
                if((cellJ->next != NULL) && (cellI->block < cellJ->next->block)) {
                    temp = cellJ->next;
                    cellJ->next = cellI;
                    cellI = cellI->next;
                    cellJ->next->next = temp;
                    cellJ = temp;
                } else if(cellJ->next == NULL) {
                    cellJ->next = cellI;
                    cellI = cellI->next;
                    cellJ = cellJ->next;
                    cellJ->next = NULL;
                }
            }
        } else {
            temp = cellI->next;
            free(cellI);
            cellI = temp;
        }
    }

    self->neighbors[i] = NULL;
}