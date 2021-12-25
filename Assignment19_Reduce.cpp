#include <stdio.h>
#include "mpi.h"
#include<iostream>
#include<cstdlib>
#include<math.h>
#include<algorithm>

using namespace std;


int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Status status;


	int* a, *b;
	int parts;
	//double sum = 0, part_sum = 0;
	long sum = 0;
	long ssum = 0;
	double start, finish;


	parts = 1000000 / size;


	a = new int[1000000];
	b = new int[parts];

	//initialization
	if (rank == 0)
	{
		for (int i = 0; i < 1000000; i++)
		{
			a[i] = 1;
		}
	}



	MPI_Bcast(&parts, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(a, parts, MPI_INT, b, parts, MPI_INT, 0, MPI_COMM_WORLD);

	for (int i = 0; i < parts; i++)
	{
		ssum += b[i];
	}

	if (rank == 0)
	{
		start = MPI_Wtime();
	}

	MPI_Reduce(&ssum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	finish = MPI_Wtime() - start;

	if (rank == 0)
	{
		cout << "Reduce Function Method" << endl;
		cout << "Sum = " << sum << " Execution time: " << finish << endl;
	}


	MPI_Finalize();
	return 0;
}