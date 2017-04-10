#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>



void * do_werk(void *arg)
{

	



}

int first_inc(char *c){
    if(c[0]==0) return 0;
    if(c[0]=='z')
	{
        c[0]='0';
        return inc(c+sizeof(char));
    }   
    c[0]++;
    return 1;
}

int second_inc(char *c){
    if(c[0]==0) return 0;
    if(c[0]=='z')
	{
        c[0]='0';
        return inc(c+sizeof(char));
    }   
    c[0]++;
    return 1;
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

	int n = 5;

	char *c_first_half = new char[((n+1)*sizeof(char))];
	char *c_second_half = new char[((n+1)*sizeof(char))];

	pthread_t threads[2];
	pthread_create( &threads[0], NULL, do_werk, &thread_args[]);

}
