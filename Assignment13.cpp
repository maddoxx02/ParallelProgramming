#include <cstdlib>
#include "mpi.h"
#include<iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;



int main(int argc, char **argv)
{
	int rank, size;
	double start, finish;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int **x = new int*[500];
	int **y = new int*[500];
	int **z = new int*[500];

	
	for (int i = 0; i < 500; i++)
	{
		x[i] = new int[500];
		y[i] = new int[500];
		z[i] = new int[500];
	}

	//Matrix Initalization

	for(int j = 0;j<500;j++)//r
	{
		for (int k = 0; k < 500; k++) //c
		{
			x[j][k] = rand() % 10;
			y[j][k] = rand() % 10;
			z[j][k] = 0;
		}
	}

	MPI_Barrier(MPI_COMM_WORLD);  //Barrier Synchronization

	
	start = MPI_Wtime(); //Start Time

	
	for (int i = 0; i < 500; i++) 
	{
		for (int j = 0; j < 500; j++) 
		{
			for (int k = 0; k < 500; k++) 
			{
				z[i][j] += x[i][k] * y[k][j]; //Matrix Multiplication
			}
		}
	}
		
	finish = MPI_Wtime() - start; //End Timing 

	//Output of execution time of matrix multiplication at each process
	cout << "Process:  " << rank << " Measured Time: " << finish << endl;

	MPI_Finalize();

	return 1;
}