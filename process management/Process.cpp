#include "Process.hpp"
#include <string>
#include <iostream>

using namespace std;

Process::Process()
{
	//this->PID = 0;
	this->process_name = "";
	this->process_status = NOWY;
	this->process_priority = 0;
	this->program_instructions = 0;
	this->command_counter = 0;
	this->AX = 0;
	this->BX = 0;
	this->CX = 0;
	this->PP = false;
}

Process::Process(string na)
{
	//	this->PID = rand() % 9999 + 1000;
	this->process_name = na;
	this->process_status = NOWY;
	this->process_priority = 5;
	this->program_instructions = 0;
	this->command_counter = 0;
	this->AX = 0;
	this->BX = 0;
	this->CX = 0;
	this->PP = false;
}

Process::Process(string na, int pr)
{
	//this->PID = rand() % 9999 + 1000;
	this->process_name = na;
	this->process_status = NOWY;
	this->process_priority = pr;
	this->program_instructions = 0;
	this->command_counter = 0;
	this->AX = 0;
	this->BX = 0;
	this->CX = 0;
	this->PP = false;
}

Process::~Process()
{
}

void Process::display()
{
	//cout << "PID: " << this->PID << endl;
	cout << "Nazwa procesu: " << this->process_name << endl;
	cout << "Status procesu: " << this->process_status << endl;
	cout << "Priorytet: " << this->process_priority << endl;
	cout << "AX: " << this->AX << endl;
	cout << "BX: " << this->BX << endl;
	cout << "CX: " << this->CX << endl;
}

/*
Process::Process()
{
this->errorCode = 0;
this->PobWielTabStronic();
}



void Process::setPriority(int n)		//to chyba jest niepotrzebne XD
{
this->process_priority = n;
}

void Process::setInstructions(int in)
{
this->program_instructions = in;
}

void Process::setProcessStatus(status)
{
this->process_status = NOWY, AKTYWNY, GOTOWY, OCZEKUJACY, ZAKONCZONY;
}



void Process::findAndDisplayProcess(string s)
{
bool czy = false;
for (auto it : Process_List::PrcList)
{
if (it.process_name == s)
{
it.display();
czy = true;
}
}
if (czy == false)
{
cout << "Proces o podanej nazwie nie istnieje.";
}
}

void Process::displayHelper()
{
cout << "PID: " << this->PID << endl;
cout << "Nazwa procesu: " << this->process_name << endl;
cout << "Status procesu: " << this->process_status << endl;
cout << "Priorytet: " << this->process_priority << endl;
}

void Process::displayAll()
{
for (auto it : Process_List::PrcList)
{
it.displayHelper();
cout << endl;
}
}

void Process::addProcess(Process a)
{
Process_List::PrcList.push_front(a);
}

void Process::removeProcess()
{
for (auto it : Process_List::PrcList)
{
if (it.process_status == ZAKONCZONY)
{
Process_List::PrcList.remove(it);
}
}
}

void Process::terminateProcess(string s)
{
for (auto it : Process_List::PrcList)
{
if (it.process_name == s)
{
Process_List::PrcList.remove(it);
}
}
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

*/
