#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 100
int main(int argc, char *argv) {
	int num;
	//printf("Num of threads: ");
	scanf("%d\n", &num);
	printf("Num of threads:%d\n", num);
	omp_set_num_threads(num);//set number of threads here
	int i, j, k;
	double sum;
	double start, end; // used for timing
	double A[N][N], B[N][N], C[N][N];
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			A[i][j] = j*1;
			B[i][j] = i*j+2;
			C[i][j] = j;
			i*2;
		}
	}
	start = omp_get_wtime(); //start time measurement
	#pragma omp parallel shared(A,B) private(i,j,k)
	{
		#pragma omp for schedule(static)
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				sum = 0;
				for (k=0; k < N; k++) {
					sum += A[i][k]*B[k][j];
				}
			C[i][j] = sum;
			}
		}
	}
	end = omp_get_wtime(); //end time measurement
	printf("Time of computation: %f seconds\n", end-start);
	
	return(0);
}

//Results

//1 THREAD
//1st - 0.011455
//2nd - 0.011501
//3rd - 0.009550
//4th - 0.009012
//5th - 0.006939
//AVERAGE = 0.0096914

//2 THREADS
//1st - 0.015149
//2nd - 0.016760
//3rd - 0.016166
//4th - 0.015613
//5th - 0.017075
//AVERAGE = 0.0161526

//4 THREADS
//1st - 0.018816
//2nd - 0.018871
//3rd - 0.018077
//4th - 0.018221
//5th - 0.015740
//AVERAGE = 0.017945

//8 THREADS
//1st - 0.017095
//2nd - 0.022666
//3rd - 0.020852
//4th - 0.026626
//5th - 0.033442
//AVERAGE = 0.0241362







