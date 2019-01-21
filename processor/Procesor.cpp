#include "Procesor.hpp"
#include <iostream>



bool work = true;

Procesor::Procesor()
{
	w_counter = 1;
	new_process = false;
	mask[0] = true;
	for (int i = 1; i < 8; i++)
	{
		mask[i] = false;
	}
}


Procesor::~Procesor()
{
}

void Procesor::check(Process&ready, Procesor&p)
{
	if (ready.process_priority > p.running.process_priority)
	{
		if (p.running.process_priority != 0)
		{
			p.running.process_status = GOTOWY;
			int it = p.running.process_priority;
			p.main_queue[it].push_back(p.running);
			p.running = ready;
			p.running.process_status = AKTYWNY;
			p.mask[it] = true;
			p.new_process = false;
		}
	}
	else
	{
		p.new_process = false;

		std::cout << "nowy proces ma taki sam priorytet lub mniejszy kontynuje prace " << endl;
	}

}

void Procesor::add(Process&ready, Procesor&p)
{
	int it = ready.process_priority;
	main_queue[it].push_back(ready);
	mask[it] = true;
	new_process = true;
	check(ready, p);

}






void Procesor::find_and_run(Procesor& p) //sprawdzanie co każdą iterację pentli w main
{
	int it = 7;
	while (it > 0)
	{
		if (p.mask[it] == true)
		{

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

	running = main_queue[it].front();
	running.process_status = AKTYWNY;
	cout << "running: " << &running.process_name << endl;
	main_queue[it].pop_front();
	if (main_queue[it].empty())
	{
		mask[it] = false;
	}
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
