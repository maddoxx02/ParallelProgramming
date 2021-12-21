#include <stdio.h>
#include<stdlib.h>
#include<iostream>
#include <iostream>
#include <mpi.h>
#include<time.h>

using namespace std;

int signal[10000001];
int buf[10000001];

int main(int argc, char* argv[])
{
	
	double time_start, time_finish;

	double len, band, time, ping;
		
	int flag = 0;

	MPI_Init(&argc, &argv);

	int rank, size;

	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0)
	{
		for (int i = 0; i <= 10000000; i++)
			signal[i] = rand();
	}

	for (int i = 0; i <= 10000000; i *= 10)
	{
		if (flag == 1)
		{
			flag = 0;
			i++;
		}


		time_start = MPI_Wtime();

		if (i == 0) flag = 1;
		for (int j = 0; j < 10; j++)
		{
			if (rank == 0)
			{
				MPI_Send(&signal[0], i, MPI_INT, 1, 0, MPI_COMM_WORLD);
				MPI_Recv(&buf[0], i, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
			}
			else
			{
				MPI_Recv(&buf[0], i, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
				MPI_Send(&buf[0], i, MPI_INT, 0, 0, MPI_COMM_WORLD);
			}
		}
		time_finish = MPI_Wtime();
		time = time_finish - time_start;

		if (rank == 0)
		{
			len = i * sizeof(int);//Length

			band = ((2 * 10 * len) / (time))/100000.0; //bandwidth

			ping = time / (2 * 10);
			cout.precision(5);
			cout << " Data Sent: " << i << endl;

			cout << " Bandwidth: " << band <<" B/ms "<< band/125<< " Mb/s "<< band/125000<< " Gb/s"<<endl;

			cout << " Latency: " << ping << endl << endl;
		}
		
	}
	MPI_Finalize();


	return 1;
}