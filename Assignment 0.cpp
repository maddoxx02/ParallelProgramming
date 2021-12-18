#include<iostream>
#include<stdlib.h>
using namespace std;

function(char *str)
{
	int flag = 0;
	int count = 0;
	
	while (*str)
	{
		if (*str == ' ' || *str == '\n' || *str == '\t')
		{
			flag = 0;
		}
		else if (flag == 0)
		{
			flag = 1;
			count++;
		}
		str++;
	}
	return count;
}

int main()
{
	char str[] = "";
	
	cout<<"Enter the Sentence:";
	cin.get(str, 100);
	
	cout<<"\n\n"<<"The Number of words present in the Sentence is : "<<function(str);
	
	return 1;
}
