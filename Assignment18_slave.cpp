
#include <stdio.h>
#include "mpi.h"
#include<iostream>
#include<cstdlib>
#include<math.h>
#include<algorithm>

using namespace std;

int main(int argc, char **argv)
{
	int rank,temp;
	MPI_Comm intercomm;
	MPI_Init(&argc, &argv);
	MPI_Comm_get_parent(&intercomm);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	//MPI_Send(&rank, 1, MPI_INT, 0, rank, intercomm);

	if (rank > 2)
	{
		MPI_Send(&rank, 1, MPI_INT, 0, rank, intercomm);
	}
	else
	{
		MPI_Comm_rank(MPI_COMM_WORLD, &temp);
		MPI_Send(&temp, 1, MPI_INT, 0, rank, intercomm);
	}

	MPI_Finalize();
	return 0;
}