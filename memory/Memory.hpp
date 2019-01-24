#pragma once
#ifndef Memory_H
#define Memory_H
#include <iostream>
#include <list>
#include <queue>
#include <string>
using namespace std;
enum class CharTable : unsigned char
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

struct STRON
{
	int RamaZajeta;
	bool wPam;
};

struct FIFO_entry {
	int PID;
	int pageNumber;

	FIFO_entry(int PID, int pageNumber) {
		this->PID = PID;
		this->pageNumber = pageNumber;
	}
};

class Memory
{
private:
	//---RAM---//
	char * RAM;
	const int WIE_PAM = 256;
	const int WIE_RAM = 16;
	const int ILOSC_RAM = WIE_PAM / WIE_RAM;
	//---Obliczenia zwiazane z ramem i plikiem wym---//
	const int ObliczOffset(int addr1);
	const int ObliczNumerStrony(int addr1);
	const int ObliczAdresFizyczny(int PID, int addr1);
	const int ObliczTabliceStronic(int siBytes);
	//---Zapewnienie wolnej ramy Procesowi---//
	const void ZapewnijWolnaRame();//=Zapewnienie ¿e rama jest wolna
	//---Odczyt Pamieci---//
	const char OdczytajZPamieci(int PID, int addr1);
	//---Zapisanie danych w PAMRam---//
	const void ZapiszWPamieci(int PID, int addr1, char element);
	//---Zapewnienie miejsca dla Strony w pamieci ram---//
	const void ZapewnijStroneWPamieci(int PID, int logicalAddress);
	//---Pobranie Ramy z pamieci dla procesu---//
	const int PobierzWolRamePamieci();
	//---PLIK WYMIANY---//
	int pageTableSize;
	char * PlikWymiany;
	const int ILOSC_RAM_P_WYMIANY = 1024;
	const int WIE_P_WYMIANY = ILOSC_RAM_P_WYMIANY * WIE_RAM;
	//---Zapis do pliku wymiany bez pam ram---//
	const void ZapiszDoPlikuWym(int nr, string Content);
	//---Pobieranie wolnej ramki z p. Wymiany---//
	const int PobierzWolnaRamePWym();
	//---Wyczyszczenie pustej ramki pliku wymiany---//
	const void WyczyscRamPlikuWym(int frameNumber);
	list<int> WolneRamki;
	list<int> WolneRamkiPlikuWymiany;
	list<FIFO_entry> FIFO;
	//---Przenoszenie z pliku wymiany do ramu i w druga strone---//
	const void PrzeStroPWymDoPam(int PID, int pageNr);
	const void PrzeStroPamDoPWym(int PID, int pageNr);
	const void PrzeZawPamDoPWym(int MemoryFrame, int SwapFileFrame);
	const void PrzeZawPWymDoPam(int SwapFileFrame, int MemoryFrame);
	//---Wpis do Fifo---//
	const void DodajDoFifo(FIFO_entry entry);
	const bool BrakMieWPowAdr(int PID, int logicalAddress);
public:
	STRON* pageTable;
	const void UtworzProgram(int PID, string path);
	//-----Pamiec-----//
	void PrzydzialPamieci(int PID, string proces, int size);
	const void zwolnieniePamieci(int PID);
	const void WypiszZasobPamieci(int nrToPrint = 0);
	const void WpiszZasobPamDoPWym(int nr, string zasobPam);
	void PIDproces(int PID, string plik);
	//----Sprawdzanie Powierzchni Adresowej----//
	const bool CzyAdrWPowAdresss(int AddrLog);
	const bool CzyZasiegAdrWPowAdres(int AddrLog, int range);
	//----Drukowanie----//
	const void WydrukujProcesy(int PID, bool wRamie);
	const void WydrukujFIFO();
	const void WydrukujTabliceStronic(int PID);
	const void WydrukujRame(int RamaNr, int StronaNr = -1);
	const void WydrukujRamePWym(int RamaNr, int StronaNr = -1);
	//----Odczytywanie i zapisywanie stringow----//
	//(potrzebne do odczytu procesow//
	void zapiszString(int PID, int Addr1, string content);
	const string odczytajString(int PID, int Addr1);
	//konstruktor//
	void UstTabStronic(STRON* newpageTable);			//Przemkowe RAM'y
	STRON* PobTabStronic();
	void UstWielTabStronic(int num);
	int PobWielTabStronic();
	Memory();
	~Memory();
};
#endif