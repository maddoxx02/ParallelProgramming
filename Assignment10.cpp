#include <iostream>
#include "mpi.h"
using namespace std;

int main(int argc, char **argv)
{
	int rank, size, prev, next;
	int buf[2];
	MPI_Init(&argc, &argv);
	MPI_Request reqs[4];
	MPI_Status stats[4];
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	prev = rank - 1;
	next = rank + 1;
	if (rank == 0) prev = size - 1;
	if (rank == size - 1) next = 0;
	MPI_Irecv(&buf[0], 1, MPI_INT, prev, 5, MPI_COMM_WORLD, &reqs[0]);
	MPI_Irecv(&buf[1], 1, MPI_INT, next, 6, MPI_COMM_WORLD, &reqs[1]);
	MPI_Isend(&rank, 1, MPI_INT, prev, 6, MPI_COMM_WORLD, &reqs[2]);
	MPI_Isend(&rank, 1, MPI_INT, next, 5, MPI_COMM_WORLD, &reqs[3]);
	MPI_Waitall(4, reqs, stats);

	//cout << "Is this Real life..??" << endl;
	//cout << "Current Process Number: " << rank<< " Recived stuff:" << prev << "  Sent Stuff" << next;

	cout << "Current Process Number: " << rank<< " Recived stuff: " << buf[0] << "  Sent Stuff " << buf[1];
	
	//Your code here.
	//Here you need to display the number of the current process, and what it receives from the previous and next processes.

	MPI_Finalize();
}