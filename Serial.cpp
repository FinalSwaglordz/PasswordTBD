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
#include <signal.h>
using namespace std;
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>


ofstream personalOutputFile;
ofstream totalOutputFile;

long serialStartTimer;
long serialStopTimer;

int found = 0;
int quit = 0;
int cancel = 0;

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

void sigintHandler(int sig_num)
{
	
	printf("\nYou cancelled the search\n");
	serialStopTimer = stop_timer(serialStartTimer, "Run time: ");
	cancel = 1;
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

	mkdir("OutputFiles", ACCESSPERMS);
	printf("Output Directory: OutputFiles\n");
	

	signal(SIGINT, sigintHandler);

	serialStartTimer = start_timer();

	int len = strlen(argv[1]);
	char input_string[len];
	strcpy(input_string,argv[1]);
	
	personalOutputFile.open("OutputFiles/Serial_Output.csv", std::ios_base::app);
	totalOutputFile.open("OutputFiles/Final_Project_Total_Data.csv", std::ios_base::app);

	totalOutputFile << "Serial,";

	personalOutputFile << input_string << ",";
	totalOutputFile << input_string << ",";

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

			serialStopTimer = stop_timer(serialStartTimer, "Serial run time: ");

			personalOutputFile << serialStopTimer << ",";
			totalOutputFile << serialStopTimer << ",";

			float min = ((float) serialStopTimer)/(1000000*60);

			personalOutputFile  << min << ",";
			totalOutputFile    << min << ",";

			
			
		}
		if(cancel)
		{
			break;
		}
			//printf("%s\n",c);

    	} 
	while(inc(c));
	}
	if(cancel)
	{
		personalOutputFile << "N/A,N/A,Cancelled,N/A" << endl;
		totalOutputFile << "N/A,N/A,Cancelled,N/A" << endl;
		personalOutputFile.close();
		totalOutputFile.close();
		
	}
	else
	{
		

		if(found)
		{
			printf("Input could not be found. Are you sure you entered valid input?\n");
			printf("Character Alphabet for this version: ASCII 'a'-'z'\n");
		}
		else
		{
			personalOutputFile << "Found";
			totalOutputFile << "Found";
		}

		personalOutputFile << ","  << "N/A"  <<  endl;
		totalOutputFile << ","  << "N/A"  <<  endl;

		personalOutputFile.close();
		totalOutputFile.close();

	}


		
		
    
	
	//long serialStopTimer = stop_timer(serialStartTimer, "Serial run time: ");
	printf("EXITING\n\n");
	free(c);
}







