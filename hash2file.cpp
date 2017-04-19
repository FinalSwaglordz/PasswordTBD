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
	FILE *file = fopen("temp_file.txt", "w"); //open file to write to

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
	fputs("\tHash: ",file);
	fputs((char*)ret, file);
	fputs("\n\n",file);

	sleep(2);
	//cin.get(); //wait for user input

	return 0;
}
