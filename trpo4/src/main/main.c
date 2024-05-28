#include <stdio.h>
#include <string.h>

int checkCircleWKT(char *wkt, int pokaz);

int main() 
{
    FILE *file;
    char filename[] = "../obj/wkt";

    file = fopen(filename, "r");
    if (file == NULL) 
    {
        fprintf(stderr, "Не удалось открыть файл.\n");
        return 2;
    }


    fclose(file);

    return 0;
}