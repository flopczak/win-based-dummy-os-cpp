#include "../processor/Procesor.hpp"
#include "Process_List.hpp"
#include "Process.hpp"
#include <iostream>

using namespace std;

Process_List::Process_List()
{

}

void Process_List::CP_1(vector<string>v)
{
	Process a(v[0]);
	Process_List::PrcList.push_front(a);
	Procesor dupa;
	dupa.add(a);
}

void Process_List::CP_2(vector<string>v)
{
	Process a(v[0], stoi(v[1]));
	Process_List::PrcList.push_back(a);
	Procesor dupa;
	dupa.add(a);
}

void Process_List::createProcess(vector<string>v)
{
	if (v.size() == 1)
	{
		CP_1(v);
	}
	else
	{
		CP_2(v);
	}
}

list<Process> Process_List::getReady()
{
	list<Process>mylist;
	mylist = PrcList;
	return mylist;
}

void Process_List::setStatus(vector<string>v)
{
	status st;
	if (v[1] == "AKTYWNY")
	{
		st = AKTYWNY;
	}
	else if (v[1] == "GOTOWY")
	{
		st == GOTOWY;
	}
	else if (v[1] == "OCZEKUJACY")
	{
		st == OCZEKUJACY;
	}
	else if (v[1] == "ZAKONCZONY")
	{
		st == ZAKONCZONY;
	}
	Process a(v[0]);
	for (it = PrcList.begin(); it != PrcList.end(); ++it)
	{
		if (a.process_name == it->process_name)
		{
			it->setProcessStatus(st);
		}
	}
}

void Process_List::setPriority(vector<string>v)
{
	Process a(v[0]);
	for (it = PrcList.begin(); it != PrcList.end(); ++it)
	{
		if (a.process_name == it->process_name)
		{
			it->setPriority(stoi(v[1]));
		}
	}
}

void Process_List::terminateProcess(vector<string>v)
{
	Process a(v[0]);
	for (it = PrcList.begin(); it != PrcList.end(); ++it)
	{
		if (a.process_name == it->process_name)
		{
			PrcList.remove(*it);
			break;
		}
	}
}


void Process_List::removeProcess()
{
	Process a;
	a.setProcessStatus(ZAKONCZONY);
	for (it = PrcList.begin(); it != PrcList.end(); ++it)
	{
		if (a.process_status == it->process_status)
		{
			PrcList.remove(*it);
			break;
		}
	}
}


void Process_List::findAndDisplayProcess(vector<string>v)
{
	Process a(v[0]);
	bool dlaczemu = false;
	for (it = PrcList.begin(); it != PrcList.end(); ++it)
	{
		if (a.process_name == it->process_name)
		{
			it->display();
			dlaczemu = true;
		}
	}
	if (dlaczemu != true)
	{
		cout << "Proces o podanej nazwie nie istnieje.";
	}
}

void Process_List::displayAll()
{
	if (PrcList.size() != 0) {
		for (it = PrcList.begin(); it != PrcList.end(); ++it)
		{
			it->displayHelper();
		}
	}
	else
	{
		cout << "Brak procesow do wyswietlenia." << endl;
	}
}