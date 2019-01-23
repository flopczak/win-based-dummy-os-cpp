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
	list<Process>PrcList;
	std::list<Process>::iterator it;
	list<Process> getReady();
	void CP_1(vector<string>v);
	void CP_2(vector<string>v);
	void createProcess(vector<string>v);
	void setStatus(vector<string>v);
	void setPriority(vector<string>v);
	void terminateProcess(vector<string>v);
	void removeProcess();
	void findAndDisplayProcess(vector<string>v);
	void displayAll();
};