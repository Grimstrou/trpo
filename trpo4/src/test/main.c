#define CTEST_MAIN

#include <stdio.h>
#include <string.h>
#include <ctest.h>
#include <regex.h>

int checkCircleWKT(char *wkt, int pokaz);

void perebor(FILE* file);

CTEST(none, checkfile)
{
    FILE *file;
    char filename[] = "obj/wkt";

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
    }
    ASSERT_NOT_NULL(file);

    fclose(file);
}

CTEST(none, checkresults)
{
    FILE *file;
    char filename[] = "obj/wkt";
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
    }
    ASSERT_NOT_NULL(file);

    perebor(file);

    fclose(file);
}

int main(int argc, const char *argv[])
{
    int result = ctest_main(argc, argv);
    return result;
}
// #define CTEST_MAIN

// #include <stdio.h>
// #include <string.h>
// #include <ctest.h>
// #include <regex.h>

// int checkCircleWKT(char *wkt, int pokaz);
// void perebor(FILE* file);
// float perimetr(float radius);
// float square(float radius);

// CTEST(circle, valid_wkt)
// {
//     char wkt[] = "circle(10 10,5)";
//     int result = checkCircleWKT(wkt, 1);
//     ASSERT_EQUAL(1, result);
// }

// CTEST(circle, invalid_wkt)
// {
//     char wkt[] = "INVALID (10 10, 5)";
//     int result = checkCircleWKT(wkt, 1);
//     ASSERT_EQUAL(0, result);
// }

// CTEST(circle, null_wkt)
// {
//     int result = checkCircleWKT(NULL, 1);
//     ASSERT_EQUAL(-1, result);
// }

// CTEST(circle, empty_wkt)
// {
//     char wkt[] = "";
//     int result = checkCircleWKT(wkt, 1);
//     ASSERT_EQUAL(0, result);
// }

// CTEST(circle, missing_circle)
// {
//     char wkt[] = "POINT (10 10)";
//     int result = checkCircleWKT(wkt, 1);
//     ASSERT_EQUAL(0, result);
// }

// CTEST(circle, invalid_format_wkt)
// {
//     char wkt[] = "circle (10 10,)";
//     int result = checkCircleWKT(wkt, 1);
//     ASSERT_EQUAL(0, result);
// }

// CTEST(file, checkfile)
// {
//     FILE *file;
//     char filename[] = "obj/wkt";

//     file = fopen(filename, "r");
//     if (file == NULL) {
//         perror("Error opening file");
//     }
//     ASSERT_NOT_NULL(file);

//     fclose(file);
// }

// CTEST(file, checkresults)
// {
//     FILE *file;
//     char filename[] = "obj/wkt";
//     file = fopen(filename, "r");
//     if (file == NULL) {
//         perror("Error opening file");
//     }
//     ASSERT_NOT_NULL(file);

//     perebor(file);

//     fclose(file);
// }

// CTEST(file, empty_file)
// {
//     FILE *file;
//     char filename[] = "obj/empty_wkt";
//     file = fopen(filename, "r");
//     if (file == NULL) {
//         perror("Error opening file");
//     }
//     ASSERT_NOT_NULL(file);

//     // Проверка обработки пустого файла
//     perebor(file);

//     fclose(file);
// }

// CTEST(file, invalid_file)
// {
//     FILE *file;
//     char filename[] = "obj/invalid_wkt";
//     file = fopen(filename, "r");
//     if (file == NULL) {
//         perror("Error opening file");
//     }
//     ASSERT_NOT_NULL(file);

//     // Проверка обработки файла с некорректными данными
//     perebor(file);

//     fclose(file);
// }

// CTEST(math, perimetr_test)
// {
//     float radius = 5.0;
//     float expected = 2 * 3.14 * radius;
//     float result = perimetr(radius);
//     ASSERT_DBL_NEAR_TOL(expected, result, 0.01);
// }

// CTEST(math, square_test)
// {
//     float radius = 5.0;
//     float expected = 3.14 * radius * radius;
//     float result = square(radius);
//     ASSERT_DBL_NEAR_TOL(expected, result, 0.01);
// }

// int main(int argc, const char *argv[])
// {
//     int result = ctest_main(argc, argv);
//     return result;
// }
