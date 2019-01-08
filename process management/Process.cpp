#include "Process.hpp"
#include "Process_List.hpp"
#include <string>
#include <iostream>

using namespace std;

Process::Process()
{
	this->PID = 0;
	this->process_name = "";
	this->process_status = NOWY;
	this->process_priority = 0;
	this->program_instructions = 0;
	this->AX = 0;
	this->BX = 0;
	this->CX = 0;
}

Process::Process(string na, int pr, int in)
{
	this->PID = rand() % 9999 + 1000;
	this->process_name = na;
	this->process_status = NOWY;
	this->process_priority = pr;
	this->program_instructions = in;
	this->AX = 0;
	this->BX = 0;
	this->CX = 0;
}

Process::Process()
{
	this->errorCode = 0;
	this->PobWielTabStronic();
}

Process::~Process()
{
}

void Process::setPriority(int n)
{
	this->process_priority = n;
}

void Process::setInstructions(int in)
{
	this->program_instructions = in;
}

void Process::setProcessStatus(string st)
{
	this->process_status = st;
}

void Process::display() 
{
	cout << "PID: " << this->PID << endl;
	cout << "Nazwa procesu: " << this->process_name << endl;
	cout << "Status procesu: " << this->process_status << endl;
	cout << "Priorytet: " << this->process_priority << endl;
}

void Process::findAndDisplayProcess(string s) 
{
	bool czy = false;
	for (int i = 0; i < Process_List::PrcList.size(); i++)
	{
		//if (s == Process_List::PrcList[i].process_name)
		{
			//Process_List::PrcList[i].display();
			czy = true;
		}
	}
	if (czy == false)
	{
		cout << "Proces o podanej nazwie nie istnieje.";
	}
}

void Process::addProcess(Process a) 
{
	Process_List::PrcList.push_front(a);
}

void Process::UstTabStronic(STRON* newpageTable)
{
	this->pageTable = newpageTable;
}

STRON* Process::PobTabStronic()
{
	return this->pageTable;
}

void Process::UstWielTabStronic(int num)
{
	this->pageTableSize = num;
}

int Process::PobWielTabStronic()
{
	return this->pageTableSize;
}


