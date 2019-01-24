#pragma once
#ifndef PCB_H
#define PCB_H
#include <list>
#include <string>
#include "../memory/Memory.hpp"
using namespace std;

enum status { AKTYWNY, GOTOWY, OCZEKUJACY, ZAKONCZONY };

class Process											//PCB
{
private:

	string process_name;								//nazwa procesu
	int PID;											//indywidualny identyifkator
	status process_status;								//status procesu: nowy, aktywny, gotowy, oczekuj�cy, zako�czony
	int program_instructions;							//instrukcje asemblerowskie
	int command_counter;								//licznik rozkazow asemblera
	int AX;												//rejestry
	int BX;
	int CX;
	int process_priority;								//priorytet
	bool PP;											//flaga obecno�ci procesora
	Memory *mmr;
public:
	Process(int pid, string na, int priority, int cc, Memory * m, int inst_size);
	~Process();											//dekonstruktor

	//settery
	void setStatus(status a);							//ustawianie statusu procesu
	void setPriority(int n);							//ustawianie priorytetu

	//gettery
	int getPID();
	string getName();

	void display();										//wyswietlanie szczegoowe jednego procesu
	void displayHelper();								//funkcja pomocnicza dla funckcji displayAll()
	
	friend bool operator==(const Process &b, const Process &a);
};
#endif