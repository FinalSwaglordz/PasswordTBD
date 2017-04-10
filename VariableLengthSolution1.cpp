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


int inc(char *c){
    if(c[0]==0) return 0;
    if(c[0]=='z')
	{
        c[0]='0';
        return inc(c+sizeof(char));
    }   
    c[0]++;
    return 1;
}


int first_thread(void * args)
{

char **input_string =(char**) args;

int n1 = 5;
char *c_first_thread = new char[((n1+1)*sizeof(char))];

int i,j;

for( i=1;i<=(n1-1);i++){
        for( j=0;j<i;j++) 
		{		
			c_first_thread[j]='0';
		}
    	c_first_thread[i]=0;
    	do 
		{
       		
			
			if(strcmp(input_string, c_first_thread) == 0)
			{
				printf("The program has determined that you entered: %s\n", c_first_thread);
				//ong serialStopTimer = stop_timer(serialStartTimer, "Serial run time: ");
				free(c_first_thread);				
				return 0;	
			}
			
			
			//printf("%s\n",c);

    	} 
		while(inc(c_first_thread));    
	}



}

int second_thread(void * args)
{

int n2 = 5;
char *c_second_thread = new char[((n2+1)*sizeof(char))];
int i,j;

char **input_string =(char**) args;

	for(i = 0; i < n2; i++)
	{
	c_second_thread[i]= '0';
	}



       
    	c_second_thread[5]=0;
    	do 
		{
       		
			
			if(strcmp(input_string, c_second_thread) == 0)
			{
				printf("The program has determined that you entered: %s\n", c_second_thread);
				//long serialStopTimer = stop_timer(serialStartTimer, "Serial run time: ");
				free(c_second_thread);				
				return 0;	
			}
			
			
			//printf("%s\n",c);

    	} 
		while(inc(c_second_thread));    
}




int main( int argc, char* argv )
{

	if(argc != 2)
	{

		printf("Incorrect number of arguments.  Argument list is <execname> <input_string>\n");
		return 0;

	}


	int len = strlen(argv[1]);
	char input_string[len];
	strcpy(input_string,argv[1]);

	printf("The string you entered was: %s\n", input_string);

	


	int x,y;
	pthread_t thread1,thread2;
	pthread_create(&thread1,NULL,first_thread,  input_string);
	pthread_create(&thread2,NULL,second_thread, input_string);

}
