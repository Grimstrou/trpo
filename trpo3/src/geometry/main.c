#include <libgeometry/functions.h>

int main(int argc, char *argv[]) {

  struct circle *circles = (struct circle *)malloc(100 * sizeof(struct circle));

  int count = 0;

  if (argc > 0) {
    ReadingData(argv[1], &circles, &count);
  }

  PrintData(circles, &count);

  for (int i = 0; i < count; i++) {

    printf("%d. ", i + 1);

    calculateCircle(circles[i].r);
  }

  free(circles);

  return 0;
}
