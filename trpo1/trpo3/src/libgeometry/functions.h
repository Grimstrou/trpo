#pragma once

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct circle {

  double x;
  double y;
  double r;
};

void error(const char *errorMessage, const char *line, int at);

int Stringnumber(const char *str);

void СorrectValues(const char *line);

void CorrectInput(const char *line, int length);

int CorrectBrackets(const char *line);

void Treatment(const char *line);

void ReadingData(const char *filename, struct circle **circles, int *count);

void PrintData(struct circle *circles, int *count);

void calculateCircle(double radius);
