#pragma once
#include "Process.h"
#include <iostream>
#include <list>
#include <queue>
#include <string>
using namespace std;
enum class CharTable : char
{
	CTL = 218, //Corner Top Left
	CTR = 191, //Corner Top Right
	CBL = 192, //Corner Bottom Left
	CBR = 217, //Corner Bottom Right
	VLR = 195, //Vertical Line
	VLL = 180,
	VL = 179,
	HLT = 193,
	HLB = 194,
	HL = 196,
	Cross = 197
};

class Process;
struct STRON;
struct FIFO_entry {
	Process * pcb;
	int pageNumber;

	FIFO_entry(Process * pcb, int pageNumber) {
		this->pcb = pcb;
		this->pageNumber = pageNumber;
	}
};

class Memory
{
private:
	enum class BledyPam {
		OUT_OF_RANGE = 9,
		OUT_OF_MEM = 10
	};
	//---RAM---//
	char * RAM;
	const int WIE_PAM = 256;
	const int WIE_RAM = 16;
	const int ILOSC_RAM = WIE_PAM / WIE_RAM;
	//---Obliczenia zwiazane z ramem i plikiem wym---//
	int ObliczOffset(int addr1);
	int ObliczNumerStrony(int addr1);
	int ObliczAdresFizyczny(Process * pcb, int addr1);
	int ObliczTabliceStronic(int siBytes);
	//---Zapewnienie wolnej ramy Procesowi---//
	void ZapewnijWolnaRame();//=Zapewnienie ¿e rama jest wolna
	//---Odczyt Pamieci---//
	char OdczytajZPamieci(Process * pcb, int addr1);
	//---Zapisanie danych w PAMRam---//
	void ZapiszWPamieci(Process * pcb, int addr1, char element);
	//---Zapewnienie miejsca dla Strony w pamieci ram---//
	void ZapewnijStroneWPamieci(Process * pcb, int logicalAddress);
	//---Pobranie Ramy z pamieci dla procesu---//
	int PobierzWolRamePamieci();
	//---PLIK WYMIANY---//
	char * PlikWymiany;
	const int ILOSC_RAM_P_WYMIANY = 1024;
	const int WIE_P_WYMIANY = ILOSC_RAM_P_WYMIANY * WIE_RAM;
	//---Zapis do pliku wymiany bez pam ram---//
	void ZapiszDoPlikuWym(int nr, string Content);
	//---Pobieranie wolnej ramki z p. Wymiany---//
	int PobierzWolnaRamePWym();
	//---Wyczyszczenie pustej ramki pliku wymiany---//
	void WyczyscRamPlikuWym(int frameNumber);
	list<int> WolneRamki;
	list<int> WolneRamkiPlikuWymiany;
	list<FIFO_entry> FIFO;
	//---Przenoszenie z pliku wymiany do ramu i w druga strone---//
	void PrzeStroPWymDoPam(Process * pcb, int pageNr);
	void PrzeStroPamDoPWym(Process * pcb, int pageNr);
	void PrzeZawPamDoPWym(int MemoryFrame, int SwapFileFrame);
	void PrzeZawPWymDoPam(int SwapFileFrame, int MemoryFrame);
	//---Wpis do Fifo---//
	void DodajDoFifo(FIFO_entry entry);
	bool BrakMieWPowAdr(Process * pcb, int logicalAddress);
public:
	//-----Pamiec-----//
	void PrzydzialPamieci(Process * pcb, string proces, int size);
	void zwolnieniePamieci(Process * pcb);
	void WypiszZasobPamieci(int nrToPrint = 0);
	void WpiszZasobPamDoPWym(int nr,string zasobPam);
	//----Sprawdzanie Powierzchni Adresowej----//
	bool CzyAdrWPowAdresss(Process * pcb, int AddrLog);
	bool CzyZasiegAdrWPowAdres(Process * pcb, int AddrLog, int range);
	//----Drukowanie----//
	void WydrukujProcesy(Process * pcb, bool wRamie);
	void WydrukujFIFO();
	void WydrukujTabliceStronic(Process * pcb);
	void WydrukujRame(int RamaNr, int StronaNr = -1);
	void WydrukujRamePWym(int RamaNr, int StronaNr = -1);
	//----Odczytywanie i zapisywanie stringow----//
	//(potrzebne do odczytu procesow//
	void zapiszString(Process*pcb, int Addr1, string content);
	string odczytajString(Process * pcb, int Addr1);
	//konstruktor//
	Memory();
	~Memory();
};

