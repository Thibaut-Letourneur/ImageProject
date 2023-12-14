#include "minunit.h"
#include "partitionImage.h"


int **tableau;
int taille1;
int taille2;


void test_setup(void) {
    taille1 = 5;
    taille2 = 6;
    tableau = init_tableau(taille1, taille2);
}


void test_teardown(void) {
    liberation_tableau(tableau, taille1, taille2);
}


MU_TEST(test_init_tableau) {
    int tab[5][6] = {{ 0, 1, 2, 3, 4, 5},
                     { 6, 7, 8, 9,10,11},
                     {12,13,14,15,16,17},
                     {18,19,20,21,22,23},
                     {24,25,26,27,28,29}};

    int i, j;
    for(i = 0; i < taille1; i++) {
        for(j = 0; j < taille2; j++) {
            mu_check(tableau[i][j] == tab[i][j]);
        }
    }
    printf("\nTest of init_tableau : successfully\n");
}


MU_TEST(test_voisin_tableau) {
    int i;
    int* tab;
    int check_tab[5][4] = {{15,  3, 10,  8}, 
                           {11, -1, -1,  3},
                           {24, 12, 19, -1},
                           {-1, 20, 27, 25},
                           {-1, 23, -1, 28}};


    tab = voisin_case(tableau, 9, taille1, taille2);
    for(i = 0; i < 4; i++) {
        mu_check(tab[i] == check_tab[0][i]);
    }
    
    tab = voisin_case(tableau, 5, taille1, taille2);
    for(i = 0; i < 2; i++) {
        mu_check(tab[i] == check_tab[1][i]);
    }
    
    tab = voisin_case(tableau, 18, taille1, taille2);
    for(i = 0; i < 3; i++) {
        mu_check(tab[i] == check_tab[2][i]);
    }
    
    tab = voisin_case(tableau, 26, taille1, taille2);
    for(i = 0; i < 3; i++) {
        mu_check(tab[i] == check_tab[3][i]);
    }
    
    tab = voisin_case(tableau, 29, taille1, taille2);
    for(i = 0; i < 2; i++) {
        mu_check(tab[i] == check_tab[4][i]);
    }
    printf("\nTest of voisin_case : successfully\n");
}


MU_TEST(test_image_coordone) {
    mu_check(image_coordone(0, 0, 30, 25, taille1, taille2) == 0);
    mu_check(image_coordone(5, 0, 30, 25, taille1, taille2) == 1);
    printf("\nTest of image_coordone : successfully\n");
}

MU_TEST_SUITE(test_suite) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_init_tableau);
    MU_RUN_TEST(test_voisin_tableau);
    MU_RUN_TEST(test_image_coordone);
}


int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    printf("All test passed succesfuly\n");
    return MU_EXIT_CODE;
}