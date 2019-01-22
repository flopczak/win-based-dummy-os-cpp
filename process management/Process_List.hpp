#pragma once
#include "Process.hpp"
#include <list>
using namespace std;

class Process_List
{
public:
	Process_List();
	list<Process>PrcList;
	std::list<Process>::iterator it;
	list<Process> getReady();
	void createProcess(string na);
	void createProcess(string na, int pr);
	void setStatus(string na, status);
	void setPriority(string na, int n);
	void terminateProcess(string s);
	void removeProcess();
	void findAndDisplayProcess(string s);
	void displayAll();
};