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
	void add(Process &ready); // metoda do dodawania proces�w



	std::map<int, std::queue<Process*>> main_queue; //kolejka proces�w w stanie gotowo�ci
	std::array<bool, 8> mask; //maska bitowa na kolejk�
	
private:
	void find_and_run();
	void remove();
	void age();

};

