#include <libgeometry/functions.h>

void error(const char *errorMessage, const char *line, int at) {
  printf("\n%s\n", line);
  for (int i = 0; i < at; i++) {
    printf(" ");
  }
  printf("^\n%s\n\n", errorMessage);
  exit(1);
}

int Stringnumber(const char *str) {
  char *endptr;
  strtod(str, &endptr);
  return (errno == 0 && *endptr == '\0');
}

void СorrectValues(const char *line) {
  const char *delimiters = " \t(),";
  char *input = strdup(line);
  char *current = strtok(input, delimiters);

  if (strcmp(current, "circle") != 0) {
    free(input);
  }

  current = strtok(NULL, delimiters);
  if (!Stringnumber(current)) {
    char *ptr = strstr(line, current);
    free(input);
    error("Invalid <X> entered", line, ptr - line);
  }

  current = strtok(NULL, delimiters);
  if (!Stringnumber(current)) {
    char *ptr = strstr(line, current);
    free(input);
    error("Invalid <Y> entered", line, ptr - line);
  }

  current = strtok(NULL, delimiters);

  if (!Stringnumber(current)) {

    char *ptr = strstr(line, current);
    free(input);
    error("Invalid <Z> entered", line, ptr - line);
  }

  free(input);
}

void CorrectInput(const char *line, int length) {
  const char *expectedName = "circle";
  char lineName[7];
  strncpy(lineName, line, length);
  if (strcmp(expectedName, lineName) != 0) {
    error("Error when reading circle", line, 0);
  }
}

int CorrectBrackets(const char *line) {
  int open = 0, close = 0, firstOpenIndex = 0, len = strlen(line);
  for (int i = 0; i < len; i++) {
    if (line[i] == '(') {
      if (open == 0)
        firstOpenIndex = i;
      open++;

      if (open == 2)
        error("Error in parentheses < ( > ", line, i);
    }

    if (line[i] == ')') {
      close++;
      if (line[i + 1] != '\n' && line[i + 1] != '\0')
        error("Character input error", line, i + 1);
    }
  }

  if (open == 0)
    error("Error when entering results < ( >", line, 6);
  if (close == 0)
    error("Error when entering results < ) >", line, len);
  return firstOpenIndex;
}


void Treatment(const char *line) {
  int figureNameLength = CorrectBrackets(line);
  CorrectInput(line, figureNameLength);
  СorrectValues(line);
}


void ReadingData(const char *filename, struct circle **circles, int *count) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error reading file");
    return;
  }

  *circles = (struct circle *)malloc(100 * sizeof(struct circle));

  int capacity = 100;
  *count = 0;

  char line[100];

  while (fgets(line, sizeof(line), file)) {
    Treatment(line);
    double x, y, r;
    if (sscanf(line, "circle(%lf %lf, %lf)", &x, &y, &r) == 3) {
      if (*count == capacity) {
        capacity *= 2;
        *circles = (struct circle *)realloc(*circles,
                                            capacity * sizeof(struct circle));

      }

      else {
        printf("\n");
        perror("One line error reading");
      }

      (*circles)[*count].x = x;
      (*circles)[*count].y = y;
      (*circles)[*count].r = r;

      (*count)++;
    }
  }

  fclose(file);
}

void PrintData(struct circle *circles, int *count) {
  printf("\n");
  for (int i = 0; i < *count; i++) {
    printf(" %d.    circle(%g %g, %g)\n\n",
           i + 1, circles[i].x, circles[i].y, circles[i].r);
  }
}

void calculateCircle(double radius) {
  double area = M_PI * pow(radius, 2);
  double perimeter = 2 * M_PI * radius;

  printf("Площадь  %0.4f\n", area);
  printf("\nПериметр %0.4f\n", perimeter);
}
