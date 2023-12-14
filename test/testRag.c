#include "minunit.h"
#include "partitionImage.h"
#include "momentImage.h"
#include "rag.h"


int **tableau;
int n;
int m;
image img;
rag rag_var;


void test_setup(void) {
    n = 8;
    m = 8;
    tableau = init_tableau(n, m);

    img = FAIRE_image();
    if(image_charger(img, "IMAGES/deg.ppm") < 0) {
        printf("invalid image.\n");
        exit(EXIT_FAILURE);
    }

    rag_var = create_RAG(img, n, m);
}


void test_teardown(void) {
    liberation_tableau(tableau, n, m);
    DEFAIRE_image(img);
}


MU_TEST(test_moment_RAG) {
    int M0;
    double M1[3], M2[3];
    int starty;
    
    int numBlock = 0;
    int stepL = img->largeur / m;
    int stepH = img->hauteur / n;

    double temp_sum, sum, sum2;
    for(numBlock = 0; numBlock < n*m; numBlock++) {
        starty = numBlock / n * stepH;
        mu_assert_int_eq(rag_var->m[numBlock].M0, stepL * stepH);

        temp_sum = (starty * (starty - 1)) / 2;
        sum = ((starty + stepH) * (starty + stepH - 1)) / 2 - temp_sum;
        mu_assert_double_eq(rag_var->m[numBlock].M1[0], stepL * sum);
        mu_assert_double_eq(rag_var->m[numBlock].M1[1], stepL * stepH * 255);
        mu_assert_double_eq(rag_var->m[numBlock].M1[2], stepL * stepH * 255);

        temp_sum = (starty * (starty - 1) * (2*starty - 1)) / 6;
        sum2 = ((starty + stepH) * (starty + stepH - 1) * (2*(starty + stepH) - 1)) / 6 - temp_sum;
        mu_assert_double_eq(rag_var->m[numBlock].M2[0], stepL * sum2);
        mu_assert_double_eq(rag_var->m[numBlock].M2[1], stepL * stepH * 255 * 255);
        mu_assert_double_eq(rag_var->m[numBlock].M2[2], stepL * stepH * 255 * 255);



    }
    printf("\nTest of RAG momments : successfully\n");
}


MU_TEST(test_voisin_RAG) {
    cellule cell;
    for(int block = 0; block < n*m; block++) {
        cell = rag_var->neighbors[block];
        while(cell != NULL) {
            mu_check(cell->block > block);
            cell = cell->next;
        }
    }
    printf("\nTest of RAG neighbors : successfully\n");
}


MU_TEST(test_erreur_partition_RAG) {
    int M0;
    double M1[3], M2[3];
    double starty;
    
    int numBlock = 0;
    double stepL = img->largeur / m;
    double stepH = img->hauteur / n;
    long double result = 0;
    double temp_sum, sum, sum2;
    for(numBlock = 0; numBlock < n*m; numBlock++) {
        starty = numBlock / n * stepH;

        temp_sum = (starty * (starty - 1)) / 2;
        sum = ((starty + stepH) * (starty + stepH - 1)) / 2 - temp_sum;
        
        temp_sum = (starty * (starty - 1) * (2*starty - 1)) / 6;
        sum2 = ((starty + stepH) * (starty + stepH - 1) * (2*(starty + stepH) - 1)) / 6 - temp_sum;

        result += (stepL * sum2) - ((stepL * sum * stepL * sum) / (stepL * stepH));
        result += (stepL * stepH * 255 * 255) - ((stepL * stepH * 255 * stepL * stepH * 255) / (stepL * stepH));
        result += (stepL * stepH * 255 * 255) - ((stepL * stepH * 255 * stepL * stepH * 255) / (stepL * stepH));
    }
    mu_assert_double_eq(rag_var->erreur_partition, result);
    printf("\nTest of RAG partition error : successfully\n");
}


MU_TEST(test_fusion_RAG) {
    RAG_merge_region(rag_var, 35, 36);
    mu_assert_int_eq(rag_var->neighbors[36]->block, 37);
    mu_assert_int_eq(rag_var->neighbors[36]->next->block, 43);
    mu_assert_int_eq(rag_var->neighbors[36]->next->next->block, 44);

    printf("\nTest of RAG fusion : successfully\n");
}



MU_TEST_SUITE(test_suite) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_moment_RAG);
    MU_RUN_TEST(test_voisin_RAG);
    MU_RUN_TEST(test_erreur_partition_RAG);
    MU_RUN_TEST(test_fusion_RAG);
}


int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    printf("All test passed succesfuly\n");
    return MU_EXIT_CODE;
}