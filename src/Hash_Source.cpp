/*
http://sha1-hash-online.waraxe.us/
This program will take a hash and find the string which creates that hash.
*/

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
#include <openssl/sha.h> //needed for SHA1 function

using namespace std;

int found[26];

char input_string[40];
char result_string[10];

long serialStartTimer;
long serialStopTimer;
long serialCheckTimer;

ofstream personalOutputFile;
ofstream totalOutputFile;

int minutes = 0;
int quit = 0;

int wait_Time = 100000;

struct threadData
{
	char * data;
	int length;
	char first_letter;
	char last_letter;
	int threadNum;
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
        std::cout << std::setprecision(7);	
	std::cout << name << ": " << ((float) (end_time - start_time)) / (1000 * 1000) << " sec\n";
	return end_time - start_time;
}

void sigintHandler(int sig_num)
{
	
	printf("\nYou cancelled the search\n");
	serialStopTimer = stop_timer(serialStartTimer, "Run time: ");
	quit = 1;
}

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


char* hash_function(char* input_string)
{
	int i = 0;
	unsigned char temp[SHA_DIGEST_LENGTH]; //where we will store the SHA digest. length = 20
	char *buf = (char *)malloc(SHA_DIGEST_LENGTH*2); //dont need (char *) if C. do need for C++
	if(buf == NULL)
	{
		return NULL;
	}
	
	memset(temp, 0x0, SHA_DIGEST_LENGTH);  //array of size 20 to store SHA1 digest
	memset(buf, 0x0, SHA_DIGEST_LENGTH*2); //array of size 2*20 to store hex result?
	
	SHA1((unsigned char *)input_string, strlen(input_string), temp);
	
	for(i=0; i<SHA_DIGEST_LENGTH; i++){
		sprintf((char*)&(buf[i*2]), "%02x", temp[i]);
		//element in temp[i] formatted with %02x and stored in buf[i*2]
	}
	
	//printf("In FUNCTION: %s\n", buf);
	return buf;
}


void* method (void *args)
{
	struct threadData *methodData = (struct threadData*) args;
	char *input_string = methodData -> data;
	int i,j,k,n = methodData -> length;
	char first = methodData -> first_letter;
	char last = methodData -> last_letter;
	int threadNum = methodData -> threadNum;
	int match, t;
	
	char *c = new char[((n+1)*sizeof(char))];
	
	char *hash;
	
	for(i = 1; i <= n; i++)
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
			//printf("Run: %i\n", times_run++, threadNum);
			hash = hash_function(c);
			
			match = 1;
			
			for(t=0; t<40; t++)
			{
				if(input_string[t] != hash[t])
				{
					match = 0;
				}
			}
			
			if(false)//(threadNum == 0)
			{
			printf("Thread %i:::::\ninput_HASH=\t\t%s\nBrute hash=\t\t%s\nBruteForce string=\t%s\n\n", threadNum, input_string, hash, c);
			}
			
			//if(strcmp(input_string, hash) == 0)
			if(match == 1)
			{
				printf("\nThread %i found: %s\n\n", threadNum, c);
				
				//set global variable to result so main() can see it
				sprintf(result_string, "%s", c);
			
				personalOutputFile << c;
				totalOutputFile << c;
			
				found[threadNum] = 1;
			
				return methodData;
			}
		
			if(strcmp(c, end) == 0)
			{
				//printf("Input was equal to z?");
				break;
			}
	
			free(hash);
	
		}
		while(inc(c));
	
	}
	
	

}


int main( int argc, char ** argv)
{

	if(argc != 3)
	{
		printf("Incorrect number of arguments.  Argument list is <execname> <input_HASH> <number_of_threads>\n");
		return 0;
	}
	
	
	
	int len = strlen(argv[1]);
	//char input_string[len]; //defined as GLOBAL
	
	int threads = atoi(argv[2]);
	int alphabet = 26;
	int baselettersperthread = alphabet/threads;
	int extraletters =  alphabet % threads;
	
	mkdir("OutputFiles", ACCESSPERMS);
	printf("Output Directory: ../OutputFiles\n");
	
	signal(SIGINT, sigintHandler);
	
	personalOutputFile.open("OutputFiles/Parallel_Variable2_Output.csv", ios::out |  std::ios_base::app);
	totalOutputFile.open("OutputFiles/Final_Project_Total_Data.csv", std::ios_base::app);
		
	totalOutputFile << "Hash_Source,";
	personalOutputFile << "Hash_Source,";
	
	for(int i = 0; i < threads; i++)
	{
		found[i] = 0;
	}
	
	if(len > 40)
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
	
	totalOutputFile << input_string << ",";
	personalOutputFile << input_string << ",";
	
	totalOutputFile << threads << ",";
	personalOutputFile << threads << ",";
	

	printf("\nThe string you entered was: %s\n", input_string);
	
	serialStartTimer = start_timer();
	
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
		printf("Thread %d: Input_string: %s, First: %c, Last: %c\n", i, input_string, first_letter, last_letter);
	}
	
	pthread_t threadList[threads];
	
	for(int i = 0; i < threads; i++)
	{
		pthread_create(&threadList[i], NULL, method, &threadDataArray[i]);
	}
	
	
	
	int exit = 1;
	do
	{
		usleep(wait_Time);
		for(int i = 0; i < threads; i++)
		{
			if(found[i] == 1)
			{
				exit = 0;
			}
		}
		
		if(quit)
		{
			break;
		}
	
	
	}
	while(exit);
	
	
	//printf("Im out\n");
	
	for(int i = 0; i < threads; i++)
	{
		printf("Thread %d found: %d\n", i, found[i]);
	}
	
	if(quit)
	{
		personalOutputFile << input_string << "," << "N/A" << "," << "N/A";	
		personalOutputFile << "," << "Cancelled";
		personalOutputFile << "," << "N/A" << endl;
		personalOutputFile.close();

		totalOutputFile << input_string << "," << "N/A" << "," << "N/A";	
		totalOutputFile << "," << "Cancelled";
		totalOutputFile << "," << "N/A" << endl;
		totalOutputFile.close();
	}
	else
	{
		serialStopTimer = stop_timer(serialStartTimer, "Run time: ");
		personalOutputFile  <<  "," << serialStopTimer;
		totalOutputFile  <<  "," << serialStopTimer;

		float min = ((float) serialStopTimer)/(1000000*60);

		personalOutputFile   <<  ","  << min;
		totalOutputFile   <<  ","  << min;
		
		personalOutputFile << "," << "Found";
		totalOutputFile << "," << "Found";
	}
	
	personalOutputFile << ","  << wait_Time  <<  endl;
	totalOutputFile << ","  << wait_Time  <<  endl;
	
	personalOutputFile.close();
	totalOutputFile.close();
	
	printf("\nResult: %s\n", result_string);
	printf("\nEXITING\n\n");
	
}
