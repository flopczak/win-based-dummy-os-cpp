#include "Process.hpp"
#include "Process_List.hpp"
#include <string>
#include <iostream>

using namespace std;

Process::Process()
{
	this->PID = 0;
	this->process_name = "";
	this->process_status = GOTOWY;
	this->process_priority = 0;
	this->AX = 0;
	this->BX = 0;
	this->CX = 0;
	this->errorCode = 0;
	this->PobWielTabStronic();
}

Process::Process(string na)
{
	this->PID = rand() % 9999 + 1000;
	this->process_name = na;
	this->process_status = GOTOWY;
	this->process_priority = 0;
	this->AX = 0;
	this->BX = 0;
	this->CX = 0;
	this->errorCode = 0;
	this->PobWielTabStronic();
}

Process::Process(string na, int pr)
{
	this->PID = rand() % 9999 + 1000;
	this->process_name = na;
	this->process_status = GOTOWY;
	this->process_priority = pr;
	this->AX = 0;
	this->BX = 0;
	this->CX = 0;
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

void Process::setProcessStatus(status a)
{
	this->process_status = a;
}

void Process::display()
{
	cout << "Nazwa procesu: " << this->process_name << endl;
	cout << "PID: " << this->PID << endl;
	cout << "Status procesu: " << this->process_status << endl;
	cout << "Priorytet: " << this->process_priority << endl;
	cout << "AX: " << this->AX << endl;
	cout << "BX: " << this->BX << endl;
	cout << "CX: " << this->CX << endl;
}

void Process::displayHelper()
{
	cout << "Nazwa procesu: " << this->process_name << endl;
	cout << "PID: " << this->PID << endl;
	cout << "Status procesu: " << this->process_status << endl;
	cout << "Priorytet: " << this->process_priority << endl;
}

int Process::getPID()
{
	return this->PID;
}

string Process::getName()
{
	return this->process_name;
}

bool operator==(const Process& b, const Process& a)
{
	if (a.process_name == b.process_name)
	{
		return true;
	}
	else return false;
}


//---------------------------------------------------------------------//

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



