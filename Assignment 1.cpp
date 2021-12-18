#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<cstdlib>
#include<omp.h>
#include<time.h>    

using namespace std; 

int main()
{
	//---------------------------------------------------------------------------------------------------------------------------
	srand(time(0)); // Random Seed	
	
	int n; // Array Size 
	
	//Array Size INPUT
	cout<<"Enter size of Array: ";
	cin>>n;	
	
	static double a[100000000]; //Array Storing Variables
	
	//---------------------------------------------------------------------------------------------------------------------------
	if(n<=20) //Small Array Small elements
	{
		for(int i = 0; i<n;i++)
		a[i] = rand()/100;
	}
	else
	for(int i=0;i<n;i++)//Loop to assign random variables to the Array
	{
	 a[i] = rand()*rand()/1000;
	}
	
	//---------------------------------------------------------------------------------------------------------------------------
	
	int threads = 0;
	double maxval = 0;
	int temp = a[0];
	
	for(int q=1;q<=10;q++)
	{
		maxval=a[0];
		double time = omp_get_wtime();
		threads++;				
	//Parallel Section
	omp_set_num_threads(q);// Number of threads Constraint
	#pragma omp parallel for num_threads(q) reduction(max:maxval)
	for(int j = 1;j < n;j++)
		{
			maxval = max(maxval, a[j]); //Comparison 
		}
	
		
	cout<< "Time = " << (omp_get_wtime() - time) << endl; //Printing Time Consumed 
	cout<<"Maximum Value = "<<maxval<<endl; //Printing Max Value Found in Array
	cout<<"Number of threads Used = "<<threads<<endl; //Printing Number of Threads Utilized 
	cout<<"\n\n";
	
	}
	//Printing Small Array Elements
	if(n<=20)
	{
		cout<<"Array Elements are as follows:";
		for(int i = 0;i<n;i++)
		{
			cout<<a[i]<<endl;
		}
		
	}
	//---------------------------------------------------------------------------------------------------------------------------
	return 1;
} 