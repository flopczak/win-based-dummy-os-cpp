#include "Procesor.hpp"
#include <iostream>

//w konstruktorze procesu automatyczne dodawanie 

bool work = true;

Procesor::Procesor(Process_List* p)
{
	this->temporary = p;
	new_process = false;
	for (int i = 0; i < 8; i++)
	{
		mask[i] = false;
	}
}


Procesor::~Procesor()
{
}

void Procesor::check(Process&ready)
{
	if (ready.process_priority > running.process_priority)
	{
		if (running.process_priority != 0)
		{
			running.process_status = GOTOWY;
			int it = running.process_priority;
			main_queue[it].push_back(running);
			running = ready;
			running.process_status = AKTYWNY;
			mask[it] = true;
		}
		if (running.process_priority == 0)
		{
			running.process_status = GOTOWY;
			int it = running.process_priority;
			running = ready;
			running.process_status = AKTYWNY;
			mask[it] = true;
		}
	}
	else
	{
		std::cout << "po dodaniu procesu nie wystąpiło wywłaszczenie " << endl;
	}

}

void Procesor::add(Process& ready)
{;
	int it = ready.process_priority;
	main_queue[it].push_back(ready);
	mask[it] = true;
	new_process = true;
	//check gdy flaga new proces jest true wywołanie funkcji check w celu sprawdzenia czy nowy
	//proces ma wyższy priorytet od bierzącego w razie ew wywłaszenia
	check(ready);
}

int Procesor::find(Procesor&p)
{
	int it = 7;
	while (it > 0)
	{
		if (p.mask[it] == true)
		{
			running = main_queue[it].front();
			main_queue[it].pop_front();
			if (main_queue[it].empty())
			{
				p.mask[it] = false;
			}
			else
			{
				p.mask[it] = true;
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

void Procesor::run(Procesor& p) //sprawdzanie co każdą iterację pentli w main
{
	running.process_status = AKTYWNY;
	//wykonanie rozkazu asemblerowego
	cout << "running: " << &running.process_name << endl;
	/*
	to chyba powinno być w funkcji wyszukującej
	main_queue[it].pop_front();

	if (main_queue[it].empty())
	{
		mask[it] = false;
	}
	*/
	cin.get();

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
