#include <stdio.h>
#include "mpi.h"
#include<iostream>
#include<cstdlib>
#include<math.h>
#include<algorithm>

using namespace std;

int main(int argc, char **argv)
{
	
	int rank, size, rank1;
	MPI_Init(&argc, &argv);
	MPI_Comm comm_revs;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0)
	{
		cout << "When Color = Rank%2" << endl;
		//cout << "When Color = Rank%3" << endl;
	}
	
	MPI_Comm_split(MPI_COMM_WORLD, rank % 2, size - rank, &comm_revs);
	MPI_Comm_rank(comm_revs, &rank1);
	cout << "Rank: " << rank << " Rank_1: " << rank1;
	MPI_Comm_free(&comm_revs);

		/* //When Color is Rank%3
	MPI_Comm_split(MPI_COMM_WORLD, rank % 3, size - rank, &comm_revs);
	MPI_Comm_rank(comm_revs, &rank1);
	cout << "Rank: " << rank << " Rank_1: " << rank1;
	MPI_Comm_free(&comm_revs);
	*/

	MPI_Finalize();
	
}