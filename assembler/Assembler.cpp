#include "Assembler.hpp"
#include <iostream>
#include <regex>


/*
//Operacje arytmetyczne//
AD - dodawanie
SB - odejmowanie
MP - mno¿enie
DV - dzielenie
MV - przenoszenie wartoci
IC - zwiêkszenie wartosci rejestru o 1
DC - zmniejszenie wartosci rejestru o 1

MR - odczyt z pamieci ??
MS - zapis do pamieci ??
JP - skok bezwarunkowy
JZ - skok przy zerowej wartoœci
HL - koniec programu

//Operacje na plikach//
CR file_name - utworzenie pliku o podanej nazwie
OF file_name - otwiera plik o podanej nazwie
CF file_name - zamyka plik o podanej nazwie
WF file_name content - zapisuje zawartoœæ do pliku
AF file_name content - dopisuje zawartoœæ do pliku
RF file_name - odczyt z pliku
RN file_name file_name_new - zmienia nazwê pliku
DF file_name - usuwa plik

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


void Assembler::run(Process &pcb) {
	getRegistersState(pcb);

	std::string order;
	order.clear();
	//	order = getOrder(mm, pcb);
	std::string arg1, arg2, arg3;
	int value = 0;

	if (order == "AD") {
		//		arg1 = getOrder(mm, pcb);
		//		arg2 = getOrder(mm, pcb);
		std::cout << "Order: " << order << " " << arg1 << " " << arg2 << std::endl;


		if ((arg1 == "AX" || arg1 == "BX" || arg1 == "CX") && isdigit(arg2[0])) {
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
		//		arg1 = getOrder(mm, pcb);
		//		arg2 = getOrder(mm, pcb);
		std::cout << "Order: " << order << " " << arg1 << " " << arg2 << std::endl;

		if ((arg1 == "AX" || arg1 == "BX" || arg1 == "CX") && isdigit(arg2[0])) {
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
		//		arg1 = getOrder(mm, pcb);
		//		arg2 = getOrder(mm, pcb);
		std::cout << "Order: " << order << " " << arg1 << " " << arg2 << std::endl;

		if ((arg1 == "AX" || arg1 == "BX" || arg1 == "CX") && isdigit(arg2[0])) {
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
		//		arg1 = getOrder(mm, pcb);
		//		arg2 = getOrder(mm, pcb);
		std::cout << "Order: " << order << " " << arg1 << " " << arg2 << std::endl;

		if ((arg1 == "AX" || arg1 == "BX" || arg1 == "CX") && isdigit(arg2[0])) {
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
		//		arg1 = getOrder(mm, pcb);
		//		arg2 = getOrder(mm, pcb);
		std::cout << "Order: " << order << " " << arg1 << " " << arg2 << std::endl;

		if ((arg1 == "AX" || arg1 == "BX" || arg1 == "CX") && isdigit(arg2[0])) {
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
		//		arg1 = getOrder(mm, pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;

		if (arg1 == "AX" || arg1 == "BX" || arg1 == "CX") {
			set_register(arg1, get_register(arg1) + 1);
		}

		printRegisters();
		saveRegisters(pcb);
	}

	if (order == "DC") {
		//		arg1 = getOrder(mm, pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;

		if (arg1 == "AX" || arg1 == "BX" || arg1 == "CX") {
			set_register(arg1, get_register(arg1) - 1);
		}

		printRegisters();
		saveRegisters(pcb);
	}

	if (order == "MR") {
		//////
	}

	if (order == "MS") {
		/////
	}

	if (order == "CR") {
		//		arg1 = getOrder(mm, pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;
		////////
		saveRegisters(pcb);
	}

	if (order == "OF") {
		//		arg1 = getOrder(mm, pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;
		/////
		saveRegisters(pcb);
	}

	if (order == "CF") {
		//		arg1 = getOrder(mm, pcb);
		//		arg2 = getOrder(mm, pcb);
		std::cout << "Order: " << order << " " << arg1 << " " << arg2 << std::endl;
		/////////
		saveRegisters(pcb);
	}

	if (order == "WF") {
		//		arg1 = getOrder(mm, pcb);
		//		arg2 = getOrder(mm, pcb);
		std::regex wzorzec("\".*\"");
		std::cout << "Order: " << order << " " << arg1 << " " << arg2 << std::endl;
		if (std::regex_match(arg2, wzorzec)) {
			arg2.erase(arg2.begin());
			arg2.erase(arg2.end() - 1);
		}
		/////////
	}

	if (order == "RF") {
		//		arg1 = getOrder(mm, pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;
		//////////
		saveRegisters(pcb);
	}

	if (order == "RN") {
		//		arg1 = getOrder(mm, pcb);
		//		arg2 = getOrder(mm, pcb);
		std::cout << "Order: " << order << " " << arg1 << " " << arg2 << std::endl;
		///////////
	}

	if (order == "DF") {
		//		arg1 = getOrder(mm, pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;
		////////////
	}

	if (order == "CP") {
		//		arg1 = getOrder(mm, pcb);
		//		arg2 = getOrder(mm, pcb);
		//		arg3 = getOrder(mm, pcb);
		std::cout << "Order: " << order << " " << arg1 << " " << arg2 << "" << arg3 << std::endl;
		/////////////
		saveRegisters(pcb);
	}

	if (order == "DP") {
		//		arg1 = getOrder(mm, pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;
		/////////////////
		saveRegisters(pcb);
	}

	if (order == "JP") {
		//		arg1 = getOrder(mm, pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;

		if (arg1 != "" && isdigit(arg1[0])) {
			if (arg1 != "" && isdigit(arg1[0])) {
				set_register("PC", stoi(arg1));
			}
		}

		printRegisters();
		saveRegisters(pcb);
	}

	if (order == "JZ") {
		//		arg1 = getOrder(mm, pcb);
		//		arg2 = getOrder(mm, pcb);
		std::cout << "Order: " << order << " " << arg1 << std::endl;

		if (arg1 == "AX" || arg1 == "BX" || arg1 == "CX") {
			if (arg2 != "" && isdigit(arg2[0])) {
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
