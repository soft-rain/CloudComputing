#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void rot(int N, double* a) {
  double tmp = a[0];
  #pragma omp parallel
  {
    int x = 0;
    #pragma omp for schedule(static) nowait
    for (int i = 0; i < N - 1; i++) {
      x = i;
    }
    double y = a[x+1];
    #pragma omp barrier
    #pragma omp for schedule(static) nowait
    for (int i = 0; i < N - 1; i++) {
      a[i] = a[i+1];
    }
    a[x] = y;
  }
  a[N - 1] = tmp;
}
