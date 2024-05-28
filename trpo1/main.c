#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_TYPE_LENGTH 128

typedef enum { CIRCLE, UNKNOWN } ShapeType;

typedef struct {
    double xPos;
    double yPos;
} Position;

typedef struct {
    Position centerPos;
    double radiusVal;
    double perimeterVal;
    double areaVal;
} Shape;

ShapeType parseShapeType(const char* typeStr);
int validateGeometryData(char* inputLine, int lineNum);
int validateBrackets(const char* inputLine, int lineNum);
int isNumeric(char** tokenPtr);
void extractShapeType(const char* src, char* dest, char** endPtr);
void markError(long index);

int main()
{
    const char* filePath = "geometry.wkt";
    char lineData[MAX_LINE_LENGTH];
    int lineCount = 0;
    Shape* shapeArr = NULL;

    FILE* file = fopen(filePath, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", filePath);
        return 1;
    }

    while (fgets(lineData, MAX_LINE_LENGTH, file)) {
        printf("%s", lineData);
        lineCount++;
        if (!validateGeometryData(lineData, lineCount)) {
            continue;
        }
    }
    fclose(file);
    free(shapeArr);
    return 0;
}

ShapeType parseShapeType(const char* typeStr)
{
    if (strcmp(typeStr, "circle") == 0)
        return CIRCLE;
    return UNKNOWN;
}

int validateGeometryData(char* inputLine, int lineNum)
{
    char* charPtr = inputLine;
    char typeStr[MAX_TYPE_LENGTH];
    extractShapeType(inputLine, typeStr, &charPtr);
    ShapeType shapeType = parseShapeType(typeStr);
    if (shapeType == UNKNOWN) {
        markError(0);
        fprintf(stderr,
                "Error at line %d: Unknown shape type. Expected 'circle', "
                "'triangle', or 'polygon'.\n",
                lineNum);
        return 0;
    }
    if (!validateBrackets(inputLine, lineNum))
        return 0;
    charPtr++;
    while (*charPtr != ')') {
        if (*charPtr == ',' || *charPtr == '(' || *charPtr == ' ') {
            charPtr++;
            continue;
        }
        if (!isNumeric(&charPtr)) {
            markError(charPtr - inputLine);
            fprintf(stderr, "Error at line %d: Expected a number.\n", lineNum);
            return 0;
        }
    }
    while (*charPtr != '\n' && *charPtr != '\0') {
        if (*charPtr != ')') {
            markError(charPtr - inputLine);
            fprintf(stderr, "Error at line %d: Unexpected token.\n", lineNum);
            return 0;
        }
        charPtr++;
    }
    return 1;
}

int validateBrackets(const char* inputLine, int lineNum)
{
    int bracketCount = 0, i;
    for (i = 0; i < strlen(inputLine); i++) {
        if (inputLine[i] == '(')
            bracketCount++;
        else if (inputLine[i] == ')') {
            bracketCount--;
            if (bracketCount < 0) {
                markError(i);
                fprintf(stderr,
                        "Error at line %d: Unexpected closing bracket.\n",
                        lineNum);
                return 0;
            }
        }
    }
    if (bracketCount != 0) {
        markError(i - 1);
        fprintf(stderr,
                "Error at line %d: Expected closing bracket.\n",
                lineNum);
        return 0;
    }
    return 1;
}

int isNumeric(char** tokenPtr)
{
    char* startPtr = *tokenPtr;
    strtod(*tokenPtr, tokenPtr);
    return startPtr != *tokenPtr;
}

void extractShapeType(const char* src, char* dest, char** endPtr)
{
    int i = 0;
    while (((src[i] <= 'Z' && src[i] >= 'A')
            || (src[i] <= 'z' && src[i] >= 'a'))
           && i < MAX_TYPE_LENGTH) {
        dest[i] = (char)tolower(src[i]);
        i++;
        if (endPtr != NULL)
            (*endPtr)++;
    }
    dest[i] = '\0';
}

void markError(long index)
{
    for (int i = 0; i < index; i++)
        printf(" ");
    printf("^\n");
}
