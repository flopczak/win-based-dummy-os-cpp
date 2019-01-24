#include "Process.hpp"
#include <string>
#include <iostream>

using namespace std;

Process::Process(int pid, string na, int priority, int cc,  Memory * m, int inst_size)
{
	this->PID = rand() % 9999 + 1000;
	this->process_name = na;
	this->process_status = GOTOWY;
	this->program_instructions = inst_size;
	this->command_counter = cc;
	this->process_priority = priority;
	this->AX = 0;
	this->BX = 0;
	this->CX = 0;
	this->mmr = m;
}

Process::~Process()
{
}

//settery
void Process::setPriority(int n)
{
	this->process_priority = n;
}

void Process::setStatus(status a)
{
	this->process_status = a;
}

//gettery
int Process::getPID()
{
	return this->PID;
}

string Process::getName()
{
	return this->process_name;
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

bool operator==(const Process& b, const Process& a)
{
	if (a.process_name == b.process_name)
	{
		return true;
	}
	else return false;
}


//---------------------------------------------------------------------//




