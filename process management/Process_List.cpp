#include <iostream>
#include "Process_List.hpp"
using namespace std;

void Process_List::createProcess(string na)
{
	Process a(na);
	Process_List::PrcList.push_front(a);
	procesor.add(a);
}

void Process_List::createProcess(string na, int pr)
{
	Process a(na, pr);
	Process_List::PrcList.push_front(a);
	procesor.add(a);
}

list<Process> Process_List::getReady()
{
	list<Process>mylist;
	for (auto const& it : Process_List::PrcList)
	{
		if (it.process_status == GOTOWY)
		{
			mylist.push_front(it);
		}
	}
	return mylist;
}

void Process_List::terminateProcess(string s)
{
	for (auto const& it : Process_List::PrcList)
	{
		if (it.process_name == s)
		{
			Process_List::PrcList.remove(it);
		}
	}
}

void Process_List::removeProcess() 
{
	for (auto const& it : Process_List::PrcList)
	{
		if (it.process_status == ZAKONCZONY)
		{
			Process_List::PrcList.remove(it);
		}
	}
}

void Process_List::findAndDisplayProcess(string s)
{
	bool czy = false;
	for (auto const& it : Process_List::PrcList)
	{
		if (it.process_name == s)
		{
			//it.display();
			czy = true;
		}
	}
	if (czy == false)
	{
		cout << "Proces o podanej nazwie nie istnieje.";
	}
}

void Process_List::displayAll()
{
	for (auto const& it : Process_List::PrcList)
	{
		//it.displayHelper();
	}
}

Process_List::Process_List()
{
	//this->proc = Procesor(this);
}

Process_List::Process_List(const Process_List & plist)
{
	this->PrcList = plist.PrcList;
	this->proc = plist.proc;
}

