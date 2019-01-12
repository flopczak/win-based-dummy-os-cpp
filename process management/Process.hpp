#pragma once
#include "Process_List.hpp"
#include <string>
using namespace std;

enum status {NOWY, AKTYWNY, GOTOWY, OCZEKUJACY, ZAKONCZONY};

struct STRON
{
	int RamZajety;
	bool wPam;
};

class Process											//PCB
{
public:
	
	STRON* pageTable;									//Przemkowe RAM'y
//JACOB zmieniam parametry na publiczne
	STRON* pageTable;	//Przemkowe RAM'y
	int pageTableSize;

	string process_name;								//nazwa procesu
	static int PID;										//indywidualny identyifkator
	status process_status;								//status procesu: nowy, aktywny, gotowy, oczekuj�cy, zako�czony
	int program_instructions;							//instrukcje asemblerowskie
	int command_counter;								//licznik rozkaz�w asemblera
	int AX;												//rejestry
	int BX;
	int CX;
	int process_priority;								//priorytet
	bool PP;											//flaga obecno�ci procesora
	

	
	Process();											//konstruktor domy�lny
	Process(string n);									//konstruktor z nazw� procesu
	Process(string n, int p);							//konstruktor z nazw� i priorytetem procesu
	~Process();											//dekonstruktor
	void setInstructions(int in);						//przekazywanie instrukcji asemblera do procesu
	void setProcessStatus(status);						//ustawianie statusu procesu
	void setPriority(int n);							//ustawianie priorytetu
	void display();										//wy�wietlanie szczeg�owe jednego procesu
	void displayAll();									//wy�wietlanie wszystkich procesow
	void displayHelper();								//funkcja pomocnicza dla funckcji displayAll()
	void findAndDisplayProcess(string s);				//szukanie procesu po nazwie w kolejce i wy�wietlanie
	void addProcess(Process a);							//dodawanie procesu do kolejki
	void removeProcess();								//usuwanie zakonczonego procesu
	void terminateProcess(string s);					//ko�czenie procesu przez u�ytkownika

	
	void UstTabStronic(STRON* newpageTable);			//Przemkowe RAM'y
	int errorCode;
	STRON* PobTabStronic();
	void UstWielTabStronic(int num);
	int PobWielTabStronic();
};