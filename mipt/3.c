#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

#define ISIZE 1000
#define JSIZE 1000

int main(int argc, char **argv) {
  double a[ISIZE][JSIZE];
  int i, j;
  FILE *ff;

  int nThreads = 1;
  if (argc != 2) {
    nThreads = 1;
  } else {
    nThreads = atoi(argv[1]);
  }

  for (i = 0; i < ISIZE; ++i) {
    for (j = 0; j < JSIZE; ++j) {
      a[i][j] = 10 * i + j;
    }
  }
  double t1, t2;
  t1 = omp_get_wtime();
  #pragma omp parallel num_threads(nThreads) shared(a) private(j, i) 
  {
    for (i = 0; i < ISIZE - 1; ++i) {
      #pragma omp for
      for (j = 1; j < JSIZE; ++j) {
        a[i][j] = sin(0.00001 * a[i + 1][j - 1]);
      }
    }
  }

  t2 = omp_get_wtime();

  printf("Time elapsed: %f\n", t2-t1);
  ff = fopen("3.out", "w");
  for (i = 0; i < ISIZE; ++i) {
    for (j = 0; j < JSIZE; ++j) {
      fprintf(ff, "%f ", a[i][j]);
    }
    fprintf(ff, "\n");
  }

  fclose(ff);
  return 0;
}