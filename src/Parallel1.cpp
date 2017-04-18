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



int thread1_active;
int thread2_active;
int thread1_found;
int thread2_found;

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


// Prints the time elapsed since the specified time
long long stop_timer(long long start_time, std::string name) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	long long end_time = tv.tv_sec * 1000000 + tv.tv_usec;
        std::cout << std::setprecision(5);	
	std::cout << name << ": " << ((float) (end_time - start_time)) / (1000 * 1000) << " sec\n";
	return end_time - start_time;
}


int inc(char *c){
    if(c[0]==0) return 0;
    if(c[0]=='z')
    {
        c[0]='a';
        return inc(c+sizeof(char));
    }   
    c[0]++;
    return 1;
}


void* second_thread( void* args)
{

	struct damonArray *damon = (struct damonArray*) args;

	char *input_string = damon -> data;


	int i, j, n = damon -> length;
	char *c_first_thread = new char[((n+1)*sizeof(char))];

	

	printf("The second thread is looking for: %s\n", input_string);

	for( i=n;i<=n;i++)
	{
       		for( j=0;j<i;j++) 
		{		
			c_first_thread[j]='a';
		}
    			c_first_thread[i]=0;
    			do 
			{
       				if(strcmp(input_string, c_first_thread) == 0)
				{
					printf("Thread 2 has determined that you entered: %s\n", c_first_thread);
					//long serialStopTimer = stop_timer(serialStartTimer, "Serial run time: ");
				
					free(c_first_thread);
					thread2_found = 1;				
					return damon;	
				}
			
			
			//printf("%s\n",c_first_thread);

    			} 
			while(inc(c_first_thread));
	}
	printf("The second thread did not find the string\n");
	thread2_active = 0;
}


void* first_thread( void* args)
{

	struct damonArray *damon = (struct damonArray*) args;

	char *input_string = damon -> data;
	
	int i,j, n = damon -> length;

	char *c_first_thread = new char[((n+1)*sizeof(char))];
	//long serialStartTimer = start_timer();
	

	printf("The first thread is looking for: %s\n", input_string);



		for( i=1;i<=(n-1);i++)
		{
       			for( j=0;j<i;j++) 
			{		
				c_first_thread[j]='a';
			}
    			c_first_thread[i]=0;
    			do 
			{
       				if(strcmp(input_string, c_first_thread) == 0)
				{
					printf("Thread 1 has determined that you entered: %s\n", c_first_thread);
					//long serialStopTimer = stop_timer(serialStartTimer, "Serial run time: ");
				
					free(c_first_thread);	
					thread1_found = 1;			
					return damon;	
				}
			
			
			//printf("%s\n",c_first_thread);

    			} 
			while(inc(c_first_thread));    
		}

	printf("The first thread did not find: %s\n", input_string);
	thread1_active = 0;
}


int main( int argc, char ** argv )
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

	printf("\nThe string you entered was: %s\n", input_string);

	

	long serialStartTimer = start_timer();
	

	thread1_active = 1;
	thread2_active = 1;
	thread1_found = 0;
	thread2_found = 0;


	pthread_t thread1,thread2;
	pthread_create(&thread1, NULL , first_thread, &damon);
	pthread_create(&thread2, NULL , second_thread, &damon);
	int exit = 1;
	do
	{
		if(thread1_active == 0 && thread2_active == 0)
		{
			exit = 0;
		}
		if(thread1_found)
		{
			exit = 0;
		}		
		if(thread2_found)
		{
			exit = 0;
		}

		usleep(10000);
		
	}
	while(exit);
	
	if(thread1_active)
	{
		pthread_cancel(thread1);
	}
	if(thread2_active)
	{
		pthread_cancel(thread2);
	}
	
	long serialStopTimer = stop_timer(serialStartTimer, "Run time: ");

	printf("EXITING\n");
	/*
	pthread_cancel(thread1);
	pthread_cancel(thread2);
	*/
	
	//pthread_join(thread1, NULL);
	//pthread_join(thread2, NULL);

	

}
