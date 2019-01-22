#include "Procesor.hpp"
#include <iostream>

//TODO gdzies jest problem bo mapa cały czas pusta

//w konstruktorze procesu automatyczne wywołanie funkcji dodającej do mapy kolejek done V
// zobaczyczyć jak synchronizacja zmienia stan procesu na oczekujący zeby wywłaszczenie

bool work = true;

Procesor::Procesor() //Procesor::Procesor(Process_List* p)
{

	new_process = false;
	for (int i = 0; i < 8; i++)
	{
		mask[i] = false;
	}
	running = DUMMY;
	mask[0] = true;
}


Procesor::~Procesor()
{
}

//zmien check
// od stattu running powinnien byc dummy / cos tu na dole jest nie tak bo runnig jest defaultowy
void Procesor::check(Process&ready)
{
	if (ready.process_priority > running.process_priority)
	{
		if (ready.process_priority > 0 && ready.process_priority < 8)
		{
			running.process_status = GOTOWY;
			int it = running.process_priority;
			main_queue[it].push_back(running);
			mask[it] = true;
			running = ready;
			;
			cout << "nastąpilo wywlaszenie..." << endl;
		}
		else if (running.process_priority == 0)
		{
			running.process_status = GOTOWY;
			int it = running.process_priority;
			main_queue[it].push_back(running);
			running = ready;
			mask[it] = true;
		}
		else
		{
			cout << "jak to jest możliwe że prtiorytet jest spoza zakresu";
		}
	}
	else
	{
		std::cout << "po dodaniu procesu nie wystąpiło wywłaszczenie " << endl;
	}

}
//problem z procesor&p z referencja lub z raczej iteratorem listy
void Procesor::add() // dodawanie do main_queue linija kodu z main niezbedna
{

	for (int i = 0; i < temporary.size(); i++)
	{
		int it = temporary.front().process_priority;
		Process ready = temporary.front();
		main_queue[it].push_back(ready);
		temporary.pop_front();
		mask[it] = true;
		check(ready);
	}
	//new_process = true;
	//check gdy flaga new proces jest true wywołanie funkcji check w celu sprawdzenia czy nowy
	//proces ma wyższy priorytet od bierzącego w razie ew wywłaszenia

}

//Procesor::find(Procesor&p) usunąłem z funkcji wszystkie p.
void Procesor::find()
{
	int it = 7;
	while (it > 0)
	{
		if (mask[it] == true)
		{
			running = main_queue[it].front();
			main_queue[it].pop_front();
			if (main_queue[it].empty() == true)
			{
				mask[it] = false;
			}
			else
			{
				mask[it] = true;
			}
			break;
		}
		else if (it == 0)
		{
			running = main_queue[it].front();
			cout << "running DUMMY" << endl;
		}
		else
		{
			it--;
		}
	}
}



//run konrada to excute bala

void Procesor::run() //sprawdzanie co każdą iterację pentli w main
{
	find(); // to juz mi przypisze odpowiedni proces do running czy to moze byc?(jako wywlaszenie)
	running.process_status = AKTYWNY;
	//tu wstawienie running do metody run konrada w celu wykonania rozkazu asemblera

	cout << "running: " << &running.process_name << endl;
	priority_inc();
	/*
	to chyba powinno być w funkcji wyszukującej
	main_queue[it].pop_front();

	if (main_queue[it].empty())
	{
	mask[it] = false;
	}
	*/
	system("pause");
}

//funkcja zwiększająca wszystkie priotytety procesów gotowych!
void Procesor::priority_inc()
{
	int i = 7;
	while (i > 0)
	{
		if (main_queue[i].empty())
		{
			i--;
			continue;
		}
		else
		{
			for (auto j : main_queue[i])
			{
				if (j.process_status == GOTOWY)
				{
					if (j.program_instructions > 0 && j.program_instructions < 4)
					{
						j.program_instructions++;
					}
					else if (j.program_instructions == 4)
					{
						age(j);
						j.program_instructions = 0;
					}
					else
						j.program_instructions = 0;
				}
			}
		}

		i--;
	}
}
//w konstruktorze zrobic puste kolejki w kazdym szczeblu mapy tak jak tu
void Procesor::displayMap()
{
	for (auto a : main_queue)
	{
		if (mask[a.first] == true)
		{
			cout << "klucz: " << a.first << endl;
			cout << "value: " << a.second.front().process_name << endl;

		}
	}
}

void Procesor::age(Process& p)
{
	if (p.process_priority > 0 && p.process_priority < 2)
	{
		p.process_priority = 2;
	}
	else if (p.process_priority > 0 && p.process_priority > 1 && p.process_priority < 4)
	{
		p.process_priority = 4;
	}
	else if (p.process_priority > 0 && p.process_priority > 3 && p.process_priority < 6)
	{
		p.process_priority = 6;
	}
	else if (p.process_priority > 0 && p.process_priority == 6)
	{
		p.process_priority = 7;
	}
}
