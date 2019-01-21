#pragma once
#include"../process management/Process.hpp"
#include"../process management/Process_List.hpp"
#include<map>
#include<array>
#include<queue>
#include<list>
#include<vector>
bool debug = true;


class Procesor
{
public:
	bool work = true;
	bool new_process = false;
	int w_counter;
	Process running;
	Process_List temporary;
	Procesor(Process_List* p);
	~Procesor();
	void add(Process& ready); // metoda do dodawania proces�w
	void check(Process &ready);
	int Procesor::find(Procesor&p);

	void run(Procesor&p);
	std::map<int, std::list<Process>> main_queue; //kolejka proces�w w stanie gotowo�ci da�em vec bez wskaznika czy to zle?
	std::array<bool, 8> mask; //maska bitowa na kolejk�


	void age(Process& p);

};

