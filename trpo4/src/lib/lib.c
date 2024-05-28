#include "lib.h"

float perimetr(float radius)
{
    return 2 * 3.14 * radius;
}

float square(float radius)
{
    return 3.14 * radius * radius;
}

void perebor(FILE* file)
{
     char line[100];
    do
    {
        line[strcspn(line, "\n")] = 0; 

        if (checkCircleWKT(line, 1))
        {
            printf("%s\n", line);
            char line[100];
            for (int i = 0; i < 3; i++) {
                fgets(line, 100, file);
            }

            char *token = strtok(line, "(),");

            for (int i = 0; i < 2; i++) {
                token = strtok(NULL, "(),");
            }

            float radius;
            sscanf( token, "%f", &radius ); 
            radius *= -1;

            printf("\tОкружность с радиусом %.2f\n", radius);
            printf("\tПериметр: %.2f\n", perimetr(radius));
            printf("\tПлощадь: %.2f\n", square(radius));
        }  
        else
        {
            printf("\n");
        }
    } while (fgets(line, sizeof(line), file));
}

int checkCircleWKT(char *wkt, int pokaz) 
{
    char *pattern = "circle\\(\\([^,]+,[^,]+\\),[^)]+\\)";
    regex_t regex;

    int reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti)
    {
        fprintf(stderr, "Could not compile regexn");
        return 3;
    }

    reti = regexec(&regex, wkt, 0, NULL, 0);

    if (!reti)
    {
        regfree(&regex);
        return 1;
    }
    else 
    {
        if(pokaz == 1)
        {
            regfree(&regex);
            fprintf(stderr, "Error in WKT format:");

            if (strstr(wkt, "circle" ) != wkt)
                printf("\n expected 'circle' at the beginning of the string ");
            else
            {
                char *pos = wkt;
                while (*pos != '(')
                    ++pos;
                if (*pos == '(')
                {
                    while (*pos != ' ' && *pos != ')' && *pos != '0')
                        ++pos;
                    if (*pos == ' ' || *pos == ')')
                        fprintf(stderr, " expected '<double>' after the coordinates ");
                    else if (*pos == '0' || *pos == ')')
                        fprintf(stderr, "\n expected ')'n ");
                    else
                        fprintf(stderr, " unexpected tokenn ");
                }
            }
        }

        return 0;
    }
}
