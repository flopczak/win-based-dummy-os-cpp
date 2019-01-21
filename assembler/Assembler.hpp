#pragma once


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
	void run(Process &pcb);

	Assembler();
};

