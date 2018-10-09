#include <stdio.h>
#include<unistd.h>


#include<thread>
#include<queue>
#include<mutex>
#include<vector>
#include <iostream>
#include<string.h>



int main(int argc, char *argv[])
{
	//dvojice argumentu pro regex + './psed' => lichy pocet, presmerovani stdin se jako argument nepocita
	if ((argc < 3) || (argc % 2 == 0))
		printf("spravne pouziti ./psed RE1 REPL1 [ RE2 REPL2 ] [ RE3  REPL3 ] ...\n");



	/*
	int res;
	line=read_line(&res);
	printf("%d\n", argc);
	*/

	

	return 0;
}