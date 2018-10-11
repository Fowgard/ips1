//Daniel Bílý(xbilyd01) a Jakub Gajdošík(xgajdo24)
#include <stdio.h>
#include<unistd.h>
#include<thread>
#include<queue>
#include<mutex>
#include<vector>
#include <iostream>
#include<string.h>
#include <regex>

char *line;

char *to_cstr(std::string a) 
{
	// prevede retezec v c++ do retezce v "c" (char *)
	char *str;
	str=(char *) malloc(sizeof(char)*(a.length()+1));
	strcpy(str,a.c_str());
	return str;
}

char *read_line(int *res)
{
	std::string line;
	char *str;
	if (std::getline(std::cin, line)) 
	{
		str=to_cstr(line);
		*res=1;
		return str;
	} 
	else 
	{
		*res=0;
		return NULL;
	}
}

void f (char *reg1, char *reg2)
{
	/*
	printf("VYSTUP: %s %s\n",reg1, reg2);
	std::regex r1 (reg1);
	std::regex r2 (reg2);
	*/
	
	//random regex z netu, funguje, muj nefunguje
	std::string s ("there is a subsequence in the string\n");
  	std::regex e ("\\b(sub)([^ ]*)");   // matches words beginning by "sub"
	std::cout << std::regex_replace (s,e,"sub-$2");

	//printf("%s",to_cstr(std::regex_replace (line, r1, r2))); 
	
}

int main(int argc, char *argv[])
{
	//dvojice argumentu pro regex + './psed' => lichy pocet, presmerovani stdin se jako argument nepocita
	if ((argc < 3) || (argc % 2 == 0))
	{
		printf("spravne pouziti ./psed RE1 REPL1 [ RE2 REPL2 ] [ RE3  REPL3 ] ...\n");
		exit(1);
	}

	int num_regex = (argc - 1) / 2;
	std::vector <std::thread *> threads; /* pole threadu promenne velikosti */
	threads.resize(num_regex); /* nastavime si velikost pole threads */

	
	
	/*
	std regex replace

	regex compile

	usleep pro deadlock

	1 nebo 2 zamky


	*/
	//nacitani radku
	int res;//result

	line=read_line(&res);
	while (res) 
	{
		//	printf("%s\n",line);

		for(int i = 0;i < num_regex;i++)
		{	
			std::thread *new_thread = new std::thread (f,argv[i * 2+1],argv[i * 2+2]);
			threads[i]=new_thread;
		}

		free(line); /* uvolnim pamet */
		line=read_line(&res);

	}

	sleep(1);//aby vlakna stihla vypsat

	/* provedeme join a uvolnime pamet threads */
	for(int i=0;i<num_regex;i++){
		(*(threads[i])).join();
		delete threads[i];
	}

	return 0;
}