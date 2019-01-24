#pragma once
#ifndef PCBList_H
#define PCBList_H
#include "Process.hpp"
#include "../memory/Memory.hpp"

#include "../processor/Procesor.hpp"
#include "../file/Disk.hpp"
#include "../assembler/Assembler.hpp"
#include <vector>
#include <map>
using namespace std;

class Process_List 
{
private:
	Memory *mem;
	Disk *disk;
	Assembler *assembler;
	static map<int, Process*>PCBList;
public:
	Process_List();
	void createProcess(const string &name, const string &instr, const int &pr);
	void terminateProcess(vector<string>v);
	void removeProcess(Process a);
	void findAndDisplayProcess(vector<string>v);
	void displayAll();
};

#endif