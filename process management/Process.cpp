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


Process::~Process()
{
}

void Process::setInstructions(int in)
{
	this->program_instructions = in;
}

void Process::setProcessStatus(string st)
{
	this->process_status = st;
}

void Process::displayProcess() 
{
	cout << "PID: " << this->PID << endl;
	cout << "Nazwa procesu: " << this->process_name << endl;
	cout << "Status procesu: " << this->process_status << endl;
	cout << "Priorytet: " << this->process_priority << endl;
}

void Process::addProcess(Process a) 
{
	//Process_List
}

