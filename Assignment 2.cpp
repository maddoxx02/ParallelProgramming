#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<cstdlib>
#include<omp.h>
#include<time.h>    


using namespace std;

// The function of allocating memory for a two-dimensional array
	double** malloc_array(long int n)
	{
		double** matrix = new double*[n];
		for (int i = 0; i < n; i++)
			matrix[i] = new double[n];
		return matrix;
	}

// Memory free function Deleting
void free_array(double** matrix,long int n)
{
	for (int i = 0; i < n; i++)
		delete[] matrix[i];
	delete[] matrix;
}

// The function of initializing a matrix with random numbers from [0,1]
void rand_init_matrix(double** matrix,long int n)
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = rand()/10000;
}

// Matrix zeroing function
void zero_init_matrix(double** matrix, long int n)
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = 0.0 ;
}

int main()
{
	const long int N = 800;//Size of matrix
	double** A, **B, **C;

// Memory allocation for matrices A, B, C
	A = malloc_array(N);
	B = malloc_array(N);
	C = malloc_array(N);

// Initialization of matrices
	rand_init_matrix(A, N);
	rand_init_matrix(B, N);
	zero_init_matrix(C, N);
	
	double t;
	int i,j,k;


	cout<<endl;
	// Matrix multiplication with cycle order ijk
	double tempijk;	
	for(int q=1;q<=10;q++)
	{
	t = omp_get_wtime();
	#pragma omp parallel for num_threads(q) shared(A, B, C) private(i, j, k)
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
				C[i][j] += A[i][k] * B[k][j];
	t = omp_get_wtime() - t;
	if(q==1)
	{
		tempijk = t;
	}
	cout << "Time utilized by ijk loop using "<<q<<" Thread/s is " << t<<endl;
	cout<< " seconds " << "Efficiency :"<< tempijk/t<<endl<<endl; 
	}	
	
	cout<<endl;
	// Matrix multiplication with cycle order jki
	double tempjki;
	for(int q=1;q<=10;q++)
	{
	zero_init_matrix(C, N);
	t = omp_get_wtime();
	#pragma omp parallel for num_threads(q) shared(A, B, C) private(i, j, k)
	for (int j = 0; j < N; j++)
		for (int k = 0; k < N; k++)
			for (int i = 0; i < N; i++)
				C[i][j] += A[i][k] * B[k][j];
	t = omp_get_wtime() - t;
	if(q==1)
	{
		tempjki = t;
	}
	cout << "Time utilized by jki loop using "<<q<<" Thread/s is " << t<<endl;
	cout << " seconds" << " Efficiency :"<< tempjki/t<<  endl<<endl;
	}
	
	cout<<endl;
	double tempikj;
	for(int q=1;q<=10;q++)
	{
	// Matrix multiplication with cycle order ikj
	zero_init_matrix(C, N);
	t = omp_get_wtime();
	#pragma omp parallel for num_threads(q) shared(A, B, C) private(i, j, k)
	for (int i = 0; i < N; i++)
		for (int k = 0; k < N; k++)
			for (int j = 0; j < N; j++)
				C[i][j] += A[i][k] * B[k][j];
	t = omp_get_wtime() - t;
	if(q==1)
	{
		tempikj = t;
	}
	cout << "Time utilized by ikj loop using "<<q<<" Thread/s is " << t<<endl;
	cout << " seconds" << " Efficiency :"<< tempikj/t<<  endl<<endl;
	}
				
	
	cout<<endl;
	/*
	cout<<"printing Matrix A:"<<endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout<<A[i][j]<<" ";
		}
		cout<<endl;
	}
	
	cout<<endl;
	cout<<"printing Matrix B:"<<endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout<<B[i][j]<<" ";
		}
		cout<<endl;
	}
	
	cout<<endl;
	cout<<"printing Matrix C:"<<endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout<<C[i][j]<<" ";
		}
		cout<<endl;
	}
	*/

// Freeing memory occupied by matrices A, B, C
	free_array(A, N);
	free_array(B, N);
	free_array(C, N);
	

	return 0;
}

