#include <pthread.h>
#include <iostream>
#include <fstream>
using namespace std;
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>
#include <iomanip>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>


int alphabet = 26;

int main (int argc, char ** argv)
{

	if(argc != 2)
	{
		printf("Bitch Please\n");
		return 0;
	}
	
	int threads = atoi(argv[1]);
	
	int baselettersperthread = alphabet/threads;
	
	int extraletters =  alphabet % threads;
	
	printf("baselettersperthread = %d\n", baselettersperthread);
	
	printf("threads = %d\n", threads);
	
	printf("alphabet = %d\n", alphabet);

	//printf("extraletters = %d\n", extraletters);
	
	int x[threads];
	
	
	for(int i = 0; i < threads; i++)
	{
	x[i] = baselettersperthread;
	}
	
	for(int i = 0; i < threads; i++)
	{
		printf("extraletters = %d\n", extraletters);
		if(extraletters > 0)
		{
			printf("inside if\n");
			x[threads-(i+1)] = x[threads-(i+1)] + 1;
			extraletters = extraletters - 1;
			
		}
		else
		{
			printf("I = %d\n", i);
			break;
		}
		
	
	}
	
	for(int i = 0; i < threads; i++)
	{
		printf("Thread %d: %d\n", i, x[i]);
	}
	
	char input = 'a';
	
	for(int i = 0; i < threads; i++)
	{
	
		for(int j = 0; j < x[i]; j++)
		{
		
			
			input++;
			
		}
		
		
		printf("last char thread %d: %c\n", i, input);
	
	}
	
	int decimals;
	
	
	
	
	
	
/*
	switch(threads)
	{
		Case 1 : 
		Case 2 :
		Case 3 :
	}
*/
}
