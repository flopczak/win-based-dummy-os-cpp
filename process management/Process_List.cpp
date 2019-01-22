#include "Process_List.hpp"
#include "Process.hpp"
#include <iostream>
using namespace std;

Process_List::Process_List()
{

}

void Process_List::createProcess(string na)
{
	Process a(na);
	Process_List::PrcList.push_front(a);

}

void Process_List::createProcess(string na, int pr)
{
	Process a(na, pr);
	Process_List::PrcList.push_back(a);

}

list<Process> Process_List::getReady()
{
	list<Process>mylist;
	mylist = PrcList;
	return mylist;
}

void Process_List::setStatus(string na, status b)
{
	Process a(na);
	for (it = PrcList.begin(); it != PrcList.end(); ++it)
	{
		if (a.process_name == it->process_name)
		{
			it->setProcessStatus(b);
		}
	}
}

void Process_List::setPriority(string na, int n)
{
	Process a(na);
	for (it = PrcList.begin(); it != PrcList.end(); ++it)
	{
		if (a.process_name == it->process_name)
		{
			it->setPriority(n);
		}
	}
}

void Process_List::terminateProcess(string s)
{
	Process a(s);
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
		if (a.process_name == it->process_name)
		{
			PrcList.remove(*it);
			break;
		}
	}
}


void Process_List::findAndDisplayProcess(string s)
{
	Process a(s);
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

