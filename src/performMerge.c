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
 * @date 31 décembre 2022
 *
 * @todo the list of improvements suggested for the file.
 * @bug the list of known bugs.
 */

/**
 * @file performMerge.c
 * @brief A_MODIFIER
 */

#include "performMerge.h"

void perform_merge(rag self,double seuil) {
    int b1;
    int b2;
    while(self->erreur_partition > seuil) {
        RAG_give_closest_region(self, &b1, &b2);
        printf("b1 : %d, b2 : %d\n", b1, b2);
        RAG_merge_region(self, b1, b2);
        printf("erreur : %Lf\n", self->erreur_partition);
    }
}