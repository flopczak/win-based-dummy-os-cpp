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
	list<Process> getReady();
	void terminateProcess(string s);
	void removeProcess();
	void createProcess(string na);
	void createProcess(string na, int pr);
	void findAndDisplayProcess(string s);
	void displayAll();
	Process_List();
	Process_List(const Process_List &plist);

private: 
	Procesor proc = Procesor(this);
};