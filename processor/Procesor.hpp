#pragma once
#include"Process.hpp"
#include"Process_List.hpp"

#include<map>
#include<array>
#include<queue>
#include<list>
#include<vector>



class Procesor
{
public:
	bool work = true;
	bool new_process = false;
	int w_counter;
	Process DUMMY = Process("DUMMY", 0);
	Process running; // wkladasz to do run od konrada aby wykonac rozkaz asemblera
					 //Process_List* temporary = new Process_List();
	list<Process> temporary;
	Procesor(); //Procesor(Process_List* p);
	~Procesor();
	void add(); // metoda do dodawania proces�w
	void check(Process &ready);
	void Procesor::find();

	void displayMap();


	void priority_inc(); //metoda inkrementująca priorytety kazdego gotowego procesu

	void run();
	std::map<int, std::list<Process>> main_queue; //kolejka proces�w w stanie gotowo�ci da�em vec bez wskaznika czy to zle?
	std::array<bool, 8> mask; //maska bitowa na kolejk�


	void age(Process& p);

};

