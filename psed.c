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
int counter; 
char * test_line;

/*

posilat poradi do regexu
aktivni cekani na svou hodnotu
az potom vypis

odstranit nektere includy, jsou skopirovane z kostry

*/

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

void f (char *reg1, char *reg2, int order)
{
	
	
	
	std::regex r1 (reg1);
	while (order != counter);
	
	printf("OUTPUT: %s\n",to_cstr(std::regex_replace (test_line, r1, reg2))); 
	
	
	counter++;
		
	

	
}

int main(int argc, char *argv[])
{
	//dvojice argumentu pro regex + './psed' => lichy pocet, presmerovani stdin se jako argument nepocita
	if ((argc < 3) || (argc % 2 == 0))
	{
		printf("spravne pouziti ./psed RE1 REPL1 [ RE2 REPL2 ] [ RE3  REPL3 ] ...\n");
		exit(1);
	}
	
	int order = 0;//kazdy regex ma sve poradi
	
	counter = -1;//pricitat a pri spravnem poradi provest urceny regex
	//z -1 do 0 pricte main, pote pricitaji jednotlive thready
	test_line = to_cstr("Ahoj, tohle je pokus");


	//tvorba pole threadu(prazdne)
	int num_regex = (argc - 1) / 2;
	std::vector <std::thread *> threads; /* pole threadu promenne velikosti */
	threads.resize(num_regex); /* nastavime si velikost pole threads */

	//mutexy
	std::mutex mutex_1;
	std::mutex mutex_2;

	for(int i = 0;i < num_regex;i++)
	{	
		std::thread *new_thread = new std::thread (f,argv[i * 2+1],argv[i * 2+2], order);
		threads[i]=new_thread;
		order++;
	}

	

	int res;//result
	line=read_line(&res);
	while (res) 
	{
		counter++;//spusteni threadu

		//aktivni cekani nefunguje??
		mutex_1.lock();
		while (counter != num_regex) {
			mutex_1.unlock();
			mutex_1.lock();
			printf("CTU");
		}
		mutex_1.unlock();

		counter = -1;

		free(line); 
		line=read_line(&res);

	}	
	/*
	std regex replace

	regex compile

	usleep pro deadlock

	1 nebo 2 zamky


	*/


	//nacitani radku

	
	sleep(1);//aby vlakna stihla vypsat

	/* provedeme join a uvolnime pamet threads */
	for(int i=0;i<num_regex;i++){
		(*(threads[i])).join();
		delete threads[i];
	}

	return 0;
}