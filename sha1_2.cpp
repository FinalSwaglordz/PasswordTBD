/*
This file takes 1 string input, calculates the SHA1 hash, and outputs the result to the console and to a "temp_file.txt".
To Compile: gcc sha1.cpp -lcrypto -o sha
To Execute: ./sha [STRING]
	ex: ./sha tom

Useful links:	https://memset.wordpress.com/2010/10/06/using-sha1-function/
*/

#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

using namespace std;

char* hash_function(char* input_string)
{
	int i = 0;
	unsigned char temp[SHA_DIGEST_LENGTH]; //where we will store the SHA digest. length = 20
	char buf[SHA_DIGEST_LENGTH*2];

	memset(temp, 0x0, SHA_DIGEST_LENGTH);  //array of size 20 to store SHA1 digest
	memset(buf, 0x0, SHA_DIGEST_LENGTH*2); //array of size 2*20 to store hex result?

	SHA1((unsigned char *)input_string, strlen(input_string), temp);
	
	for(i=0; i<SHA_DIGEST_LENGTH; i++){
		sprintf((char*)&(buf[i*2]), "%02x", temp[i]);
		//element in temp[i] formatted with %02x and stored in buf[i*2]
	}
	
	//printf("In FUNCTION: %s\n", buf);
	return (char *)&buf;
}

int main(int argc, char * argv[])
{
	if(argc != 2)
	{
		printf("Usage: %s <string>\n", argv[0]);
		return -1;
	}
	
	char *hash = hash_function(argv[1]);
	
	printf("Plaintext:\t%s\nSHA-1:\t\t%s\n\n", argv[1], hash);
	
	//FILE *file = fopen("temp_file.txt", "a+"); //open file to write to
	//fprintf(file, "Plaintext: %s\nSHA-1: %s\n\n", argv[1], buf);

	return 0;
}