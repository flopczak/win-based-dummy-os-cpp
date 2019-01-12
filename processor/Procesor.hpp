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
	void add(Process &ready); // metoda do dodawania procesów



	std::map<int, std::list<Process>> main_queue; //kolejka procesów w stanie gotowoœci da³em vec bez wskaznika czy to zle?
	std::array<bool, 8> mask; //maska bitowa na kolejkê
	
private:
	void find_and_run(Procesor&p);
	void age(Procesor& p);

};

