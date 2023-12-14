#include "minunit.h"
#include "partitionImage.h"
#include "momentImage.h"
#include "rag.h"
#include "performMerge.h"


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



MU_TEST(test_perform_merge) {
    perform_merge(rag_var, 10000);
    printf("erreur : %Lf\n", rag_var->erreur_partition);

    printf("\nTest of perform fusion: successfully\n");
}



MU_TEST_SUITE(test_suite) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_perform_merge);
}


int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    printf("All test passed succesfuly\n");
    return MU_EXIT_CODE;
}