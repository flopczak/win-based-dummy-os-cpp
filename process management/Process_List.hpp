#pragma once
#include "Process.hpp"
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
};