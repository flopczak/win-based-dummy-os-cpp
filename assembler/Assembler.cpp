#include "Assembler.hpp"
#include <iostream>
#include <regex>


/*
//Operacje arytmetyczne//
AD - dodawanie
SB - odejmowanie
MP - mno�enie
DV - dzielenie
MV - przenoszenie wartoci
IC - zwi�kszenie wartosci rejestru o 1
DC - zmniejszenie wartosci rejestru o 1

JP - skok bezwarunkowy
JZ - skok przy zerowej warto�ci
HL - koniec programu

//Operacje na plikach//
CR file_name - utworzenie pliku o podanej nazwie
WF file_name content - zapisuje zawarto�� do pliku
AF file_name content - dopisuje zawarto�� do pliku
RF file_name - odczyt z pliku
DF file_name - usuwa plik

LC file_name - tworzy i zamyka zamek powi�zany z nazw� pliku
UL file_name - otwiera zamek

//Operacje na procesach//
CP name file_name priority - tworzy proces
DP name - usuwa proces


*/

Assembler::Assembler(const Process_List *pl, Memory *m, Disk *d) {
	this->pl = pl;
	this->m = m;
	this->d = d;
	PID = 0;
	regAX = 0;
	regBX = 0;
	regCX = 0;
	PC = 0;
}
Assembler::~Assembler() {}

void Assembler::getRegistersState(Process &pcb) {
	PID = pcb.PID;
	regAX = pcb.AX;
	regBX = pcb.BX;
	regCX = pcb.CX;
	PC = pcb.command_counter;
}

void Assembler::saveRegisters(Process &pcb) {
	pcb.PID = PID;
	pcb.AX = regAX;
	pcb.BX = regBX;
	pcb.CX = regCX;
	pcb.command_counter = PC;
}

void Assembler::printRegisters() {
	std::cout << "PID: " << PID << std::endl;
	std::cout << "AX: " << regAX << std::endl;
	std::cout << "BX: " << regBX << std::endl;
	std::cout << "CX: " << regCX << std::endl;
	std::cout << "Program counter: " << PC << std::endl;
}

void Assembler::set_register(std::string reg, int value) {
	if (reg == "AX") {
		regAX = value;
	}

	if (reg == "BX") {
		regBX = value;
	}

	if (reg == "CX") {
		regCX = value;
	}

	if (reg == "PC") {
		PC = value;
	}
}


int Assembler::get_register(std::string reg) {
	if (reg == "AX") {
		return regAX;
	}

	if (reg == "BX") {
		return regBX;
	}

	if (reg == "CX") {
		return regCX;
	}
	if (reg == "PC") {
		return PC;
	}
}

std::string Assembler::getOrder(Process &pcb) {
	std::string order;
	order = m->odczytajString(&pcb,PC);
	PC += order.size() + 1;
	return order;
}

void Assembler::error(Process &pcb) {
	std::cout << "Blad parsowania. Proces " << pcb.getPID() << " zostal zatrzymany!" << std::endl;
	pcb.setProcessStatus(ZAKONCZONY);
	return;
}

std::map<std::string, Sync>Sync::zamkiNaPlikach;

