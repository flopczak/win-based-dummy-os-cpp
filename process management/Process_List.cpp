#include "../processor/Procesor.hpp"
#include "Process_List.hpp"
#include "Process.hpp"
#include "../processor/Procesor.hpp"
#include <iostream>

using namespace std;

map<int, Process*>Process_List::PCBList = {};

Process_List::Process_List()
{
	this->mem = new Memory();
	this->disk = new Disk();
	this->assembler = new Assembler(this, this->mem, this->disk);
}

void Process_List::createProcess(string name, string instr, int pr)
{
	int pid = rand() & 9999 * 1000;
	//dodac instr do pamieci w miejscu pid
	Process p = Process(pid, name, pr, 0, this->mem, instr.size());
	PCBList.insert(pair<int, Process*>(pid, &p));
	//dodanie tego procesu do listy gotowych procesow w procesorze
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
		st = GOTOWY;
	}
	else if (v[1] == "OCZEKUJACY")
	{
		st = OCZEKUJACY;
	}
	else if (v[1] == "ZAKONCZONY")
	{
		st = ZAKONCZONY;
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

void Process_List::removeProcess(Process a)
{
	
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