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

Assembler::Assembler() {
	PID = 0;
	regAX = 0;
	regBX = 0;
	regCX = 0;
	PC = 0;
}


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

std::string Assembler::getOrder(Memory &m, Process &pcb) {
	std::string order;
	order = m.odczytajString(&pcb,PC);
	PC += order.size() + 1;
	return order;
}

std::map<std::string, Sync>Sync::zamkiNaPlikach;

void Assembler::run(Process &pcb, Memory &m, Disk &disk) {
	

	getRegistersState(pcb);

	std::string order;
	order.clear();
	order = getOrder(m, pcb);
	std::string arg1, arg2, arg3;
	int value = 0;

	if (order == "AD") {
		arg1 = getOrder(m, pcb);
		arg2 = getOrder(m, pcb);
		
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

	if (order == "SB") {
		arg1 = getOrder(m, pcb);
		arg2 = getOrder(m, pcb);
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

	if (order == "MP") {
		arg1 = getOrder(m, pcb);
		arg2 = getOrder(m, pcb);
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

	if (order == "DV") {
		arg1 = getOrder(m, pcb);
		arg2 = getOrder(m, pcb);
		std::cout << "Order: " << order << " " << arg1 << " " << arg2 << std::endl;

		std::regex wzorzec("[0-9]*");

		if ((arg1 == "AX" || arg1 == "BX" || arg1 == "CX") && std::regex_match(arg2, wzorzec)) {
			value = stoi(arg2);
			if (value != 0) {
				set_register(arg1, get_register(arg1) / value);
			}

			else {
				std::cout << "Don't divide by 0" << std::endl;
			}
		}

		else if ((arg1 == "AX" || arg1 == "BX" || arg1 == "CX") && (arg2 == "AX" || arg2 == "BX" || arg2 == "CX")) {
			if (get_register(arg2) != 0) {
				set_register(arg1, get_register(arg1) / get_register(arg2));
			}

			else {
				std::cout << "Don't divide by 0" << std::endl;
			}
		}

		printRegisters();
		saveRegisters(pcb);
	}

	if (order == "MV") {
		arg1 = getOrder(m, pcb);
		arg2 = getOrder(m, pcb);
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

	if (order == "IC") {
		arg1 = getOrder(m, pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;

		if (arg1 == "AX" || arg1 == "BX" || arg1 == "CX") {
			set_register(arg1, get_register(arg1) + 1);
		}

		printRegisters();
		saveRegisters(pcb);
	}

	if (order == "DC") {
		arg1 = getOrder(m, pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;

		if (arg1 == "AX" || arg1 == "BX" || arg1 == "CX") {
			set_register(arg1, get_register(arg1) - 1);
		}

		printRegisters();
		saveRegisters(pcb);
	}

	if (order == "LC") {
		arg1 = getOrder(m, pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;

		Sync::lockFile(arg1, &pcb);
	}

	if (order == "UL") {
		arg1 = getOrder(m, pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;
		Sync::unlockFile(arg1, &pcb);
	}

	if (order == "CR") {
		arg1 = getOrder(m, pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;
		////////
		disk.dodajpPlik(arg1);
		saveRegisters(pcb);
		
	}

	if (order == "WF") {
		arg1 = getOrder(m, pcb);
		arg2 = getOrder(m, pcb);
		std::regex wzorzec("\".*\"");
		std::cout << "Order: " << order << " " << arg1 << " " << arg2 << std::endl;
		if (std::regex_match(arg2, wzorzec)) {
			arg2.erase(arg2.begin());
			arg2.erase(arg2.end() - 1);
		}
		if (disk.czyMozna(arg1)) {
			if (disk.open(arg1)) {
				disk.nadpiszPlik(arg1, arg2);
				disk.close(arg1);
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

	if (order == "AF") {
		arg1 = getOrder(m, pcb);
		arg2 = getOrder(m, pcb);
		std::regex wzorzec("\".*\"");
		std::cout << "Order: " << order << " " << arg1 << " " << arg2 << std::endl;
		if (std::regex_match(arg2, wzorzec)) {
			arg2.erase(arg2.begin());
			arg2.erase(arg2.end() - 1);
		}
		if (disk.czyMozna(arg1)) {
			if (disk.open(arg1)) {
				disk.dopiszDoPliku(arg1, arg2);
				disk.close(arg1);
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

	if (order == "RF") {
		arg1 = getOrder(m, pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;
		if (disk.czyMozna(arg1)) {
			if (disk.open(arg1)) {
				disk.wypiszPlik(arg1); //Andrzej do poprawy
				disk.close(arg1);
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


	if (order == "DF") {
		arg1 = getOrder(m, pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;
		if (disk.czyMozna(arg1)) {
			disk.usunPlik(arg1);
		}
		saveRegisters(pcb);
	}

	if (order == "CP") {
		arg1 = getOrder(m, pcb);
		arg2 = getOrder(m, pcb);
		arg3 = getOrder(m, pcb);
		std::cout << "Order: " << order << " " << arg1 << " " << arg2 << "" << arg3 << std::endl;
		

		saveRegisters(pcb);
	}

	if (order == "DP") {
		arg1 = getOrder(m, pcb);
		arg2 = getOrder(m, pcb);
		std::cout << "Order: " << order << " " << arg1 << " " << arg2 << std::endl;
		/////////////////
		saveRegisters(pcb);
	}

	if (order == "JP") {
		arg1 = getOrder(m, pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;

		std::regex wzorzec("[0-9]*");

		if (arg1 != "" && std::regex_match(arg1, wzorzec)) {
				set_register("PC", stoi(arg1));
		}

		printRegisters();
		saveRegisters(pcb);
	}

	if (order == "JZ") {
		arg1 = getOrder(m, pcb);
		arg2 = getOrder(m, pcb);
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

	if (order == "HL") {
		std::cout << "Order: " << order << std::endl;
		saveRegisters(pcb);
		//////
	
	}
}
