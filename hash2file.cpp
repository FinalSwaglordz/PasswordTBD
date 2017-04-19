/*
This file takes 1 string input, calculates the SHA1 hash, and outputs the result to the console and to a "temp_file.txt".
To Compile: g++ hash2file.cpp -lcrypto
To Execute: ./a.out [STRING]
	ex: ./a.out tom

Useful links: 	http://stackoverflow.com/questions/6934232/is-there-a-simple-c-or-c-function-that-calculates-the-sha1-hash-of-a-string
		http://stackoverflow.com/questions/5040920/converting-from-signed-char-to-unsigned-char-and-back-again
*/

#include <openssl/sha.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

int main(int argc, char ** argv)
{
	if(argc !=2)
	{
		printf("Incorrect number of arguments. Argument list is <execname> <input_string>\n");
		return 0;
	}

	FILE *file = fopen("temp_file.txt", "a+"); //open file to write to

	int len = strlen(argv[1]);

	char str[len];
	unsigned char u_str[len];

	strcpy(str, argv[1]); //copy input string into "signed char str[]"

	cout<< "str: " << str << "-END\n"; //output to assure it is correct

	//u_str = *(unsigned char*)(&str);
	unsigned char hash[20];
	unsigned char* ret;

	ret = SHA1(u_str, sizeof(u_str)-1, hash);
	cout<< "Hash: " << ret << "-END\n"; //this is the calculated SHA1 hash

	fputs("String: ",file);
	fputs(str, file); //output ret to file
	fputs("\nHash: ",file);
	fputs((char*)ret, file);
	fputs("\n\n",file);

	//sleep(2);
	//cin.get(); //wait for user input

	return 0;
}
