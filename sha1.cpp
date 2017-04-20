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

int main(int argn, char * argv[])
{
	int i = 0;
	unsigned char temp[SHA_DIGEST_LENGTH]; //where we will store the SHA digest. length = 20
	char buf[SHA_DIGEST_LENGTH*2];

	if(argn != 2)
	{
		printf("Usage: %s string\n", argv[0]);
		return -1;
	}

	memset(temp, 0x0, SHA_DIGEST_LENGTH);  //array of size 20 to store SHA1 digest
	memset(buf, 0x0, SHA_DIGEST_LENGTH*2); //array of size 2*20 to store hex result?

	SHA1((unsigned char *)argv[1], strlen(argv[1]), temp);

	FILE *file = fopen("temp_file.txt", "a+"); //open file to write to

	for(i=0; i<SHA_DIGEST_LENGTH; i++){
		sprintf((char*)&(buf[i*2]), "%02x", temp[i]); //printing each element in buf[] as hex?
	}

	printf("Plaintext:\t%s\nSHA-1:\t\t%s\n\n", argv[1], buf);
	fprintf(file, "Plaintext: %s\nSHA-1: %s\n\n", argv[1], buf);

	return 0;
}
