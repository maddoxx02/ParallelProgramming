
#include <stdio.h>
#include "mpi.h"
#include<iostream>
#include<cstdlib>
#include<math.h>
#include<algorithm>
#include <string.h>

using namespace std;

#define BUFSIZE 100

void fcreator(const char *NAME, const char *LINE, int SIZE) //File Creation function
{
	MPI_File fh;
	MPI_Status status;
	MPI_File_open(MPI_COMM_WORLD, NAME, MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);
	MPI_File_write(fh, LINE, SIZE, MPI_CHAR, &status);
	MPI_File_close(&fh);

}


int main(int argc, char **argv)
{
	
	int bufsize, num, sum;
	MPI_Init(&argc, &argv);

	fcreator("file.txt", "This is a sentence in the File.!", 32);

	MPI_Status status;
	MPI_File fh;
	char buf[BUFSIZE];
	MPI_File_open(MPI_COMM_WORLD, "file.txt", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
	MPI_File_set_view(fh, 0, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);
	sum = 0;
	do {
		MPI_File_read(fh, buf, BUFSIZE, MPI_CHAR, &status);
		MPI_Get_count(&status, MPI_CHAR, &num);
		printf("buf=%s\n", buf);
		sum += num;
	} while (num >= BUFSIZE);
	MPI_File_close(&fh);
	//print the number of read symbols sum from the file
	printf("\nNumber of Symbols sum from the File: %d", sum);

	MPI_File_delete("file.txt", MPI_INFO_NULL);
	cout << endl<< "FILE HAS BEEN DELETED...!!";
	MPI_Finalize();
}