#pragma once
#include <list>
#include <string>
using namespace std;

enum status { AKTYWNY, GOTOWY, OCZEKUJACY, ZAKONCZONY };

struct STRON
{
	int RamaZajeta;
	bool wPam;
};

class Process											//PCB
{
public:
	STRON* pageTable;									//Przemkowe RAM'y
	//JACOB zmieniam parametry na publiczne
	//STRON* pageTable;	//Przemkowe RAM'y
	int pageTableSize;

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

	Process();											//konstruktor domyslny
	Process(string n);									//konstruktor z nazwa procesu
	Process(string n, int p);							//konstruktor z nazwa i priorytetem procesu
	~Process();											//dekonstruktor
	void setProcessStatus(status a);					//ustawianie statusu procesu
	void setPriority(int n);							//ustawianie priorytetu
	void display();										//wyswietlanie szczegoowe jednego procesu
	void displayHelper();								//funkcja pomocnicza dla funckcji displayAll()
	int getPID();
	string getName();
	friend bool operator==(const Process &b, const Process &a);


	void UstTabStronic(STRON* newpageTable);			//Przemkowe RAM'y
	int errorCode;
	STRON* PobTabStronic();
	void UstWielTabStronic(int num);
	int PobWielTabStronic();
};