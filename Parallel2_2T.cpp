
//Imported Packages, not sure if they all are needed :/
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



/*
global varibles to check if the threads are active or if either thread
found the input.
*/
int thread1_active;
int thread2_active;
int thread1_found;
int thread2_found;


//A struct I made to pass multiple arguments into pthread_create
struct damonArray
{
	char * data;
	int length;

};

/*
Timing methods
*/
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


/*
Incrementing method to iterate from one string to the next.
Can be used by any number of threads, assuming the threads are all initialized to their the beginning of their respective character spaces and themselves provide the checks to stop at the end of their character space
*/

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

/*
Method for the second thread.  
Searches the characer space aaa....an (n being the letter, not the length of the input)
For example, for input length 4, this thread would search (n-z), (an-zz), (aan-zzz), (aaan-zzzz)
*/
void* second_thread(void*args)
{

	struct damonArray *damon = (struct damonArray*) args;

	char *input_string = damon -> data;
	
	int i,j,n = damon -> length;

	char *c_second_thread = new char[((n+1)*sizeof(char))];

	printf("The second thread is looking for: %s\n", input_string);

	for( i=1;i<=n;i++)
	{
		/*
		for( j=0;j<i;j++) 
		{		
			c_second_thread[j]='a';
		}
		*/
		printf("2: Checking Length %i\n", i);		
		c_second_thread[i-1] = 'n';
		for( j=0; j< n-2; j++)
		{
			c_second_thread[j]='a';
		}
		c_second_thread[i]=0;
		do 
		{
			//printf("2: %s\n",c_second_thread);       			
			if(strcmp(input_string, c_second_thread) == 0)
			{
				printf("Thread 2 has determined that you entered: %s\n", c_second_thread);
				thread2_found = 1;	
				
				free(c_second_thread);	
							
				return damon;	
			}
			
			
			

    		} 
		while(inc(c_second_thread));    

	}
	printf("The second thread did not find: %s\n", input_string);
	thread2_active = 0;
}

/*
Method for the first thread.  
Searches the characer space (aaaa....-zzzzm)
For example, for input length 4, this thread would search (a-z), (aa-zm), (aaa-zzm), (aaaa-zzzm)
**Notice, there is some slight overlap between the threads, specifically (n-z) gets done twice, but I mean come-on, its one set of like 13 letters. Its no big deal.  It doesn't manifest into the longer length inputs.
*/

void* first_thread( void* args)
{

	struct damonArray *damon = (struct damonArray*) args;
	char *input_string = damon -> data;
	int i,j,k,n = damon -> length;
	char *c_first_thread = new char[((n+1)*sizeof(char))];

	printf("The first thread is looking for: %s\n", input_string);
	
	


	for( i=1;i<=n;i++)
	{
		
		printf("1: Checking Length %i\n", i);		
		char * end = new char[((i+1)*sizeof(char))];
		for( k = 0; k<(i-1); k++)
		{
			end[k] = 'z';
		}
		end[k] = 'm';


		for( j=0;j<i;j++) 
		{		
			c_first_thread[j]='a';
		}
		c_first_thread[i]=0;
		do 
		{
       			
			//printf("1: %s\n",c_first_thread);
			if(strcmp(input_string, c_first_thread) == 0)
			{
				printf("Thread 1 has determined that you entered: %s\n", c_first_thread);
				thread1_found = 1;	
				
				free(c_first_thread);	
							
				return damon;	
			}
			
			if(strcmp(c_first_thread, end) == 0)
			{
								
				break;
			}
			
			
			//printf("end: %s\n", end);
			

    		} 
		while(inc(c_first_thread));    

	}
	printf("The first thread did not find: %s\n", input_string);
	thread1_active = 0;

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
		
		usleep(50000);

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

	if(thread1_found == 0 && thread2_found == 0)
	{
		printf("Input could not be found.  Are you sure you entered valid input?\n");
		printf("Character Alphabet for this version: ASCII 'a'-'z'\n");
	}
	
	printf("EXITING\n\n");

}



