void Assembler::run(Process &pcb) {
	
	getRegistersState(pcb);

	std::string order;
	order.clear();
	order = getOrder(pcb);
	std::string arg1, arg2, arg3;
	int value = 0;

	if (order == "AD") {
		arg1 = getOrder(pcb);
		arg2 = getOrder(pcb);
		
		std::cout << "Order: " << order << " " << arg1 << " " << arg2 << std::endl;
		std::regex wzorzec("[0-9]*");

		if ((arg1 == "AX" || arg1 == "BX" || arg1 == "CX") && std::regex_match(arg2, wzorzec)) {
			value = stoi(arg2);
			set_register(arg1, get_register(arg1) + value);
		}

		else if ((arg1 == "AX" || arg1 == "BX" || arg1 == "CX") && (arg2 == "AX" || arg2 == "BX" || arg2 == "CX")) {
			set_register(arg1, get_register(arg1) + get_register(arg2));
		}


		printRegisters();
		saveRegisters(pcb);
	}

	else if (order == "SB") {
		arg1 = getOrder(pcb);
		arg2 = getOrder(pcb);
		std::cout << "Order: " << order << " " << arg1 << " " << arg2 << std::endl;

		std::regex wzorzec("[0-9]*");

		if ((arg1 == "AX" || arg1 == "BX" || arg1 == "CX") && std::regex_match(arg2, wzorzec)) {
			value = stoi(arg2);
			set_register(arg1, get_register(arg1) - value);
		}

		else if ((arg1 == "AX" || arg1 == "BX" || arg1 == "CX") && (arg2 == "AX" || arg2 == "BX" || arg2 == "CX")) {
			set_register(arg1, get_register(arg1) - get_register(arg2));
		}

		printRegisters();
		saveRegisters(pcb);
	}

	else if (order == "MP") {
		arg1 = getOrder(pcb);
		arg2 = getOrder(pcb);
		std::cout << "Order: " << order << " " << arg1 << " " << arg2 << std::endl;

		std::regex wzorzec("[0-9]*");

		if ((arg1 == "AX" || arg1 == "BX" || arg1 == "CX") && std::regex_match(arg2, wzorzec)) {
			value = stoi(arg2);
			set_register(arg1, get_register(arg1) * value);
		}

		else if ((arg1 == "AX" || arg1 == "BX" || arg1 == "CX") && (arg2 == "AX" || arg2 == "BX" || arg2 == "CX")) {
			set_register(arg1, get_register(arg1) * get_register(arg2));
		}

		printRegisters();
		saveRegisters(pcb);
	}

	else if (order == "DV") {
		arg1 = getOrder(pcb);
		arg2 = getOrder(pcb);
		std::cout << "Order: " << order << " " << arg1 << " " << arg2 << std::endl;

		std::regex wzorzec("[0-9]*");

		if ((arg1 == "AX" || arg1 == "BX" || arg1 == "CX") && std::regex_match(arg2, wzorzec)) {
			value = stoi(arg2);
			if (value != 0) {
				set_register(arg1, get_register(arg1) / value);
			}

			else {
				std::cout << "Nie mozna dzielic przez 0." << std::endl;
			}
		}

		else if ((arg1 == "AX" || arg1 == "BX" || arg1 == "CX") && (arg2 == "AX" || arg2 == "BX" || arg2 == "CX")) {
			if (get_register(arg2) != 0) {
				set_register(arg1, get_register(arg1) / get_register(arg2));
			}

			else {
				std::cout << "Nie mozna dzielic przez zero." << std::endl;
			}
		}

		printRegisters();
		saveRegisters(pcb);
	}

	else if (order == "MV") {
		arg1 = getOrder(pcb);
		arg2 = getOrder(pcb);
		std::cout << "Order: " << order << " " << arg1 << " " << arg2 << std::endl;

		std::regex wzorzec("[0-9]*");

		if ((arg1 == "AX" || arg1 == "BX" || arg1 == "CX") && std::regex_match(arg2, wzorzec)) {
			value = stoi(arg2);
			set_register(arg1, value);
		}

		else if ((arg1 == "AX" || arg1 == "BX" || arg1 == "CX") && (arg2 == "AX" || arg2 == "BX" || arg2 == "CX")) {
			set_register(arg1, get_register(arg2));
		}

		printRegisters();
		saveRegisters(pcb);
	}

	else if (order == "IC") {
		arg1 = getOrder(pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;

		if (arg1 == "AX" || arg1 == "BX" || arg1 == "CX") {
			set_register(arg1, get_register(arg1) + 1);
		}

		printRegisters();
		saveRegisters(pcb);
	}

	else if (order == "DC") {
		arg1 = getOrder(pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;

		if (arg1 == "AX" || arg1 == "BX" || arg1 == "CX") {
			set_register(arg1, get_register(arg1) - 1);
		}

		printRegisters();
		saveRegisters(pcb);
	}

	else if (order == "LC") {
		arg1 = getOrder(pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;

		Sync::lockFile(arg1, &pcb);
	}

	else if (order == "UL") {
		arg1 = getOrder(pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;
		Sync::unlockFile(arg1, &pcb);
	}

	else if (order == "CR") {
		arg1 = getOrder(pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;
		////////
		d->dodajpPlik(arg1);
		saveRegisters(pcb);
		
	}

	else if (order == "WF") {
		arg1 = getOrder(pcb);
		arg2 = getOrder(pcb);
		std::regex wzorzec("\".*\"");
		std::cout << "Order: " << order << " " << arg1 << " " << arg2 << std::endl;
		if (std::regex_match(arg2, wzorzec)) {
			arg2.erase(arg2.begin());
			arg2.erase(arg2.end() - 1);
		}
		if (d->czyMozna(arg1)) {
			if (d->open(arg1)) {
				d->nadpiszPlik(arg1, arg2);
				d->close(arg1);
			}
			else {
				std::cout << "Nie mozna otworzyc pliku" << std::endl;
			}
		}
		else {
			std::cout << "Brak uprawnien do pliku" << std::endl;
		}
		saveRegisters(pcb);
	}

	else if (order == "AF") {
		arg1 = getOrder(pcb);
		arg2 = getOrder(pcb);
		std::regex wzorzec("\".*\"");
		std::cout << "Order: " << order << " " << arg1 << " " << arg2 << std::endl;
		if (std::regex_match(arg2, wzorzec)) {
			arg2.erase(arg2.begin());
			arg2.erase(arg2.end() - 1);
		}
		if (d->czyMozna(arg1)) {
			if (d->open(arg1)) {
				d->dopiszDoPliku(arg1, arg2);
				d->close(arg1);
			}
			else {
				std::cout << "Nie mozna otworzyc pliku" << std::endl;
			}
		}
		else {
			std::cout << "Brak uprawnien do pliku" << std::endl;
		}
		saveRegisters(pcb);
	}

	else if (order == "RF") {
		arg1 = getOrder(pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;
		if (d->czyMozna(arg1)) {
			if (d->open(arg1)) {
				d->wypiszPlik(arg1);
				d->close(arg1);
			}
			else {
				std::cout << "Nie mozna otworzyc pliku" << std::endl;
			}
		}
		else {
			std::cout << "Brak uprawnien do pliku" << std::endl;
		}
		saveRegisters(pcb);
		
	}


	else if (order == "DF") {
		arg1 = getOrder(pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;
		if (d->czyMozna(arg1)) {
			d->usunPlik(arg1);
		}
		else {
			std::cout << "Brak uprawnien do pliku" << std::endl;
		}
		saveRegisters(pcb);
	}

	else if (order == "CP") {
		arg1 = getOrder(pcb);
		arg2 = getOrder(pcb);
		std::cout << "Order: " << order << " " << arg1 << " " << arg2 << "" << arg3 << std::endl;
		std::vector<std::string> doprocesu;
		doprocesu.push_back(arg1);
		doprocesu.push_back(arg2);
		pl->createProcess(doprocesu);
		saveRegisters(pcb);
	}

	else if (order == "DP") {
		arg1 = getOrder(pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;
		std::vector<std::string> doprocesu;
		doprocesu.push_back(arg1);
		pl->terminateProcess(doprocesu);
		saveRegisters(pcb);
	}

	else if (order == "JP") {
		arg1 = getOrder(pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;

		std::regex wzorzec("[0-9]*");

		if (arg1 != "" && std::regex_match(arg1, wzorzec)) {
				set_register("PC", stoi(arg1));
		}

		printRegisters();
		saveRegisters(pcb);
	}

	else if (order == "JZ") {
		arg1 = getOrder(pcb);
		arg2 = getOrder(pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;

		std::regex wzorzec("[0-9]*");

		if (arg1 == "AX" || arg1 == "BX" || arg1 == "CX") {
			if (arg2 != "" && std::regex_match(arg2, wzorzec)) {
				if (get_register(arg1) == 0) {
					set_register("PC", stoi(arg2));
				}
			}
		}

		printRegisters();
		saveRegisters(pcb);
	}

	else if (order == "HL") {
		std::cout << "Order: " << order << std::endl;
		std::vector<std::string> doprocesu;
		/////////////////
		saveRegisters(pcb);
	}
	else {
		error(pcb);
	}
}
