#include "Procesor.hpp"
#include <iostream>

bool debug = true;

Procesor::Procesor() //maska inaczej?
{
	mask[0] = true;
	for (int i = 1; i < 8; i++)
	{
		mask[i] = false;
	}
}


Procesor::~Procesor()
{
}

void Procesor::add(Process&ready) // przemysl czy ageing musi by� oddzielny i czy chcesz doda� cos do PCB
{
	int it = ready.process_priority;
	main_queue[it].push_back(ready);
	mask[it] = true;
}



void Procesor::find_and_run(Procesor& p) //przemysl jak sprawdzac czy pojawil sie nowy proces
{
	int it = 8;
	while (it < 0)
	{
		if (p.mask[it] == true)
		{
				Process temp = main_queue[it].front;
				temp.process_status = AKTYWNY;
				main_queue[it].pop_front;
				if (main_queue[it].empty())
				{
					p.mask[it] = false;
				}
				else
				{
					p.mask[it] = true;
				}
		}
		else if (it == 0)
		{
			Process temp = main_queue[it].front;
			temp.process_status = AKTYWNY;
		}
		else continue;

		it--;
	}
}



void Procesor::age(Procesor& p)
{

}
