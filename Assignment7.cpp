#include <mpi.h>
#include <iostream>
#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

using namespace std;

const int n = 1000000;
int sum = 0;

int prod(int size, int *v1cc, int *v2cc)
{
	for (int i = 0; i < size; i++)
		sum += v1cc[i] * v2cc[i];
	
	return sum;
}

int main(int argc, char *argv[])
{
	int* v1 = new int[n];
	int* v2 = new int[n];

	int rank;
	int m;
	int out;
	int finalsum;
	

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &m);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0)//intialize
		for (int i = 0; i < n; i++)
		{
			v1[i] = 1;
			v2[i] = 1;
		}

	int half = n / m; 

	int* v1ptr = new int[half];
	int* v2ptr = new int[half];

	//distribution with others
	MPI_Scatter(v1, half, MPI_INT, v1ptr, half, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(v2, half, MPI_INT, v2ptr, half, MPI_INT, 0, MPI_COMM_WORLD);

	finalsum = prod(half, v1ptr, v2ptr);

	MPI_Reduce(&finalsum, &out, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		cout << "The Dot Product of the Vectors = " << out << endl;
	}

	MPI_Finalize();
	
	return 1;


}