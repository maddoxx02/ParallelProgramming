#include <stdio.h>
#include "mpi.h"
#include<iostream>
#include<cstdlib>
#include<math.h>
#include<algorithm>

using namespace std;

int main(int argc, char **argv)
{
	int size, rank1, rank2, rpros;
	MPI_Status status;
	MPI_Comm intercomm;
	char slave[80] = " C:\\Users\\Shiv\\source\\repos\\ConsoleApplication3\\Debug\\ConsoleApplication3.exe.";
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_spawn(slave, MPI_ARGV_NULL, 3, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm, MPI_ERRCODES_IGNORE);
	MPI_Recv(&rank1, 1, MPI_INT, 0, 0, intercomm, &status);
	MPI_Recv(&rank2, 1, MPI_INT, 1, 1, intercomm, &status);

	cout << "Slaves " << rank1 << " & " << rank2 << " are working...!!!"<<endl;

	//Display "Slaves rank1 and rank2 are working", instead of the words rank1 and rank2 their values should be displayed.

	//third function
	
	MPI_Recv(&rpros, 1, MPI_INT, 2, 2, intercomm, &status); 
	cout << "Number of Process Running " << rpros << "Called from the Slave: " << status.MPI_SOURCE;
	MPI_Finalize();
	return 0;
}