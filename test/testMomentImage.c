#include "minunit.h"
#include "partitionImage.h"
#include "momentImage.h"


int **tableau;
int n;
int m;
image img;


void test_setup(void) {
    n = 16;
    m = 8;
    tableau = init_tableau(n, m);

    img = FAIRE_image();
    if(image_charger(img, "IMAGES/deg.ppm") < 0) {
        printf("invalid image.\n");
        exit(EXIT_FAILURE);
    }
}


void test_teardown(void) {
    liberation_tableau(tableau, n, m);
    DEFAIRE_image(img);
}


MU_TEST(test_image_moment) {
    int M0;
    double M1[3], M2[3];
    int starty;
    
    int numBlock = 0;
    int stepL = img->largeur / m;
    int stepH = img->hauteur / n;

    for(numBlock = 0; numBlock < n*m; numBlock++) {
        starty = numBlock / n * stepH;
        give_moments(img, numBlock, n, m, &M0, M1, M2);

        mu_assert_int_eq(M0, stepL * stepH);

        int temp_sum = (starty * (starty - 1)) / 2;
        int sum = ((starty + stepH) * (starty + stepH - 1)) / 2 - temp_sum;
        mu_assert_double_eq(M1[0], stepL * sum);
        mu_assert_double_eq(M1[1], stepL * stepH * 255);
        mu_assert_double_eq(M1[2], stepL * stepH * 255);

        temp_sum = (starty * (starty - 1) * (2*starty - 1)) / 6;
        sum = ((starty + stepH) * (starty + stepH - 1) * (2*(starty + stepH) - 1)) / 6 - temp_sum;
        mu_assert_double_eq(M2[0], stepL * sum);
        mu_assert_double_eq(M2[1], stepL * stepH * 255 * 255);
        mu_assert_double_eq(M2[2], stepL * stepH * 255 * 255);

    }
    printf("\nTest of image_coordone : successfully\n");
}


MU_TEST_SUITE(test_suite) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_image_moment);
}


int main(int argc, char *argv[]) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    printf("All test passed succesfuly\n");
    return MU_EXIT_CODE;
}