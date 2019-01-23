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
private:
	Memory *m;
	Disk *d;
	Process_List *pl;

	int PID;
	int regAX;
	int regBX;
	int regCX;
	int PC;
public:


	Assembler(Process_List *pl, Memory *m, Disk *d);
	~Assembler();
	void getRegistersState(Process &pcb);
	void saveRegisters(Process &pcb);
	void printRegisters();
	int get_register(std::string reg);
	void set_register(std::string reg, int value);
	void run(Process &pcb);
	std::string getOrder(Process &pcb);
	void error(Process &p);
};

