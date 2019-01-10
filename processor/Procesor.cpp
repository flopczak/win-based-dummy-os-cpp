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

void Procesor::add(Process&ready) // przemysl czy ageing musi byæ oddzielny i czy chcesz dodaæ cos do PCB
{
	int it = ready.process_priority;
	main_queue[it].push_back(ready);
	mask[it] = false;
}



void Procesor::find_and_run()
{
}

void Procesor::remove()
{
}

void Procesor::age()
{
}
