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
int end;
int line_done;


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
	while(!end)
	{	
		while(line_done == 0);
		std::string output = regex_replace (line, r1, reg2);
		
		while (order != counter && end != 1);
		if(end == 0)
		{
			printf("%s\n", to_cstr(output)); 
			counter++;
			while(counter != -1);
		}
	}

	
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
	end = 0;
	counter = -1;//pricitat a pri spravnem poradi provest urceny regex
	//z -1 do 0 pricte main, pote pricitaji jednotlive thready

	line_done = 0;
	//tvorba pole threadu(prazdne)
	int num_regex = (argc - 1) / 2;
	std::vector <std::thread *> threads; /* pole threadu promenne velikosti */
	threads.resize(num_regex); /* nastavime si velikost pole threads */

	//mutexy
	std::mutex mutex_1;
	for(int i = 0;i < num_regex;i++)
	{	
		std::thread *new_thread = new std::thread (f,argv[i * 2+1],argv[i * 2+2], order);
		threads[i]=new_thread;
		order++;
	}
	
	int res;//result
	line=read_line(&res);
	line_done = 1;
	while (res) 
	{
		counter++;//spusteni threadu
		mutex_1.lock();
		while (counter != num_regex)
		{
			mutex_1.unlock();
			mutex_1.lock();
		}
		mutex_1.unlock();
		counter = -1;
		line_done = 0;
		free(line);
		line=read_line(&res);

		line_done = 1;

	}
	sleep(1);
	end = 1;

	/* provedeme join a uvolnime pamet threads */
	for(int i=0;i<num_regex;i++)
	{
		(*(threads[i])).join();
		delete threads[i];
	}

	return 0;
}