
#include <stdio.h>
#include "mpi.h"
#include<iostream>
#include<cstdlib>
#include<math.h>
#include<algorithm>
#include <string.h>

using namespace std;

int main(int argc, char **argv)
{
	//int r;
	char message[10];
	MPI_Init(&argc, &argv);
	char port_name[MPI_MAX_PORT_NAME];
	MPI_Status status;
	MPI_Comm intercomm;
	MPI_Open_port(MPI_INFO_NULL, port_name);
	printf("Port Name: %s\n", port_name);
	printf("\nWaiting For Client.....");
	MPI_Comm_accept(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
	printf("\n Client Connected");
	MPI_Recv(&message, 10, MPI_INT, 0, 0, intercomm, &status);
	MPI_Comm_free(&intercomm);
	MPI_Close_port(port_name);
	printf("Server Sent value `%10s` \n",message);
	MPI_Finalize();
	return 0;
}
