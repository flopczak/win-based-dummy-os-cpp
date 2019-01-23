#pragma once
#include"../process management/Process.hpp"
#include"../process management/Process_List.hpp"
#include "../processor/Procesor.hpp"
#include "../memory/Memory.hpp"
#include "../file/Disk.hpp"
#include<map>
#include<array>
#include<queue>
#include<list>
#include<vector>

extern class Assembler;

class Procesor
{
private:
	Assembler *a;
	Memory *m;
	Disk *d;

public:
	bool work = true;
	bool new_process = false;
	int w_counter;
	
	Procesor(Assembler *a, Memory *m, Disk *d);


	Process DUMMY = Process("DUMMY", 0);
	Process running; // wkladasz to do run od konrada aby wykonac rozkaz asemblera
					 //Process_List* temporary = new Process_List();
	list<Process> temporary;
	~Procesor();
	void add(Process&ready); // metoda do dodawania proces�w
	void check(Process &ready);
	void Procesor::find();

	void displayMap();

	Process * prtrunning = new Process(running);

	void priority_inc(); //metoda inkrementująca priorytety kazdego gotowego procesu

	void run();
	static std::map<int, std::list<Process>> main_queue; //kolejka proces�w w stanie gotowo�ci da�em vec bez wskaznika czy to zle?
	static std::array<bool, 8> mask; //maska bitowa na kolejk�
	void ramka();
	list<Process> synchro(list<Process>& s);
	void age(Process& p);

};

