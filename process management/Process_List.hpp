#pragma once
#ifndef PCBList_H
#define PCBList_H
#include "Process.hpp"
#include "../memory/Memory.hpp"
#include "../assembler/Assembler.hpp"
#include "../processor/Procesor.hpp"
#include "../file/Disk.hpp"
#include <vector>
#include <map>
using namespace std;

class Process_List 
{
private:
	Memory *mem;
	Assembler *assembler;
	Disk *disk;
public:
	Process_List();
	static map<int, Process*>PCBList;

	void createProcess(string name, string instr, int pr);
	void terminateProcess(vector<string>v);
	void removeProcess(Process a);
	void findAndDisplayProcess(vector<string>v);
	void displayAll();
};

#endif