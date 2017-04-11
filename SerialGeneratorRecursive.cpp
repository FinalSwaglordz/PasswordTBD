#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/time.h>
#include <math.h>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <string.h>


long long start_timer()
{
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

int main(int argc, char* argv[])
{
		
	if(argc != 2)
	{
		printf("Incorrect number of arguments.  Argument list is <execname> <input_string>\n");
		return 0;
	}
	
	long serialStartTimer = start_timer();

	int len = strlen(argv[1]);
	char input_string[len];
	strcpy(input_string,argv[1]);
	

    int n = len;
    int i,j;
    char *c = new char[((n+1)*sizeof(char))];
	printf("The string you entered was: %s\n", input_string);
	//char set[] = {'a','b','c'};
		
	//i is index that keeps track of length.
	for(i=1;i<=n;i++)
	{

	printf("Checking Length %i\n", i);
        for(j=0;j<i;j++) 
		{		
			c[j]='a';
		}
    	c[i]=0;
    	do 
		{
       		
			
			if(strcmp(input_string, c) == 0)
			{
				printf("The program has determined that you entered: %s\n", c);
				long serialStopTimer = stop_timer(serialStartTimer, "Serial run time: ");
				free(c);				
				return 0;	
			}
			
			
			//printf("%s\n",c);

    	} 
		while(inc(c));    
	}
	//long serialStopTimer = stop_timer(serialStartTimer, "Serial run time: ");
	printf("We couldn't find that shizzzz\n");
	printf("%s\n",c);
    free(c);
}
