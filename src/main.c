#include "partitionImage.h"

int main() {
    int **tableau;
    int taille1 = 8;
    int taille2 = 8;
    tableau = init_tableau(taille1, taille2);
    afficher_tableau(tableau, taille1, taille2);

    printf("%d\n", image_coordone(5, 0, 30, 25, taille1, taille2));

    return 1;
}