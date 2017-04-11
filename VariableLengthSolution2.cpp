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


struct damonArray
{
	char * data;
	int length;

};

long long start_timer() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

long long stop_timer(long long start_time, std::string name) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	long long end_time = tv.tv_sec * 1000000 + tv.tv_usec;
        std::cout << std::setprecision(5);	
	std::cout << name << ": " << ((float) (end_time - start_time)) / (1000 * 1000) << " sec\n";
	return end_time - start_time;
}

void* first_thread( void* args)
{

	struct damonArray *damon = (struct damonArray*) args;

	char *input_string = damon -> data;
	
	int i,j,n = damon -> length;
	char *c_first_thread = new char[((n+1)*sizeof(char))];

	printf("input_string: %s\n", input_string);
	
	for( i=1;i<=n;i++)
	{
		for( j=0;j<i;j++) 
		{		
			c_first_thread[j]='0';
		}


	}


}


int main( int argc, char ** argv)
{

	if(argc != 2)
	{

		printf("Incorrect number of arguments.  Argument list is <execname> <input_string>\n");
		return 0;

	}


	int len = strlen(argv[1]);
	char input_string[len];
	strcpy(input_string,argv[1]);

	struct damonArray damon;
	damon.data = input_string;
	damon.length = len;

	printf("The string you entered was: %s\n", input_string);

	



}



























