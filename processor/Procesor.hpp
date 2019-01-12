#pragma once
#include"../process management/Process.hpp"
#include<map>
#include<array>
#include<queue>
#include<list>
#include<vector>
bool debug = true;

class Procesor
{
public:
	Procesor();
	~Procesor();
	void add(Process &ready); // metoda do dodawania proces�w



	std::map<int, std::list<Process>> main_queue; //kolejka proces�w w stanie gotowo�ci da�em vec bez wskaznika czy to zle?
	std::array<bool, 8> mask; //maska bitowa na kolejk�
	
private:
	void find_and_run(Procesor&p);
	void age(Procesor& p);

};

