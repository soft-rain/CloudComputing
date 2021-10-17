//
// 2021 Fall - Cloud Computing (01)
// Homework #1: Parallelize matrix-vector multiplication,
// 		and max operation using OpenMPI
//
// Copyright (c) Prof. Jaehyeong Sim
// Department of Computer Science and Engineering, Ewha Womans University
//

#include "mpi.h"
#include <stdio.h>

#define N 16
//#define N 1024

double mat[N][N];
double vec[N];

int main(int argc, char *argv[])
{
	int rank, size;
	double t1, t2;
	char filename[16];

	// Read matrix and vector data from file
	sprintf(filename, "%d.txt", N);
	FILE *fp = fopen(filename, "r");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fscanf(fp, "%lf", &mat[i][j]);
		}
	}
	for (int i = 0; i < N; i++)
	{
		fscanf(fp, "%lf", &vec[i]);
	}
	fclose(fp);

	// MPI start
	MPI_Init(&argc, &argv);
	t1 = MPI_Wtime();

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Scatter(mat, N*N/size, MPI_DOUBLE,mat, N*N/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(vec, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	double temp[N/size];
	double result[N];
	for(int i=0; i<N/size; i++){
		result[N]=0;
	}
	for(int i=0; i<N/size; i++)
		for(int j=0; j<N; j++)
			temp[i] += vec[j]*mat[i][j];
	MPI_Gather(temp, N/size, MPI_DOUBLE, result, N/size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	
	double max = -1;
	if(rank==0){
		for(int i=0; i<N; i++){
			if(max < temp[i])
				max = temp[i];
		}
		//for(int i=0; i<N; i++){
		//	printf("%3lf ", temp[i]);
		//}
		//printf("\n");
		printf("Max : %lf\n", max);
	}
	t2 = MPI_Wtime();
	if (rank == 0)
		printf("Elapsed time for rank 0 is %f\n", t2 - t1);
	if (rank == 1)
		printf("Elapsed time for rank 1 is %f\n", t2 - t1);

	MPI_Finalize();

	return 0;
}
