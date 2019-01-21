#pragma once
#include "Process.hpp"
#include "../processor/Procesor.hpp"
#include <deque>
#include <list>
using namespace std;

class Process_List
{
public:
	static list<Process>PrcList;
	Procesor procesor = new Procesor(this);
	list<Process> getReady();
	void terminateProcess(string s);
	void removeProcess();
	void createProcess(string na);
	void createProcess(string na, int pr);
	void findAndDisplayProcess(string s);
	void displayAll();
};