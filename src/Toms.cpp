#include <pthread.h>
#include <iostream>
#include <fstream>
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

using namespace std;

int found[26];

struct threadData
{
	char * data;
	int length;
	char first_letter;
	char last_letter;
	int threadNum;
};

int inc(char *c)
{
	
    if(c[0]==0) return 0;
    if(c[0]=='z')
    {
        c[0]='a';
        return inc(c+sizeof(char));
    }   
    c[0]++;
    return 1;

}


void* method (void *args)
{
	struct threadData *methodData = (struct threadData*) args;
	char *input_string = methodData -> data;
	int i,j, k,n = methodData -> length;
	char first = methodData -> first_letter;
	char last = methodData -> last_letter;
	int threadNum = methodData -> threadNum;
	
	char *c = new char[((n+1)*sizeof(char))];

	
	
	
	
	for(int i = 1; i <= n; i++)
	{
		
		char * end = new char[((i+1)*sizeof(char))];
		for( k = 0; k<(i-1); k++)
		{
			end[k] = 'z';
		}
		end[k] = last;
		
		
		
		c[i-1] = first;
		for( j=0; j< i-1; j++)
		{
			c[j]='a';
		}
		c[i]=0;
	
		do
		{
			if(strcmp(input_string, c) == 0)
			{
				printf("You entered: %s\n", c);
			
				found[threadNum] = 1;
			
				return methodData;
			}
		
			if(strcmp(c, end) == 0)
			{
				break;
			}
	
	
		}
		while(inc(c));
	
	}
	
	

}

int main( int argc, char ** argv)
{

	if(argc != 3)
	{
		printf("Incorrect number of arguments.  Argument list is <execname> <input_string> 			<number_of_threads>\n");
		return 0;
	}
	
	
	
	int len = strlen(argv[1]);
	char input_string[len];
	
	int threads = atoi(argv[2]);	
	int alphabet = 26;
	int baselettersperthread = alphabet/threads;
	int extraletters =  alphabet % threads;
	
	for(int i = 0; i < threads; i++)
	{
		found[i] = 0;
	}
	
	if(len > 9)
	{
		printf("I'm assuming you made a mistake.\n");
		printf("String is pretty long, better change programs to look for that one.\n\n");
		return 0;
	}
	
	int threadWork[threads];
	for(int i = 0; i < threads; i++)
	{
	threadWork[i] = baselettersperthread;
	}
	for(int i = 0; i < threads; i++)
	{
		//printf("extraletters = %d\n", extraletters);
		if(extraletters > 0)
		{
			//printf("inside if\n");
			threadWork[threads-(i+1)] = threadWork[threads-(i+1)] + 1;
			extraletters = extraletters - 1;
		
		}
		else
		{
			//printf("I = %d\n", i);
			break;
		}
	}
	
	threadData threadDataArray[threads];
	
	strcpy(input_string,argv[1]);
	

	printf("\nThe string you entered was: %s\n", input_string);
	
	char input = 'a';
	char first_letter;
	char last_letter;
	for(int i = 0; i < threads; i++)
	{
		
		first_letter = input;
		for(int j = 0; j < threadWork[i]; j++)
		{
			
			input++;
		}
		last_letter = --input;
		input++;
			
		
		threadDataArray[i] = {input_string, len, first_letter, last_letter, i};
		printf("Thread :%d, Input_string: %s, First: %c, Last: %c\n", i, input_string, first_letter, last_letter);
	}
	
	pthread_t threadList[threads];
	
	for(int i = 0; i < threads; i++)
	{
		pthread_create(&threadList[i], NULL, method, &threadDataArray[i]);
	}
	
	
	
	int exit = 1;
	do
	{
		for(int i = 0; i < threads; i++)
		{
			if(found[i] == 1)
			{
				exit = 0;
			}
		}
	
	
	}
	while(exit);
	
	
	printf("Im out\n");
	
	for(int i = 0; i < threads; i++)
	{
		printf("found%d: %d\n", i, found[i]);
	}
	
	
}













