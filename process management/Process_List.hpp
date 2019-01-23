#pragma once
#include "Process.hpp"
#include "../processor/Procesor.hpp"
#include <vector>
#include <list>
using namespace std;

class Process_List
{
public:
	Process_List();
	static list<Process>PrcList;
	list<Process>::iterator it;
	list<Process> getReady();
	Process CP_1(vector<string>v);
	Process CP_2(vector<string>v);
	void createProcess(vector<string>v);
	void setStatus(vector<string>v);
	void setPriority(vector<string>v);
	void terminateProcess(vector<string>v);
	void removeProcess(Process a);
	void findAndDisplayProcess(vector<string>v);
	void displayAll();
};