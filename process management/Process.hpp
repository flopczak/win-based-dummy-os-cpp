#pragma once
#include "Process_List.hpp"
#include <string>
using namespace std;

enum status {NOWY, AKTYWNY, GOTOWY, OCZEKUJACY, ZAKONCZONY};

class Process	//PCB
{
public:
	string process_name;				//nazwa procesu

private:
	static int PID;						//indywidualny identyifkator
	string process_status;				//status procesu: nowy, aktywny, gotowy, oczekuj¹cy, zakoñczony
	int program_instructions;			//instrukcje asemblerowskie
	int AX;								//rejestry
	int BX;
	int CX;
	int process_priority;				//priorytet
	
	
	Process();							//konstruktor domyœlny
	Process(string n, int p, int i);	//konstruktor
	~Process();							//dekonstruktor
	void setInstructions(int in);		//przekazywanie instrukcji asemblera do procesu
	void setProcessStatus(string st);	//ustawianie statusu procesu
	void displayProcess();
	void addProcess(Process a);
};