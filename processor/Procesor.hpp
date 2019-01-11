#pragma once
#include"../process management/Process.hpp"
#include<map>
#include<array>
#include<queue>

bool debug = true;

class Procesor
{
public:
	Procesor();
	~Procesor();
	void add(Process &ready); // metoda do dodawania procesów



	std::map<int, std::queue<Process*>> main_queue; //kolejka procesów w stanie gotowoœci
	std::array<bool, 8> mask; //maska bitowa na kolejkê
	
private:
	void find_and_run();
	void remove();
	void age();

};

