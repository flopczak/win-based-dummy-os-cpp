#pragma once
#include "../process management/Process.hpp"
#include "../process management/Process_List.hpp"
#include "../memory/Memory.hpp"
#include "../processor/Procesor.hpp"
#include "../FileAccess/FileAccess.hpp"
#include "../file/Files.hpp"
#include "../sync/Sync.hpp"
#include "../file/Disk.hpp"


class Assembler{
public:
	int PID;
	int regAX;
	int regBX;
	int regCX;
	int PC;

	void getRegistersState(Process &pcb);
	void saveRegisters(Process &pcb);
	void printRegisters();
	int get_register(std::string reg);
	void set_register(std::string reg, int value);
	void run(Process &pcb, Memory &m, Disk &disk);
	std::string getOrder(Memory &m, Process &pcb);
	Assembler();
};

